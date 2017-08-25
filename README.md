# StandAlone_RTC_BT_Fancontroller
Stand-alone fan controller with realtime clock and adjustable via bluetooth


## Commands:
Replace {TEXT} by the desired input

### Manual Control
Turn the fan on
* **fanOn**   Return format: fanOn+OK

Turn the fan off
* **fanOff**    Return format: fanOff+OK

Check weither the fan is on
* **getFanOn**    Return format getFanOn{0/1}

### Time
Set the date
* **setTime{YEAR}:{MONTH}:{DAY}:{HOUR}:{MINUTE}:{SECOND}**     Return format: Date {YEAR}/{MONTH}/{DAY} {HOUR}:{MINUTE}:{SECOND}

Get the time
* **getTime**   Return format: Date {YEAR}/{MONTH}/{DAY} {HOUR}:{MINUTE}:{SECOND}

### Fan Timers
Set the fan speed (between 0 and 255) on a day of the week on a specific time
* **setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:{SPEED}**    Return format: setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:{SPEED}


Set the fan speed (between 0 and 255) of the fan on a specific time
* **SetFan{HOUR}:{MINUTE}:{SECOND}:{SPEED}**    Return format: setFan{DAY}:{HOUR}:{MINUTE}:{SECOND}:{SPEED}

Remove fan timer
* **removeFan{ID}**   Return format: removeFan{ID}+OK

Remove all fan timers
* **removeFans**    Return format: removeFans+OK

Get the current set fan timer     
 * **getFans**    Return format: getFanTimer+{ID};{TYPE};{HOUR:MINUTE:SECOND};{SPEED}
 
 Get Max amount of fan Timer
 * **maxFans**    Return format: maxFans+{AMOUNT}
 
 Get amount of current set Timers
 * **amountFans**   Return format: amountFans{AMOUNT}

### Settings
Get All settings
* **getInfo**   Return format: all of the above get commands   
