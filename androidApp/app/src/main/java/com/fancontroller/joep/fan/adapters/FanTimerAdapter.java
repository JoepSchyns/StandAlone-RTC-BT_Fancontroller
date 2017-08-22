package com.fancontroller.joep.fan.adapters;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.TextView;

import com.fancontroller.joep.fan.FanControl.FanTimer;
import com.fancontroller.joep.fan.R;
import com.fancontroller.joep.fan.services.DeviceConnectService;

import java.util.ArrayList;
import java.util.Calendar;

/**
 * Created by Joep on 21/08/2017.
 */

public class FanTimerAdapter extends ArrayAdapter {


    public FanTimerAdapter(Context context, ArrayList<FanTimer> fanTimers) {
        super(context,0,fanTimers);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        // Get the data item for this position
        final FanTimer fanTimer = (FanTimer) getItem(position);
        if(!fanTimer.enabled){
            return null;
        }
        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.fan_row, parent, false);
        }

        TextView time = (TextView) convertView.findViewById(R.id.timeField);
        TextView speed = (TextView) convertView.findViewById(R.id.speedField);
        Button remove = (Button) convertView.findViewById(R.id.removeButton);



        //fanTimer.calendar.get(Calendar.SECOND);
        time.setText(fanTimer.calendar.get(Calendar.HOUR_OF_DAY) + ":" + fanTimer.calendar.get(Calendar.MINUTE));
        speed.setText(String.valueOf(fanTimer.speed));

        convertView.setTag(fanTimer.id);

        convertView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO
            }
        });

        remove.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO
            }
        });
        return convertView;
    }
}
