package com.fancontroller.joep.fan.FanControl;

import android.bluetooth.BluetoothDevice;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import static android.content.ContentValues.TAG;

/**
 * Created by Joep on 21/08/2017.
 */

public class Fan {

    BluetoothDevice bluetoothDevice;

    public Fan(BluetoothDevice bluetoothDevice) {
        this.bluetoothDevice = bluetoothDevice;
    }

    public boolean hasBluetoothDevice(BluetoothDevice bluetoothDevice){
        return this.bluetoothDevice.getAddress().equals(bluetoothDevice.getAddress());
    }

    public void setInfo(String info){
        Log.d(TAG, "setInfo: " + info);
    }


}
