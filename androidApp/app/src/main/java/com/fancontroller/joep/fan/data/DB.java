package com.fancontroller.joep.fan.data;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import com.fancontroller.joep.fan.FanControl.Fan;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Joep on 22/08/2017.
 */

public class DB {

    private Context context;
    private SQLiteDatabase db;
    private FanReaderDbHelper fanReaderDbHelper;
    public DB(Context context){
        this.context = context;
        fanReaderDbHelper = new FanReaderDbHelper(context);
        db = fanReaderDbHelper.getWritableDatabase();
    }

    public long add(String mac, String name){

        List<Fan> fans = read();

        for(Fan fan : fans){ //if the device is already in the db dont add
            if(fan.bluetoothDevice.getAddress().equals(mac)){
                return -1;
            }
        }
        ContentValues values = new ContentValues();
        values.put(FanReaderContract.FanEntry.COLUMN_NAME_MAC, mac);
        values.put(FanReaderContract.FanEntry.COLUMN_NAME_NAME, name);
        return db.insert(FanReaderContract.FanEntry.TABLE_NAME, null, values);
    }



    public List<Fan>  read(){
        Cursor cursor = db.query(
                FanReaderContract.FanEntry.TABLE_NAME,                     // The table to query
                null,                               // The columns to return
                null,                                // The columns for the WHERE clause
                null,                            // The values for the WHERE clause
                null,                                     // don't group the rows
                null,                                     // don't filter by row groups
                null                                 // The sort order
        );

        List<Fan> result = new ArrayList<>();
        while(cursor.moveToNext()) {
            String mac = cursor.getString(cursor.getColumnIndexOrThrow(FanReaderContract.FanEntry.COLUMN_NAME_MAC));
            String name = cursor.getString(cursor.getColumnIndexOrThrow(FanReaderContract.FanEntry.COLUMN_NAME_NAME));
            Fan fan = new Fan(mac,name,context);
            result.add(fan);
        }
        cursor.close();

        return result;
    }

    public void remove(String mac){
        String selection = FanReaderContract.FanEntry.COLUMN_NAME_MAC + " LIKE ?";

        String[] selectionArgs = { mac };

        db.delete(FanReaderContract.FanEntry.TABLE_NAME, selection, selectionArgs);
    }


    protected void destroy() { //TODO dont forget
        fanReaderDbHelper.close();
    }

}
