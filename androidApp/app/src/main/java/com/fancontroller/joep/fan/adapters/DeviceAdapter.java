package com.fancontroller.joep.fan.adapters;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.res.TypedArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.fancontroller.joep.fan.FanControl.Fan;
import com.fancontroller.joep.fan.R;
import com.fancontroller.joep.fan.services.DeviceConnectService;

import java.util.ArrayList;

/**
 * Created by Joep on 19/08/2017.
 */

public class DeviceAdapter extends ArrayAdapter<BluetoothDevice> {
    private BluetoothDevice device;
    public DeviceAdapter(Context context, ArrayList<BluetoothDevice> devices) {
        super(context,0, devices);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        // Get the data item for this position
        device = getItem(position);
        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.device_row, parent, false);
        }
        // Lookup view for data population
        TextView name = (TextView) convertView.findViewById(R.id.textView1);
        TextView mac = (TextView) convertView.findViewById(R.id.textView2);
        final ProgressBar progressBar = (ProgressBar) convertView.findViewById(R.id.progressBar);
        // Populate the data into the template view using the data object
        name.setText(device.getName());
        mac.setText(device.getAddress());
        // Return the completed view to render on screen

        convertView.setTag(device.getAddress());

        convertView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                progressBar.setVisibility(View.VISIBLE);
                Fan.requestDeviceService(v.getContext(),device.getAddress(),device.getName());
            }
        });

        int[] attrs = new int[]{R.attr.selectableItemBackground};
        TypedArray typedArray = convertView.getContext().obtainStyledAttributes(attrs);
        int backgroundResource = typedArray.getResourceId(0, 0);
        convertView.setBackgroundResource(backgroundResource);
        typedArray.recycle();

        return convertView;
    }
}
