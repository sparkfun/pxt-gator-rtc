/**
* Lori Crotser @ SparkFun Electronics
* September 8, 2022

* Development environment specifics:
* Written in Microsoft Makecode
* Tested with a SparkFun gatorRTC sensor and micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.

*/

/**
 * Functions to operate the gatorRTC sensor
 */

serial.redirectToUSB()
basic.pause(1000)
serial.writeLine("Setting Date to: Thursday, September-5-2019")
gatorRTC.setDate(
dayNames.Thursday,
Months.September,
5,
19
)
serial.writeLine("Setting Time to: 3:30:00 PM")
serial.writeLine("")
gatorRTC.set12Time(
3,
30,
0,
Afternoon.PM
)
serial.writeLine("Resolution of RTC (1.5 sec. delays):")
for (let index = 0; index < 10; index++) {
    serial.writeNumber(gatorRTC.timeComponent(TimeType.Weekday))
    serial.writeString(" = ")
    serial.writeString(gatorRTC.weekdayName())
    serial.writeString(" ")
    serial.writeLine(gatorRTC.get8601Time())
    basic.pause(1500)
}
serial.writeLine("")
serial.writeLine("Resolution of RTC (0.8 sec. delays):")
gatorRTC.setTimeComponent(TimeType.Seconds, 0)
for (let index = 0; index < 10; index++) {
    serial.writeLine(gatorRTC.time())
    basic.pause(800)
}
serial.writeLine("")
serial.writeLine("Test timestamp button:")
basic.forever(function () {
    serial.writeString("Current Time = ")
    serial.writeString(gatorRTC.time())
    serial.writeString(" Last Timestamp = ")
    serial.writeLine(gatorRTC.timestamp())
})
