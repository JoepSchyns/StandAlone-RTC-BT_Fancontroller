package com.fancontroller.joep.fan.services;

import android.app.IntentService;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.IBinder;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Joep on 19/08/2017.
 */

public class DeviceConnectService extends IntentService {

    private BluetoothAdapter bluetoothAdapter;
    private List<DeviceService> deviceServices;



    public final IBinder mBinder = new LocalBinder();
    /**
     * Creates an IntentService.  Invoked by your subclass's constructor.
     *
     */
    public DeviceConnectService() {
        super("worker");
        deviceServices = new ArrayList<>();
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

    }

    @Override
    protected void onHandleIntent(Intent intent) {
        Bundle extras = intent.getExtras();
        String mac = extras.getString("MAC");

        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(mac);

        deviceServices.add(new DeviceService(this,device));


    }

    public boolean writeTo(String mac,String text){
        for (DeviceService service: deviceServices) {
            if(service.getDevice().getAddress().equals(mac)){
                return service.writeCharacteristics(text);
            }
        }
        return false;//device not found
    }

    public List<BluetoothDevice> getConnectedDevices(){
        List<BluetoothDevice> result = new ArrayList<>();
        for (DeviceService service: deviceServices) {
            if(service.connectionState == DeviceService.STATE_CONNECTED){
                result.add(service.getDevice());
            }
        }
        return result;
    }




    public class LocalBinder extends Binder {
        public DeviceConnectService getService() {
            // Return this instance of LocalService so clients can call public methods
            return DeviceConnectService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

}
