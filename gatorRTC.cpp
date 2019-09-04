/**
* Andy England @ SparkFun Electronics
* September 6, 2018
* https://github.com/sparkfun/pxt-light-bit
*
* Development environment specifics:
* Written in Microsoft PXT
* Tested with a SparkFun temt6000 sensor and micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


#include "pxt.h"
#include <cstdint>
#include <math.h>
#include "SparkFun_RV3028.h"


using namespace pxt;

namespace gatorRTC {
	MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);
	RV3028 *rtc; //BME280 handles our Temp, pressure, and humidity
	
	//%
	void set24Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
	{
		rtc->set24Hour();
		rtc->setHours(hours);
		rtc->setMinutes(minutes);
		rtc->setSeconds(seconds);	
	}
	
	//%
	void set12Time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t amPm)
	{
		rtc->set24Hour();
		rtc->setHours(hours + (amPm * 12));
		rtc->setMinutes(minutes);
		rtc->setSeconds(seconds);	
		rtc->set12Hour();
	}
	
	//%
	void set12HourMode()
	{
		rtc->set12Hour();
	}
	
	//%
	void set24HourMode()
	{
		rtc->set24Hour();
	}
	
	//%
	bool is12HourMode()
	{
		return rtc->is12Hour();
	}
	
	//%
	bool isAfternoon()
	{
		return rtc->isPM();
	}
	
	//%
	void setDate(uint8_t weekday, uint8_t month, uint8_t day, uint8_t year)
	{
		rtc->setWeekday(weekday);
		rtc->setMonth(month);	
		rtc->setDate(day);	
		rtc->setYear(year);	
	}
	
	//%
	void setTimeComponent(uint8_t timeComponent, uint8_t value)
	{
		switch (timeComponent)
		{
			case 1:
				rtc->setSeconds(value);
				break;
			case 2:
				rtc->setMinutes(value);
				break;
			case 3:
				rtc->setHours(value);
				break;
			case 4:
				rtc->setDate(value);
				break;
			case 5:
				rtc->setMonth(value);
				break;
			case 6:
				rtc->setYear(value);
				break;
			case 7:
				rtc->setWeekday(value);
				break;
		}	
	}
	
	//%
	uint16_t getTimeComponent(uint8_t timeComponent)
	{
		rtc->updateTime();
		uint16_t returnValue;
		switch (timeComponent)
		{
			case 1:
				returnValue = rtc->getSeconds();
				break;
			case 2:
				returnValue = rtc->getMinutes();
				break;
			case 3:
				returnValue = rtc->getHours();
				break;
			case 4:
				returnValue = rtc->getDate();
				break;
			case 5:
				returnValue = rtc->getMonth();
				break;
			case 6:
				returnValue = rtc->getYear();
				break;
			case 7:
				returnValue = rtc->getWeekday();
				break;
			default:
				returnValue = 0;
				break;
		}
		return returnValue;
	}
	
	//%
	uint16_t getTimestampComponent(uint8_t timeComponent)
	{
		if (rtc->updateTimestamp())
		{
			uint16_t returnValue;
			switch (timeComponent)
			{
				case 1:
					returnValue = rtc->getSecondsTimestamp();
					break;
				case 2:
					returnValue = rtc->getMinutesTimestamp();
					break;
				case 3:
					returnValue = rtc->getHoursTimestamp();
					break;
				case 4:
					returnValue = rtc->getDateTimestamp();
					break;
				case 5:
					returnValue = rtc->getMonthTimestamp();
					break;
				case 6:
					returnValue = rtc->getYearTimestamp();
					break;
				default:
					returnValue = 0;
					break;
			}
			return returnValue;
		}
		else
		{
			return 0;
		}
	}
}