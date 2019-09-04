/**
* Andy England @ SparkFun Electronics
* September 6, 2018
* Development environment specifics:
* Written in Microsoft Makecode
* Tested with a SparkFun gatorlog sensor and micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


/**
 * Functions to operate the gatorrtc sensor
 */

 enum TimeType{
	Seconds=1,
	Minutes=2,
	Hours=3,
	Date=4,
	Month=5,
	Year=6,
	Weekday=7
 }
 
 enum dayNames{
	Monday=0,
	Tuesday=1,
	Wednesday=2,
	Thursday=3,
	Friday=4,
	Saturday=5,
	Sunday=6
 }
 
 enum TimeStampType{
	Seconds=1,
	Minutes=2,
	Hours=3,
	Date=4,
	Month=5,
	Year=6
 }
 
 enum Months{
	January=1,
	February=2,
	March=3,
	April=4,
	May=5,
	June=6,
	July=7,
	August=8,
	September=9,
	October=10,
	November=11,
	December=12,
 }
 
 enum TimeMode{
	 Military=0,
	 Standard=1
 }
 
 enum Afternoon{
	AM=0,
	PM=1
 }

//% color=#f44242 
//% icon="\uf017"
namespace gatorRTC {
	// Functions for reading and setting time on the gator:RTC
	
	/**
	* Set RTC time in HH:MM:SS in 12 hour format format
	*/
	//% weight=49
	//% blockId="gatorRTC_set12Time"
	//% block="set time to %hours :%minutes :%seconds -%amPm"
	//% hours.min=0 hours.max=12
	//% minutes.min=0 minutes.max=60
	//% seconds.min=0 seconds.max=60
	//% shim=gatorRTC::set12Time
	export function set12Time(hours: number, minutes: number, seconds: number, amPm: Afternoon){
		return
	}
	
	/**
	* Set RTC time in HH:MM:SS in 24 hour format
	*/
	//% weight=48
	//% blockId="gatorRTC_set24Time"
	//% block="set time to %hours | : %minutes | : %seconds in 24 hour mode"
	//% hours.min=0 hours.max=24
	//% minutes.min=0 minutes.max=60
	//% seconds.min=0 seconds.max=60
	//% shim=gatorRTC::set24Time
	//% advanced=true
	export function set24Time(hours: number, minutes: number, seconds: number){
		return
	}
	
	/**
	* Set RTC Date in MM-DD-YYYY format
	*/
	//% weight=47
	//% blockId="gatorRTC_setDate"
	//% block="set date to %weekday|, %month |-%day |-20%year"
	//% day.min=1 day.max=31
	//% year.min=0 year.max=99
	//% shim=gatorRTC::setDate
	export function setDate(weekday:dayNames, month: Months, day: number, year: number){
		return
	}
	
	/**
	* Set's one component of the time on the RTC. Select which component you would like to set from the drop down.
	*/
	//% weight=46
	//% blockId="gatorRTC_setTimeComponent"
	//% block="set %timeComponent | to %value"
	//% shim=gatorRTC::setTimeComponent
	export function setTimeComponent(timeComponent: TimeType, value: number){
		return
	}
	
	/**
	* Get's one component of the time on the RTC. Select which component you would like to get from the drop down.
	*/
	//% weight=45
	//% blockId="gatorRTC_getTimeComponent"
	//% block="value of %timeComponent"
	//% shim=gatorRTC::getTimeComponent
	export function getTimeComponent(timeComponent: TimeType): number{
		return 0
	}
	
	/**
	* Get's one component of the time on the RTC. Select which component you would like to get from the drop down.
	*/
	//% weight=44
	//% blockId="gatorRTC_getWeekdayName"
	//% block="text of weekday"
	export function getWeekdayName(): string{
		let dayString: string
		switch (getTimeComponent(TimeType.Weekday))
		{
			case 0:
				dayString = "Monday"
				break;
			case 1:
				dayString = "Tuesday"
				break;
			case 2:
				dayString = "Wednesday"
				break;
			case 3:
				dayString = "Thursday"
				break;
			case 4:
				dayString = "Friday"
				break;
			case 5:
				dayString = "Saturday"
				break;
			case 6:
				dayString = "Sunday"
				break;
		}
		return dayString
	}
	
