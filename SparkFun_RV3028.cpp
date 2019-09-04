/******************************************************************************
SparkFun_RV3028.h
RV3028 Arduino Library
Andy England @ SparkFun Electronics
February 5, 2018
https://github.com/sparkfun/Qwiic_RTC

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFun_RV3028.h"

#ifndef __MICROBIT_H_
#define __MICROBIT_H_
#include "MicroBit.h"
#endif

#define TIME_ARRAY_LENGTH 7
#define TIMESTAMP_ARRAY_LENGTH 6 // Total number of writable values in device

static MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);

enum time_order {
	TIME_SECONDS,    // 0
	TIME_MINUTES,    // 1
	TIME_HOURS,      // 2
	TIME_DAY,
	TIME_DATE,       // 3
	TIME_MONTH,      // 4
	TIME_YEAR,       // 5
};

uint8_t _time[TIME_ARRAY_LENGTH];
uint8_t _timestamp[TIMESTAMP_ARRAY_LENGTH];

//Configure RTC to output 1-12 hours
//Converts any current hour setting to 12 hour
void RV3028::set12Hour()
{
	//Set the 12/24 hour bit
	uint8_t setting = readRegister(RV3028_CTRL2);
	setting |= (1<<CTRL2_12_24);
	writeRegister(RV3028_CTRL2, setting);
}

//Configure RTC to output 0-23 hours
//Converts any current hour setting to 24 hour
void RV3028::set24Hour()
{
	//Change to 24 hour mode
	uint8_t setting = readRegister(RV3028_CTRL2);
	setting &= ~(1<<CTRL2_12_24); //Clear the 12/24 hr bit
	writeRegister(RV3028_CTRL2, setting);
}

//Returns true if RTC has been configured for 12 hour mode
bool RV3028::is12Hour()
{
	uint8_t controlRegister = readRegister(RV3028_CTRL2);
	return(controlRegister & (1<<CTRL2_12_24));
}

//Returns true if RTC has PM bit set and 12Hour bit set
bool RV3028::isPM()
{
	return readRegister(RV3028_HOURS) & (1<<HOURS_AM_PM);
}

//Returns the status byte. This likely clears the interrupts as well.
//See .begin() for ARST bit setting
uint8_t RV3028::status(void)
{
	return(readRegister(RV3028_STATUS));
}

bool RV3028::setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
	_time[TIME_SECONDS] = DECtoBCD(sec);
	_time[TIME_MINUTES] = DECtoBCD(min);
	_time[TIME_HOURS] = DECtoBCD(hour);
	_time[TIME_DATE] = DECtoBCD(date);
	_time[TIME_DAY] = DECtoBCD(day);
	_time[TIME_MONTH] = DECtoBCD(month);
	_time[TIME_YEAR] = DECtoBCD(year);
		
	return setTime(_time, TIME_ARRAY_LENGTH);
}

// setTime -- Set time and date/day registers of RV3028 (using data array)
bool RV3028::setTime(uint8_t * time, uint8_t len)
{
	if (len != TIME_ARRAY_LENGTH)
		return false;
	
	writeMultipleRegisters(RV3028_SECONDS, time, len);
}

void RV3028::setSeconds(uint8_t value)
{
	writeRegister(RV3028_SECONDS, DECtoBCD(value));
}

void RV3028::setMinutes(uint8_t value)
{
	writeRegister(RV3028_MINUTES, DECtoBCD(value));
}

void RV3028::setHours(uint8_t value)
{
	writeRegister(RV3028_HOURS, DECtoBCD(value));
}

void RV3028::setDate(uint8_t value)
{
	writeRegister(RV3028_DATE, DECtoBCD(value));
}

void RV3028::setMonth(uint8_t value)
{
	writeRegister(RV3028_MONTHS, DECtoBCD(value));
}

void RV3028::setYear(uint8_t value)
{
	writeRegister(RV3028_YEARS, DECtoBCD(value));
}

void RV3028::setWeekday(uint8_t value)
{
	writeRegister(RV3028_WEEKDAYS, DECtoBCD(value));
}

void RV3028::initializeTimestamping()
{
	if (_timestampInitialized == false)
	{
		uint8_t setting = readRegister(RV3028_CTRL2);
		setting |= (1<<CTRL2_TSE); //Set timestamp to trigger on button
		writeRegister(RV3028_CTRL2, setting);
		setting = readRegister(RV3028_EVENT_CTRL);
		setting |= (0b01<<EVENT_CTRL_ET); //Set read of EVI pin to a 3.9 ms sampling period to debounce the switch
		setting |= (1<<EVENT_CTRL_TSOW); //Set TSOW so that we overwrite the TS register with each new button press
		writeRegister(RV3028_EVENT_CTRL, setting);
		_timestampInitialized = true;
	}
}

//Move the hours, mins, sec, etc registers from RV-3028 into the _time array
//Needs to be called before printing time or date
//We do not protect the GPx registers. They will be overwritten. The user has plenty of RAM if they need it.
void RV3028::updateTime()
{
	readMultipleRegisters(RV3028_SECONDS, _time, TIME_ARRAY_LENGTH);
	
	if(is12Hour()) _time[TIME_HOURS] &= ~(1<<HOURS_AM_PM); //Remove this bit from value
}

bool RV3028::updateTimestamp()
{
	initializeTimestamping();
	bool newStamp = false;
	_tsCount = readRegister(RV3028_COUNT_TS);
	if (_tsCount != _previousTsCount)
	{
		newStamp = true;
		readMultipleRegisters(RV3028_SECONDS_TS, _timestamp, TIMESTAMP_ARRAY_LENGTH);
		if(is12Hour()) _timestamp[TIME_HOURS] &= ~(1<<HOURS_AM_PM); //Remove this bit from value
	}
	_previousTsCount = _tsCount;
	return newStamp;
}

uint8_t RV3028::getSeconds()
{
	return BCDtoDEC(_time[TIME_SECONDS]);
}

uint8_t RV3028::getMinutes()
{
	return BCDtoDEC(_time[TIME_MINUTES]);
}

uint8_t RV3028::getHours()
{
	return BCDtoDEC(_time[TIME_HOURS]);
}

uint8_t RV3028::getDate()
{
	return BCDtoDEC(_time[TIME_DATE]);
}

uint8_t RV3028::getMonth()
{
	return BCDtoDEC(_time[TIME_MONTH]);
}

uint8_t RV3028::getYear()
{
	return BCDtoDEC(_time[TIME_YEAR]);
}

uint8_t RV3028::getWeekday()
{
	return BCDtoDEC(_time[TIME_DAY]);
}

uint8_t RV3028::getSecondsTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_SECONDS]);
}

uint8_t RV3028::getMinutesTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_MINUTES]);
}

uint8_t RV3028::getHoursTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_HOURS]);
}

uint8_t RV3028::getDateTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_DATE - 1]); //Subtract one due to lack of weekday register in timestamp
}

uint8_t RV3028::getMonthTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_MONTH - 1]); //Subtract one due to lack of weekday register in timestamp
}

uint8_t RV3028::getYearTimestamp()
{
	return BCDtoDEC(_timestamp[TIME_YEAR - 1]); //Subtract one due to lack of weekday register in timestamp
}

uint8_t RV3028::BCDtoDEC(uint8_t val)
{
	return ( ( val / 0x10) * 10 ) + ( val % 0x10 );
}

// BCDtoDEC -- convert decimal to binary-coded decimal (BCD)
uint8_t RV3028::DECtoBCD(uint8_t val)
{
	return ( ( val / 10 ) * 0x10 ) + ( val % 10 );
}

uint8_t RV3028::readRegister(uint8_t addr)
{
	return i2c.readRegister(RV3028_ADDR, addr);
}

void RV3028::writeRegister(uint8_t addr, uint8_t val)
{
	i2c.writeRegister(RV3028_ADDR, addr, val);
}

void RV3028::writeMultipleRegisters(uint8_t addr, uint8_t * values, uint8_t length)
{
	uint8_t realLength = length + 1;
	char temp[realLength];
	temp[0] = addr;
	memcpy(&temp[1], values, length); //tempLong is 4 bytes, we only need 3
	i2c.write(RV3028_ADDR, temp, realLength);
}

void RV3028::readMultipleRegisters(uint8_t addr, uint8_t * dest, uint8_t len)
{
	i2c.readRegister(RV3028_ADDR, addr, dest, len);
}
