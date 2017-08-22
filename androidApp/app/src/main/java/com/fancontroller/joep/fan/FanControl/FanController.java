package com.fancontroller.joep.fan.FanControl;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.util.Log;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import static android.content.ContentValues.TAG;

/**
 * Created by Joep on 21/08/2017.
 */

public class FanController {

    public List<Fan> fans;

    public FanController(Context context){
        fans = new ArrayList<>();

    }



    public List<BluetoothDevice> notInFanControllerList(List<BluetoothDevice> devices){

        List<BluetoothDevice> uniqueDevices = new ArrayList<>();
        devicesLoop : for (BluetoothDevice d : devices) { //remove equal bluetooth devices
            BluetoothDevice uniqueDevice = null;
            for (BluetoothDevice ud : uniqueDevices) {
                if(d.getAddress().equals(ud.getAddress())){
                    continue devicesLoop;
                }
            }
            if (uniqueDevice != null) {
                uniqueDevices.add(uniqueDevice);
            }
            if(uniqueDevices.size() == 0){
                uniqueDevices.add(devices.get(0));
            }

        }

        fanLoop : for (Fan fan: fans) { //remove bluetooth devices that are already in fans
            Iterator<BluetoothDevice> iterator = uniqueDevices.iterator();

            while (iterator.hasNext()){
                BluetoothDevice bluetoothDevice = iterator.next();
                if(fan.hasBluetoothDevice(bluetoothDevice)){
                    uniqueDevices.remove(bluetoothDevice);
                    continue fanLoop;
                }
            }

        }

        return uniqueDevices;
    }

    public void setInfo(String mac,String value){
        Fan fan = getFan(mac);
        fan.setInfo(value);
    }

    private Fan getFan(String mac){
        for (Fan fan : fans) {
            if(fan.bluetoothDevice.getAddress().equals(mac)){
                return fan;
            }
        }
        return null;
    }

    public void add(List<Fan> fans){
        for (Fan fan : fans) {
            add(fan);
        }
    }

    public void add(Fan fan){
        for (Fan controllerFan : fans) {
                if(controllerFan.equals(fan)){
                    return;
                }
        }
        fans.add(fan);
    }
}
