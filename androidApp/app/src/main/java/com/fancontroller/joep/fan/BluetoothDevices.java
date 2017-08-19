package com.fancontroller.joep.fan;

import android.app.ListActivity;
import android.bluetooth.BluetoothDevice;
import android.widget.BaseAdapter;

import java.util.ArrayList;

/**
 * Created by Joep on 19/08/2017.
 */

public class BluetoothDevices {

    public ArrayList<BluetoothDevice> devices;

    public BluetoothDevices(){
        devices = new ArrayList<>();
    }

    public boolean addDevice(BluetoothDevice d){
        if(!devices.contains(d)) {
            devices.add(d);
            return true;
        }
        return false;
    }
}
