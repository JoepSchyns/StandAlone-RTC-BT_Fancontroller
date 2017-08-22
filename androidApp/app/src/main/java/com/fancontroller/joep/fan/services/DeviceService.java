package com.fancontroller.joep.fan.services;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import static android.content.ContentValues.TAG;

/**
 * Created by Joep on 21/08/2017.
 */

public class DeviceService {

    public static final int STATE_DISCONNECTED = 0;
    public static final int STATE_CONNECTING = 1;
    public static final int STATE_CONNECTED = 2;
    public static final String GET_FAN_ON = "GET_FAN_ON";
    public int connectionState = STATE_DISCONNECTED;
    public final static String KEY_MAC_INTENT =
            "KEY_MAC_INTENT";
    public final static String KEY_VALUE_INTENT =
            "KEY_VALUE_INTENT";
    public final static String ACTION_GATT_CONNECTED =
            "ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED =
            "ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED =
            "ACTION_GATT_SERVICES_DISCOVERED";
    public final static String ACTION_DATA_AVAILABLE =
            "ACTION_DATA_AVAILABLE";
    public final static String EXTRA_DATA =
            "EXTRA_DATA";

    public final static String OK_RESULT = "+OK";
    public final static String ERROR_RESULT = "+ERROR";
    public final static String MAX_FANS_RESULT = "+MAX_FANS_ERROR";
    public final static String FAN_ON = "fanOn";
    public final static String FAN_OFF = "fanOff";
    public final static String SET_FAN = "setFan";
    public final static String SET_TIMER_FAN = "setTimerFan";
    public final static String SET_TIME = "setTime";
    public final static String GET_FANS = "getFans";
    public final static String GET_TIME = "getTime";
    public final static String GET_INFO = "getInfo";
    public final static String REMOVE_FAN = "removeFan";
    public final static String REMOVE_FANS = "removeFans";
    public final static String MAX_FANS = "maxFans";
    public final static String AMOUNT_FANS = "amountFans";
    public final static String GET_FAN_TIMER = "getFanTimer";

    private BluetoothDevice device;
    private BluetoothGatt bluetoothGatt;
    private Context context;

    public DeviceService(Context context, BluetoothDevice device){
        this.device = device;
        this.context = context;
        bluetoothGatt = device.connectGatt(context,true,bluetoothGattCallback);



    }

    List<BluetoothGattCharacteristic> characteristics;
    BluetoothGattCallback bluetoothGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            String intentAction;
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                intentAction = ACTION_GATT_CONNECTED;
                connectionState = STATE_CONNECTED;
                broadcastUpdate(intentAction);
                Log.i(TAG, "Connected to GATT server.");
                // Attempts to discover services after successful connection.
                Log.i(TAG, "Attempting to start service discovery:" +
                        bluetoothGatt.discoverServices());


            } else if (newState == STATE_DISCONNECTED) {
                intentAction = ACTION_GATT_DISCONNECTED;
                connectionState = STATE_DISCONNECTED;
                Log.i(TAG, "Disconnected from GATT server.");
                broadcastUpdate(intentAction);
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            characteristics = new ArrayList<>();
            if (status == BluetoothGatt.GATT_SUCCESS) {
                broadcastUpdate(ACTION_GATT_SERVICES_DISCOVERED);

                for (BluetoothGattService service :gatt.getServices()) {
                    characteristics.addAll(service.getCharacteristics());


                }
                bluetoothGatt.setCharacteristicNotification(characteristics.get(characteristics.size() - 1),true);//TODO make fixed



            } else {
                Log.w(TAG, "onServicesDiscovered received: " + status);
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt,
                                         BluetoothGattCharacteristic characteristic,
                                         int status) {
            Log.d(TAG, "onCharacteristicRead: ");
            if (status == BluetoothGatt.GATT_SUCCESS) {
                broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
            }
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt,
                                            BluetoothGattCharacteristic characteristic) {
            Log.d(TAG, "onCharacteristicChanged: ");
            broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
        }
    };

    public boolean writeCharacteristics(String text){
        if(characteristics == null){
            return false;
        }
        BluetoothGattCharacteristic chars = characteristics.get(characteristics.size() - 1); //get the last one since this one should be the serial write //TODO
        Log.d(TAG, "writeCharacteristics: " + chars.getUuid().toString());
        chars.setValue(text);
        bluetoothGatt.writeCharacteristic(chars);

        return true;
    }

    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        intent.putExtra(KEY_MAC_INTENT,device.getAddress());
        context.sendBroadcast(intent);
    }

    private void broadcastUpdate(final String action,
                                 final BluetoothGattCharacteristic characteristic) {
        final Intent intent = new Intent(action);
        intent.putExtra(KEY_MAC_INTENT,device.getAddress());
        intent.putExtra(KEY_VALUE_INTENT,characteristic.getStringValue(0));
        context.sendBroadcast(intent);
    }

    public BluetoothDevice getDevice(){
        return bluetoothGatt.getDevice();
    }


}
