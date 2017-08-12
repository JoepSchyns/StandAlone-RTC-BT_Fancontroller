# StandAlone_RTC_BT_Fancontroller
Stand-alone fan controller with realtime clock and adjustable via bluetooth


## Commands:
### Time
set the date
* setTime{YEAR}:{MONTH}:{DAY}:{HOUR}:{MINUTE}:{SECOND}

get the time
* getTime

### Fan Timers
turn on or off the fan on a day of the week on a specific time
* setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:on
* setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:off

turn on or off the fan on a specific time
* SetFan{HOUR}:{MINUTE}:{SECOND}:on
* SetFan{HOUR}:{MINUTE}:{SECOND}:off


get the current set fan timers 
 * getFans 
