package com.fancontroller.joep.fan.activities;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;
import android.widget.ProgressBar;

import com.fancontroller.joep.fan.BluetoothDevices;
import com.fancontroller.joep.fan.R;
import com.fancontroller.joep.fan.adapters.DeviceAdapter;
import com.fancontroller.joep.fan.data.DB;
import com.fancontroller.joep.fan.services.DeviceConnectService;
import com.fancontroller.joep.fan.services.DeviceService;

import java.util.List;

public class FindDevice extends AppCompatActivity {

    private BluetoothDevices bluetoothDevices;

    private BluetoothLeScanner bluetoothLeScanner;
    private boolean scanning;
    private Handler handler;
    // Stops scanning after 10 seconds.
    private static final long SCAN_PERIOD = 10000;
    private static final int REQUEST_ENABLE_BT = 0;
    private DeviceAdapter deviceAdapter;
    private DeviceConnectService deviceConnectService;
    boolean deviceConnectServiceBound = false;
    private ListView deviceList;
    private DB db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_find_device);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        deviceList = (ListView) findViewById(R.id.deviceList);

        enableBluetooth();
        handler = new Handler();

        bluetoothDevices = new BluetoothDevices();

        deviceAdapter = new DeviceAdapter(this,bluetoothDevices.devices);
        deviceList.setAdapter(deviceAdapter);

        IntentFilter intentFiler = new IntentFilter();
        intentFiler.addAction(DeviceService.ACTION_DATA_AVAILABLE);
        intentFiler.addAction(DeviceService.ACTION_GATT_CONNECTED);
        intentFiler.addAction(DeviceService.ACTION_GATT_DISCONNECTED);
        intentFiler.addAction(DeviceService.ACTION_GATT_SERVICES_DISCOVERED);

        registerReceiver(broadcastReceiver,intentFiler);

        db = new DB(getApplicationContext());



        bluetoothLeScanner.startScan(scanCallback); //start scanning on activity start
    }

    BroadcastReceiver broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.d("test", "onReceive: " + intent.getAction());

            if(intent.getAction().equals(DeviceService.ACTION_GATT_CONNECTED)){ //connection with new device is succesfull
                List<BluetoothDevice> devices = deviceConnectService.getConnectedDevices();

                for (BluetoothDevice device: devices) {
                    Log.d("test", "onReceive: " + device.getAddress());
                    View v = deviceList.findViewWithTag(device.getAddress());
                    ( v.findViewById(R.id.progressBar)).setVisibility(View.INVISIBLE);
                    ( v.findViewById(R.id.check)).setVisibility(View.VISIBLE);

                    db.add(device.getAddress(),device.getName());
                }


            }
        }
    };

    private void enableBluetooth(){
        // Initializes Bluetooth adapter.
        final BluetoothManager bluetoothManager =
                (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        final BluetoothAdapter bluetoothAdapter = bluetoothManager.getAdapter();


        if (bluetoothAdapter == null || !bluetoothAdapter.isEnabled()) { //enable bluetooth if not
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        bluetoothLeScanner = bluetoothAdapter.getBluetoothLeScanner();
    }





    // Device scan callback.
    private ScanCallback scanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            super.onScanResult(callbackType, result);

            boolean newDevice = bluetoothDevices.addDevice(result.getDevice());

            if(newDevice){
                deviceAdapter.notifyDataSetChanged();
            }
        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {
            super.onBatchScanResults(results);
        }

        @Override
        public void onScanFailed(int errorCode) {
            super.onScanFailed(errorCode);
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_find_device, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.scanButton) {
            bluetoothLeScanner.startScan(scanCallback);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(broadcastReceiver);
        bluetoothLeScanner.stopScan(scanCallback);
    }

    @Override
    protected void onStart() {
        super.onStart();
        // Bind to LocalService
        Intent intent = new Intent(this, DeviceConnectService.class);
        bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onStop() {
        super.onStop();
        // Unbind from the service
        if (deviceConnectServiceBound) {
            unbindService(mConnection);
            deviceConnectServiceBound = false;
        }
    }


    /** Defines callbacks for service binding, passed to bindService() */
    private ServiceConnection mConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className,
                                       IBinder service) {
            // We've bound to LocalService, cast the IBinder and get LocalService instance
            DeviceConnectService.LocalBinder binder = (DeviceConnectService.LocalBinder) service;
            deviceConnectService = binder.getService();
            deviceConnectServiceBound = true;
            Log.d("test", "onServiceConnected: ");

        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            deviceConnectServiceBound = false;
        }
    };
}
