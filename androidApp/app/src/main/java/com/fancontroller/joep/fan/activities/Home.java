package com.fancontroller.joep.fan.activities;

import android.Manifest;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.IBinder;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextClock;
import android.widget.Toast;

import com.fancontroller.joep.fan.FanControl.Fan;
import com.fancontroller.joep.fan.FanControl.FanController;
import com.fancontroller.joep.fan.R;
import com.fancontroller.joep.fan.services.DeviceConnectService;
import com.fancontroller.joep.fan.services.DeviceService;

import java.util.ArrayList;
import java.util.List;

public class Home extends AppCompatActivity {

    private DeviceConnectService deviceConnectService;
    private static TextClock mainClock;
    private static Switch mainSwitchActive;
    private static Fan mainFan;
    boolean deviceConnectServiceBound = false;
    private FanController fanController;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(view.getContext(), FindDevice.class);
                startActivity(intent);
            }
        });

        setupBluetooth();

        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                0);

        IntentFilter intentFiler = new IntentFilter();
        intentFiler.addAction(DeviceService.ACTION_DATA_AVAILABLE);
        intentFiler.addAction(DeviceService.ACTION_GATT_CONNECTED);
        intentFiler.addAction(DeviceService.ACTION_GATT_DISCONNECTED);
        intentFiler.addAction(DeviceService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFiler.addAction(Fan.NEW_INFO);

        registerReceiver(broadcastReceiver,intentFiler);

        fanController = new FanController(getApplicationContext());

        mainClock = (TextClock)findViewById(R.id.mainClock);
        mainSwitchActive = (Switch)findViewById(R.id.mainSwitchActive);
        mainSwitchActive.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                String action = DeviceService.FAN_OFF;
                if(isChecked){
                    action = DeviceService.FAN_ON;
                }
                mainFan.fanOn = isChecked;
                deviceConnectService.writeTo(mainFan.bluetoothDevice.getAddress(),action);
            }
        });



    }



    private void setupBluetooth() {
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, R.string.ble_not_supported, Toast.LENGTH_SHORT).show();
            finish();
        }

    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_home, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    BroadcastReceiver broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
        Log.d("test", "onReceive: " + intent.getAction());
        if(intent.getAction().equals(DeviceService.ACTION_GATT_SERVICES_DISCOVERED)){
            List<BluetoothDevice> bluetoothDevices = deviceConnectService.getConnectedDevices();
            createNewFans(bluetoothDevices);
        }else if (intent.getAction().equals(DeviceService.ACTION_DATA_AVAILABLE)){

            String mac = intent.getStringExtra(DeviceService.KEY_MAC_INTENT);
            String value = intent.getStringExtra(DeviceService.KEY_VALUE_INTENT);
            fanController.setInfo(mac,value);
        }else if(intent.getAction().equals(Fan.NEW_INFO)){ //if there is new fan info update fields

            //String mac = intent.getStringExtra(DeviceService.KEY_MAC_INTENT);

                updateMainInfo();

        }

        }
    };

    private void createNewFans(List<BluetoothDevice> bluetoothDevices){
        Log.d("test", "createNewFans: connected devices " + bluetoothDevices.size());
        List<BluetoothDevice> newBluetoothDevices = fanController.notInFanControllerList(bluetoothDevices);
        Log.d("test", "createNewFans: connected new devices " + newBluetoothDevices.size());
        for (BluetoothDevice device: newBluetoothDevices) {
            Fan fan  = new Fan(device,getApplicationContext());
            mainFan = fan;
            fanController.add(fan);
            deviceConnectService.writeTo(device.getAddress(),DeviceService.GET_INFO); //request information about the fan

        }
    }

    public void updateMainInfo(){
        if(mainFan != null){
            //setTime //TODO set or always update
            mainSwitchActive.setChecked(mainFan.fanOn);
        }
    }



    /** Defines callbacks for service binding, passed to bindService() */
    public ServiceConnection mConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className,
                                       IBinder service) {
            // We've bound to LocalService, cast the IBinder and get LocalService instance
            DeviceConnectService.LocalBinder binder = (DeviceConnectService.LocalBinder) service;
            deviceConnectService = binder.getService();
            deviceConnectServiceBound = true;
            Log.d("test", "onServiceConnected: ");

            createNewFans(deviceConnectService.getConnectedDevices());//create new fans if neccesairy

        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            deviceConnectServiceBound = false;
        }
    };
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

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(broadcastReceiver);
    }

}
