package com.fancontroller.joep.fan.FanControl;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.fancontroller.joep.fan.activities.Home;
import com.fancontroller.joep.fan.services.DeviceService;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static android.content.ContentValues.TAG;
import static com.fancontroller.joep.fan.services.DeviceService.KEY_MAC_INTENT;

/**
 * Created by Joep on 21/08/2017.
 */

public class Fan {

    public static final String NEW_INFO = "NEW_INFO";
    public BluetoothDevice bluetoothDevice;

    public boolean fanOn;
    public String time;
    public List<FanTimer> fanTimers;
    public int maxFans;
    public int amountFans;
    public static String NEW_LINE = "\\r\\n|\\r|\\n";
    public static String PLUS_SIGN = "\\+";
    private String prevInfo = "";
    private Context context;


    public Fan(BluetoothDevice bluetoothDevice, Context context) {
        this.bluetoothDevice = bluetoothDevice;
        fanTimers = new ArrayList<>();
        this.context = context;
    }

    public boolean hasBluetoothDevice(BluetoothDevice bluetoothDevice){
        return this.bluetoothDevice.getAddress().equals(bluetoothDevice.getAddress());
    }

    public void setInfo(String infoFragment){

        String[] infos = contructInfo(infoFragment);
        placeInfo(infos);

    }

    private void placeInfo(String[] infos){ //place infomation fragments in correct places
        for (String info : infos) {
            String[] keyValue = info.split(PLUS_SIGN);

            if(keyValue.length != 2){ //contructing info when wrong
                return;
            }

            String key = keyValue[0];
            String value = keyValue[1];

            switch (key){
                case DeviceService.MAX_FANS:
                    maxFans = Integer.parseInt(value);
                    Log.d("placeInfo", "maxFans" + maxFans);
                    break;
                case DeviceService.GET_TIME:
                    time = value;
                    Log.d("placeInfo", "time" + time);
                    break;
                case DeviceService.GET_FAN_TIMER:
                    fanTimers.add(new FanTimer(value));
                    Log.d("placeInfo", "fanTimers" + value);
                    break;
                case DeviceService.AMOUNT_FANS:
                    amountFans = Integer.parseInt(value);
                    Log.d("placeInfo", "amountFans" + amountFans);
                    break;
                case DeviceService.GET_FAN_ON:
                    fanOn = "1".equals(value);
                    Log.d("placeInfo", "fanOn" + fanOn + " value " + value);
                    break;
                default:
                    Log.d(TAG, "placeInfo: info not recognized" + key + " " + value);
                    break;
            }
        }
        broadcastUpdate(NEW_INFO); //update fields user
    }

    private String[] contructInfo(String infoFragment){ //sometimes ln writes for info are not seperated by characteristics read thus info lines have to be constructed from received fragemnts
        if(infoFragment.isEmpty()){ //nothing retreived
            return null;
        }

        String[] segs = infoFragment.split(NEW_LINE);

        segs[0] = prevInfo + segs[0];//add text from previous read to first segment
        prevInfo = "";

        if(!infoFragment.endsWith(NEW_LINE)){ //last segment not complete
            prevInfo  = segs[segs.length -1]; //save not completed segment for next setInfo
            segs = Arrays.copyOf(segs,segs.length-1); //remove last from info list
        }

        return segs;
    }

    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        intent.putExtra(KEY_MAC_INTENT,bluetoothDevice.getAddress());

        context.sendBroadcast(intent);
    }




}
