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
 * Functions to operate the gatorlog sensor
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

//% color=#f44242 
//% icon="\uf0ce"
namespace gatorRTC {
	
	/**
	* Sets the RTC to the time on the compiler. Make sure you recompile your code if you are using this function to set your time.
	*/
	//% weight=50
	//% blockId="gatorRTC_setToCompilerTime"
	//% block="Set time on RTC to the time in the MakeCode compiler"
	//% shim=gatorRTC::setToCompilerTime
	export function setToCompilerTime(){
		return
	}
	
	/**
	* Set RTC time in HH:MM:SS format
	*/
	//% weight=49
	//% blockId="gatorRTC_setTime"
	//% block="Set time to %hours | : %minutes | : %seconds"
	//% shim=gatorRTC::setTime
	export function setTime(hours: number, minutes: number, seconds: number){
		return
	}
	
	/**
	* Set RTC Date in MM-DD-YYYY format
	*/
	//% weight=48
	//% blockId="gatorRTC_setDate"
	//% block="Set date to %month | : %day | : %year"
	//% shim=gatorRTC::setDate
	export function setDate(month: Months, day: number, year: number){
		return
	}
	
	/**
	* Set's one component of the time on the RTC. Select which component you would like to set from the drop down.
	*/
	//% weight=47
	//% blockId="gatorRTC_setTimeComponent"
	//% block="Set %timeComponent | to %value"
	//% shim=gatorRTC::setTimeComponent
	export function setTimeComponent(timeComponent: TimeType, value: number){
		return
	}
	
	/**
	* Get RTC time in HH:MM:SS format
	*/
	//% weight=46
	//% blockId="gatorRTC_getTime"
	//% block="Time in HH:MM:SS"
	//% shim=gatorRTC::getTime
	export function getTime(): string{
		return "10:10:10"
	}
	
	/**
	* Get RTC Timestamp in yyyy-mm-ddThh:mm:ss format. This is the ISO8601 standard timestamp format.
	*/
	//% weight=45
	//% blockId="gatorRTC_getTimeStamp"
	//% block="Timestamp in yyyy-mm-ddThh:mm:ss"
	//% shim=gatorRTC::getTimeStamp
	export function getTimeStamp(): string{
		return "1995-05-2110:10:10"
	}
	
	/**
	* Get RTC date in mm-dd-yyyy
	*/
	//% weight=44
	//% blockId="gatorRTC_getDateUSA"
	//% block="Date in mm-dd-yyyy"
	//% shim=gatorRTC::getDateUSA
	export function getDateUSA(): string{
		return "05-21-1995"
	}
	
	/**
	* Get RTC date in dd-mm-yyyy
	*/
	//% weight=43
	//% blockId="gatorRTC_getDate"
	//% block="Date in mm-dd-yyyy"
	//% shim=gatorRTC::getDate
	export function getDate(): string{
		return "21-05-1995"
	}
	
	/**
	* Get's one component of the time on the RTC. Select which component you would like to get from the drop down.
	*/
	//% weight=42
	//% blockId="gatorRTC_getTimeComponent"
	//% block="Value of %timeComponent"
	//% shim=gatorRTC::getTimeComponent
	export function getTimeComponent(timeComponent: TimeType): number{
		return 0
	}
}