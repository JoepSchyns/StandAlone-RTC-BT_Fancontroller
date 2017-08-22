package com.fancontroller.joep.fan;

import android.Manifest;
import android.bluetooth.BluetoothGattCharacteristic;

import java.util.UUID;


/**
 * Created by Joep on 22/08/2017.
 * TODO why can't I create a static charateristic why do I have to retreive the characteristic every time
 */

public class Hm10Characteristic extends BluetoothGattCharacteristic {

    private static final String UUID_STRING = "0000ffe1-0000-1000-8000-00805f9b34fb";
    private static final int PERMISSIONS = 0;
    private static final int PROPERTIES = 22;

    public Hm10Characteristic() {
        super(java.util.UUID.fromString(UUID_STRING), PROPERTIES, PERMISSIONS);
    }
}