	/**
	* Get RTC time in HH:MM:SS format
	*/
	//% weight=43
	//% blockId="gatorRTC_getTime"
	//% block="time in HH:MM:SS"
	export function getTime(): string{
		let minutes = getTimeComponent(TimeType.Minutes)
		let seconds = getTimeComponent(TimeType.Seconds)
		let minuteDelimiterString: string = ":"
		let secondDelimiterString: string = ":"
		let ampmString: string = ""
		if (minutes < 10)
		{
			minuteDelimiterString = ":0"
		}
		if (seconds < 10)
		{
			secondDelimiterString = ":0"
		}
		if (is12HourMode())
		{
			ampmString = " AM"
			if (isAfternoon())
			{
				ampmString = " PM"
			}
		}
		let timeString: string = getTimeComponent(TimeType.Hours) + minuteDelimiterString + minutes + secondDelimiterString + seconds + ampmString
		return timeString
	}
	
	/**
	* Get RTC Time in yyyy-mm-ddThh:mm:ss format. This is the ISO8601 standard timestamp format.
	*/
	//% weight=42
	//% blockId="gatorRTC_get8601Time"
	//% block="time in yyyy-mm-ddThh:mm:ss"
	//% advanced=true
	export function get8601Time(): string{
		let minutes = getTimeComponent(TimeType.Minutes)
		let seconds = getTimeComponent(TimeType.Seconds)
		let minuteDelimiterString: string = ":"
		let secondDelimiterString: string = ":"
		if (minutes < 10)
		{
			minuteDelimiterString = ":0"
		}
		if (seconds < 10)
		{
			secondDelimiterString = ":0"
		}
		let timeString: string = "20" + getTimeComponent(TimeType.Year) + "-" + getTimeComponent(TimeType.Month) + "-" + getTimeComponent(TimeType.Date) + "T" + getTimeComponent(TimeType.Hours) + minuteDelimiterString + minutes + secondDelimiterString + seconds
		return timeString
	}
	
	/**
	* Get RTC date in mm-dd-yyyy
	*/
	//% weight=41
	//% blockId="gatorRTC_getDateUSA"
	//% block="date in mm-dd-yyyy"
	export function getDateUSA(): string{
		let timeString: string = getTimeComponent(TimeType.Month) + "-" + getTimeComponent(TimeType.Date) + "-" + "20" + getTimeComponent(TimeType.Year)
		return timeString
	}
	
	/**
	* Get RTC date in dd-mm-yyyy
	*/
	//% weight=40
	//% blockId="gatorRTC_getDateWorld"
	//% block="date in dd-mm-yyyy"
	//% advanced=true
	export function getDateWorld(): string{
		let timeString: string = getTimeComponent(TimeType.Date) + "-" + getTimeComponent(TimeType.Month) + "-" + "20" + getTimeComponent(TimeType.Year)
		return timeString
	}
	
	/**
	* Get RTC timestamp from button press in HH:MM:SS format
	*/
	//% weight=39
	//% blockId="gatorRTC_getTimestamp"
	//% block="button timestamp in HH:MM:SS"
	export function getTimestamp(): string{
		let minutes = getTimestampComponent(TimeStampType.Minutes)
		let seconds = getTimestampComponent(TimeStampType.Seconds)
		let minuteDelimiterString: string = ":"
		let secondDelimiterString: string = ":"
		let ampmString: string = ""
		if (minutes < 10)
		{
			minuteDelimiterString = ":0"
		}
		if (seconds < 10)
		{
			secondDelimiterString = ":0"
		}
		if (is12HourMode())
		{
			ampmString = " AM"
			if (isAfternoon())
			{
				ampmString = " PM"
			}
		}
		let timeString: string = getTimestampComponent(TimeStampType.Hours) + minuteDelimiterString + minutes + secondDelimiterString + seconds + ampmString
		return timeString
	}
	
