package com.fancontroller.joep.fan.FanControl;

import android.util.Log;



import java.util.Calendar;
import java.util.GregorianCalendar;


import static android.content.ContentValues.TAG;

/**
 * Created by Joep on 21/08/2017.
 */

public class FanTimer {
    public int id;
    public boolean enabled;
    private int type;
    public Calendar calendar;
    public int speed;
    public FanTimer(String value){ //0;1;3;11:23:0;250
        Log.d(TAG, "new FanTimer: " + value);
        String[] values = value.split(";");
        if(values.length != 5){
            return;
        }
        id = Integer.parseInt(values[0]);
        enabled = "1".equals(values[1]);
        type = Integer.parseInt(values[2]);
        String[] time = values[3].split(":");
        calendar = new GregorianCalendar(0,0,0,Integer.parseInt(time[0]),Integer.parseInt(time[1]),Integer.parseInt(time[2]));
        speed = Integer.parseInt(values[4]);

    }
}
