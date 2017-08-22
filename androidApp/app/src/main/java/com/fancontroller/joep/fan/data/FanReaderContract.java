package com.fancontroller.joep.fan.data;

import android.provider.BaseColumns;

/**
 * Created by Joep on 22/08/2017.
 */

public class FanReaderContract {
    private FanReaderContract() {}

    /* Inner class that defines the table contents */
    public static class FanEntry implements BaseColumns {
        public static final String TABLE_NAME = "fans";
        public static final String COLUMN_NAME_MAC = "mac";
        public static final String COLUMN_NAME_NAME = "name";


    }
}
