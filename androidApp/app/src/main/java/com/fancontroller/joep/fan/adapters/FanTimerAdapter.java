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
import android.widget.TextView;

import com.fancontroller.joep.fan.R;
import com.fancontroller.joep.fan.services.DeviceConnectService;

import java.util.ArrayList;

/**
 * Created by Joep on 21/08/2017.
 */

public class FanTimerAdapter extends ArrayAdapter {


    public FanTimerAdapter(Context context, ArrayList<BluetoothDevice> devices) {
        super(context,0,devices);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        // Get the data item for this position
        final BluetoothDevice device = (BluetoothDevice) getItem(position);
        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.fan_row, parent, false);
        }
        // Lookup view for data population
        //TextView name = (TextView) convertView.findViewById(android.R.id.acti);
        TextView mac = (TextView) convertView.findViewById(android.R.id.text2);
        // Populate the data into the template view using the data object
        //name.setText(device.getName());
        mac.setText(device.getAddress());
        // Return the completed view to render on screen

        convertView.setTag(device.getAddress());

        convertView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(v.getContext(), DeviceConnectService.class);
                intent.putExtra("NAME",device.getName());
                intent.putExtra("MAC",device.getAddress());
                v.getContext().startService(intent);
            }
        });
        return convertView;
    }
}
