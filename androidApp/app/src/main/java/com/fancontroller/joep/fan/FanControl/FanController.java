package com.fancontroller.joep.fan.FanControl;

import android.bluetooth.BluetoothDevice;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by Joep on 21/08/2017.
 */

public class FanController {

    private List<Fan> fans;

    public FanController(){
        fans = new ArrayList<>();
    }



    public List<BluetoothDevice> notInFanControllerList(List<BluetoothDevice> devices){

        fanLoop : for (Fan fan: fans) {
            Iterator<BluetoothDevice> iterator = devices.iterator();

            while (iterator.hasNext()){
                BluetoothDevice bluetoothDevice = iterator.next();
                if(fan.hasBluetoothDevice(bluetoothDevice)){
                    devices.remove(devices);
                    continue fanLoop;
                }
            }

        }

        return devices;
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

    public void add(BluetoothDevice bluetoothDevice){
        fans.add(new Fan(bluetoothDevice));
    }
}
