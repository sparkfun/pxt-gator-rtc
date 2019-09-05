# gator:rtc Real Time Clock

[![Community Discord](https://img.shields.io/discord/448979533891371018.svg)](https://aka.ms/makecodecommunity)

The gator:rtc is a gator clippable RTC based on the RV3028 by Micro Crystal. It's accurate to 1 PPM and runs at extraordinarily low power.

![SparkFun gator:light](https://raw.githubusercontent.com/sparkfun/pxt-gator-rtc/master/icon.png)  

## ~ hint

To use this package, go to https://makecode.microbit.org, click ``Add package`` and search for **gator-rtc**. The package is located [here](https://makecode.microbit.org/pkg/sparkfun/pxt-gator-rtc)

## ~

## Basic usage

```blocks
//Sets the time to whatever you choose in 12 hour mode
gatorRTC.set12Time(
    12,
    2,
    37,
    Afternoon.PM
)
```

Use ``||set time to **12:2:37-PM**||`` to set the time to 12:02:37 PM.

```blocks
//Sets the date
gatorRTC.setDate(
dayNames.Thursday,
Months.September,
5,
19
)
```

Use ``||set date to **Thursday**, **September** - "5" - 2019||`` to set the date to Thursday, September 5, 2019.

```blocks
//Sets one component of your time (in this case, seconds), selectable from a dropdown ot the value given
gatorRTC.setTimeComponent(TimeType.Seconds, 5)
```

Use ``||set **Seconds** to 5||`` to set the seconds component of your time to 5.

```blocks
//Using Serial write to write the seconds component of your timestamp
serial.writeNumber(gatorRTC.getTimeComponent(TimeType.Seconds))
```

Use ``||serial write number ||value of **Seconds**|| ||`` to write the seconds value out over serial.

```blocks
//Using Serial write to write the name of the weekday
serial.writeString(gatorRTC.getWeekdayName())
```

Use ``||serial write string ||text of weekday|| ||`` to write the day of the week out over serial.

```blocks
//Using Serial write to write the time in HH:MM:SS
serial.writeString(gatorRTC.getTime())
```

Use ``||serial write string ||time in HH:MM:SS|| ||`` to write the time in HH:MM:SS over serial

```blocks
//Using Serial write to write the date in mm-dd-yyyy
serial.writeString(gatorRTC.getDateUSA())
```

Use ``||serial write string ||date in mm-dd-yyyy|| ||`` to write the date in mm-dd-yyyy over serial

```blocks
//Using Serial write to write the timestamp in HH:MM:SS
serial.writeString(gatorRTC.getTimestamp())
```

Use ``||serial write string ||button timestamp in HH:MM:SS|| ||`` to write the button timestamp in HH:MM:SS over serial

```blocks
//Using Serial write to write the date of the timestamp in mm-dd-yyyy
serial.writeString(gatorRTC.getDateUSATimestamp())
```

Use ``||serial write string ||button timestamp date in mm-dd-yyyy|| ||`` to write the button timestamp date in mm-dd-yyyy over serial

##Advanced Blocks

```blocks
//Sets the time to whatever you choose in 24 hour mode

gatorRTC.set24Time(15, 2, 37)
```

Use ``||set time to **15:2:37**||`` to set the time to 15:02:37.

```blocks
//Using Serial write to write the time in ISO8601 format (yyyy-mm-ddThh:mm:ss)
serial.writeString(gatorRTC.get8601Time())
```

Use ``||serial write string ||time in yyyy-mm-ddThh:mm:ss|| ||`` to write the time in ISO8601 over serial

```blocks
//Using Serial write to write the date in dd-mm-yyyy
serial.writeString(gatorRTC.getDateWorld())
```

Use ``||serial write string ||date in dd-mm-yyyy|| ||`` to write the date in dd-mm-yyyy over serial

```blocks
//Using Serial write to write the timestamp in ISO8601 format (yyyy-mm-ddThh:mm:ss)
serial.writeString(gatorRTC.get8601Timestamp())
```

Use ``||serial write string ||button timestamp in yyyy-mm-ddThh:mm:ss|| ||`` to write the timestamp in ISO8601 over serial

```blocks
//Using Serial write to write the timestamp date in dd-mm-yyyy
serial.writeString(gatorRTC.getDateWorld())
```

Use ``||serial write string ||button timestamp date in dd-mm-yyyy|| ||`` to write the button timestamp date in dd-mm-yyyy over serial

```blocks
//Change between 12 and 24 hour time modes, below will change to 24 hour mode
gatorRTC.set1224Mode(TimeMode.Military)
```

Use ``||set to **Military** time||`` to write the button timestamp date in dd-mm-yyyy over serial.

## Example: Set and Read Time
```blocks
//Set the time and date, then read it out over Serial every 10 seconds
gatorRTC.setDate(
dayNames.Thursday,
Months.September,
5,
19
)
gatorRTC.set12Time(
12,
2,
37,
Afternoon.PM
)
basic.forever(function () {
    serial.writeString(gatorRTC.getWeekdayName())
    serial.writeString(", ")
    serial.writeString(gatorRTC.getDateUSA())
    serial.writeString(", ")
    serial.writeLine(gatorRTC.getTime())
    basic.pause(10000)
})
```

## Supported targets

* for PXT/microbit

## License

MIT

```package
gatorRTC=github:sparkfun/pxt-gator-rtc
```