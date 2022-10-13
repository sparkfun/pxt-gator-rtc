
#include "pxt.h"
#include <cstdint>
#include <math.h>
#include "SparkFun_RV3028.h"


using namespace pxt;

namespace gatorRTC {
	
	RV3028 *rtc = NULL;

	void init() {
		if ( rtc == NULL) {
			rtc = new RV3028;
		}
	}
	
	//%
	void set24Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
	{
		init();
		rtc->set24Hour();
		rtc->setHours(hours);
		rtc->setMinutes(minutes);
		rtc->setSeconds(seconds);	
	}
	
	//%
	void set12Time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t amPm)
	{
		init();
		rtc->set24Hour();
		rtc->setHours(hours + (amPm * 12));
		rtc->setMinutes(minutes);
		rtc->setSeconds(seconds);	
		rtc->set12Hour();
	}
	
	//%
	void set12HourMode()
	{
		init();
		rtc->set12Hour();
	}
	
	//%
	void set24HourMode()
	{
		init();
		rtc->set24Hour();
	}
	
	//%
	bool is12HourMode()
	{
		init();
		return rtc->is12Hour();
	}
	
	//%
	bool isAfternoon()
	{
		init();
		return rtc->isPM();
	}
	
	//%
	void setDate(uint8_t weekday, uint8_t month, uint8_t day, uint8_t year)
	{
		init();
		rtc->setWeekday(weekday);
		rtc->setMonth(month);	
		rtc->setDate(day);	
		rtc->setYear(year);	
	}
	
	//%
	void setTimeComponent(uint8_t timeComponent, uint8_t value)
	{
		init();
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
	uint16_t timeComponent(uint8_t timeComponent)
	{
		init();
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
	uint16_t timestampComponent(uint8_t timeComponent)
	{
		init();

		rtc->updateTimestamp();
		
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
}