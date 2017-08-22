package com.fancontroller.joep.fan.data;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by Joep on 22/08/2017.
 */

public class FanReaderDbHelper extends SQLiteOpenHelper {
    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "FeedReader.db";

    private static final String SQL_CREATE_ENTRIES =
            "CREATE TABLE " + FanReaderContract.FanEntry.TABLE_NAME + " (" +
                    FanReaderContract.FanEntry._ID + " INTEGER PRIMARY KEY," +
                    FanReaderContract.FanEntry.COLUMN_NAME_MAC + " TEXT," +
                    FanReaderContract.FanEntry.COLUMN_NAME_NAME + " TEXT)";

    private static final String SQL_DELETE_ENTRIES =
            "DROP TABLE IF EXISTS " + FanReaderContract.FanEntry.TABLE_NAME;

    public FanReaderDbHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(SQL_CREATE_ENTRIES);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(SQL_DELETE_ENTRIES);
        onCreate(db);
    }
    public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        onUpgrade(db, oldVersion, newVersion);
    }
}