	/**
	* Get RTC button timestamp in yyyy-mm-ddThh:mm:ss format. This is the ISO8601 standard timestamp format.
	*/
	//% weight=38
	//% blockId="gatorRTC_get8601Timestamp"
	//% block="button timestamp in yyyy-mm-ddThh:mm:ss"
	//% advanced=true
	export function get8601Timestamp(): string{
		let minutes = getTimestampComponent(TimeStampType.Minutes)
		let seconds = getTimestampComponent(TimeStampType.Seconds)
		let minuteDelimiterString: string = ":"
		let secondDelimiterString: string = ":"
		if (minutes < 10)
		{
			minuteDelimiterString = ":0"
		}
		if (seconds < 10)
		{
			secondDelimiterString = ":0"
		}
		let timeString: string = "20" + getTimestampComponent(TimeStampType.Year) + "-" + getTimestampComponent(TimeStampType.Month) + "-" + getTimestampComponent(TimeStampType.Date) + "T" + getTimestampComponent(TimeStampType.Hours) + minuteDelimiterString + minutes + secondDelimiterString + seconds
		return timeString
	}
	
	/**
	* Get RTC button timestamp date in mm-dd-yyyy
	*/
	//% weight=37
	//% blockId="gatorRTC_getDateUSATimestamp"
	//% block="button timestamp date in mm-dd-yyyy"
	export function getDateUSATimestamp(): string{
		let timeString: string = getTimestampComponent(TimeStampType.Month) + "-" + getTimestampComponent(TimeStampType.Date) + "-" + "20" + getTimestampComponent(TimeStampType.Year)
		return timeString
	}
	
	/**
	* Get RTC button timestamp date in dd-mm-yyyy
	*/
	//% weight=36
	//% blockId="gatorRTC_getDateWorldTimestamp"
	//% block="button timestamp date in dd-mm-yyyy"
	//% advanced=true
	export function getDateWorldTimestamp(): string{
		let timeString: string = getTimestampComponent(TimeStampType.Date) + "-" + getTimestampComponent(TimeStampType.Month) + "-" + "20" + getTimestampComponent(TimeStampType.Year)
		return timeString
	}
	
	/**
	* Get's one component of the most recent button timestamp on the RTC. Select which component you would like to get from the drop down.
	*/
	//% weight=35
	//% blockId="gatorRTC_getTimestampComponent"
	//% block="value of button timestamp %timeComponent"
	//% shim=gatorRTC::getTimestampComponent
	//% advanced=true
	export function getTimestampComponent(timeComponent: TimeStampType): number{
		return 0
	}
	
	/**
	* Switch between standard (12 hour) and military (24 hour) time formats
	*/
	//% weight=34
	//% blockId="gatorgatorRTC_set1224Mode"
	//% block="set to %timeType| time"
	//% advanced=true
	export function set1224Mode(timeType: TimeMode){
		if(timeType)
		{
			set12HourMode()
		}
		else
		{
			set24HourMode()
		}
	}
	
	//% shim=gatorRTC::set12HourMode
	function set12HourMode()
	{
		return
	}
	
	//% shim=gatorRTC::set24HourMode
	function set24HourMode()
	{
		return
	}
	
	//% shim=gatorRTC::is12HourMode
	function is12HourMode(): boolean
	{
		return false
	}
	
	//% shim=gatorRTC::isAfternoon
	function isAfternoon(): boolean
	{
		return true
	}
	
	//% shim=gatorRTC::initializeTimestamp
	function initializeTimestamp()
	{
		return false
	}
}