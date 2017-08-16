# StandAlone_RTC_BT_Fancontroller
Stand-alone fan controller with realtime clock and adjustable via bluetooth


## Commands:
Replace {TEXT} by the desired input
### Time
Set the date
* setTime{YEAR}:{MONTH}:{DAY}:{HOUR}:{MINUTE}:{SECOND}

Get the time
* getTime

### Fan Timers
Turn on or off the fan on a day of the week on a specific time
* setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:on
* setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:off

Turn on or off the fan on a specific time
* SetFan{HOUR}:{MINUTE}:{SECOND}:on
* SetFan{HOUR}:{MINUTE}:{SECOND}:off

Remove fan timer
* removeFan{ID}

Get the current set fan timers in format:  ID TIME TYPE
 * getFans 
