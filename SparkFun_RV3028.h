/******************************************************************************
SparkFun_RV3028.h
RV3028 Arduino Library
Andy England @ SparkFun Electronics
February 5, 2018
https://github.com/sparkfun/Qwiic_RTC

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#ifndef __MBED_H_
#define __MBED_H_
#include "mbed.h"
#endif

//The 7-bit I2C address of the RV3028
#define RV3028_ADDR						0b10100100

//The upper part of the part number is always 0x18
#define RV3028_PART_NUMBER_UPPER		0x18

//Possible CONFKEY Values
#define RV3028_CONF_RST					0x3C //value written to Configuration Key for reset
#define RV3028_CONF_OSC					0xA1 //value written to Configuration Key for oscillator control register write enable
#define RV3028_CONF_WRT					0x9D //value written to Configuration Key to enable write of trickle charge, BREF, CAPRC, IO Batmode, and Output Control Registers

//Bits in Control1 Register
#define CTRL1_STOP	7
#define CTRL1_PSWB	5
#define CTRL1_ARST						1 << 2 //Enables reset of interrupt flags in status register 

#define CTRL2_TSE						7		//Time stamp enable bit
#define CTRL2_12_24						1

#define EVENT_CTRL_ET					4	//Event filtering time setting
#define EVENT_CTRL_TSOW					1	//Time stamp overwrite, 0 here means first event stays in timestamp until reset. 1 means last event will overwrite TS registers

//Bits in Hours register
#define HOURS_AM_PM						5

//Interrupt Enable Bits
#define INTERRUPT_BLIE	4
#define INTERRUPT_TIE	3
#define INTERRUPT_AIE	2
#define INTERRUPT_EIE	1


//PSW Pin Function Selection Bits
#define PSWS_OFFSET     2
#define PSWS_INV_IRQ    0b000
#define PSWS_SQW        0b001
#define PSWS_INV_AIRQ   0b011
#define PSWS_TIRQ       0b100
#define PSWS_INV_TIRQ   0b101
#define PSWS_SLEEP      0b110
#define PSWS_STATIC     0b111

//Countdown Timer Control
#define COUNTDOWN_SECONDS		0b10
#define COUNTDOWN_MINUTES		0b11
#define CTDWN_TMR_TE_OFFSET		7
#define CTDWN_TMR_TM_OFFSET		6
#define CTDWN_TMR_TRPT_OFFSET	5


//Status Bits
#define STATUS_CB	7
#define STATUS_BAT 6
#define STATUS_WDF 5
#define STATUS_BLF 4
#define STATUS_TF 3
#define STATUS_AF 2
#define STATUS_EVF 1

//Reference Voltage
#define TWO_FIVE						0x70
#define TWO_ONE							0xB0
#define ONE_EIGHT						0xD0
#define ONE_FOUR						0xF0

//Register names:
#define RV3028_SECONDS					0x00
#define RV3028_MINUTES					0x01
#define RV3028_HOURS					0x02
#define RV3028_WEEKDAYS					0x03
#define RV3028_DATE         			0x04
#define RV3028_MONTHS        			0x05
#define RV3028_YEARS        			0x06
#define RV3028_MINUTES_ALM     			0x07
#define RV3028_HOURS_ALM       			0x08
#define RV3028_WEEKDAYS_ALM    			0x09
#define RV3028_DATE_ALM					0x09
#define RV3028_TIMER_0					0x0A
#define RV3028_TIMER_1					0x0B
#define RV3028_TIMER_STATUS_0			0x0C
#define RV3028_TIMER_STATUS_1			0x0D
#define RV3028_STATUS					0x0E
#define RV3028_CTRL1					0x0F
#define RV3028_CTRL2					0x10
#define RV3028_GP_BITS					0x11
#define RV3028_INT_MASK					0x12
#define RV3028_EVENT_CTRL				0x13
#define RV3028_COUNT_TS					0x14
#define RV3028_SECONDS_TS				0x15
#define RV3028_MINUTES_TS				0x16
#define RV3028_HOURS_TS					0x17
#define RV3028_DATE_TS					0x18
#define RV3028_MONTH_TS					0x19
#define RV3028_YEAR_TS					0x1A
#define RV3028_UNIX_TIME_0				0x1B
#define RV3028_UNIX_TIME_1				0x1C
#define RV3028_UNIX_TIME_2				0x1D
#define RV3028_UNIX_TIME_3				0x1E
#define RV3028_USER_RAM_1				0x1F
#define RV3028_USER_RAM_2				0x20
#define RV3028_PASSWORD_0				0x21
#define RV3028_PASSWORD_1				0x22
#define RV3028_PASSWORD_2				0x23
#define RV3028_PASSWORD_3				0x24
#define RV3028_EEPROM_ADDR				0x25
#define RV3028_EEPROM_DATA				0x26
#define RV3028_EEPROM_CMD				0x27
#define RV3028_ID						0x28

class RV3028
{
  public:
	
    RV3028( void );

	bool setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
	bool setTime(uint8_t * time, uint8_t len);
	void setSeconds(uint8_t value);
	void setMinutes(uint8_t value);
	void setHours(uint8_t value);
	void setDate(uint8_t value);
	void setWeekday(uint8_t value);
	void setMonth(uint8_t value);
	void setYear(uint8_t value);
	
	void initializeTimestamping();
	
	void updateTime(); //Update the local array with the RTC registers
	bool updateTimestamp(); //Update the local array with the RTC registers
	
	uint8_t getSeconds();
	uint8_t getMinutes();
	uint8_t getHours();
	uint8_t getDate();
	uint8_t getWeekday();
	uint8_t getMonth();
	uint8_t getYear();
	
	uint8_t getSecondsTimestamp();
	uint8_t getMinutesTimestamp();
	uint8_t getHoursTimestamp();
	uint8_t getDateTimestamp();
	uint8_t getMonthTimestamp();
	uint8_t getYearTimestamp();	
	
	bool is12Hour(); //Returns true if 12hour bit is set
	bool isPM(); //Returns true if is12Hour and PM bit is set
	void set12Hour();
	void set24Hour();
	
	uint8_t status(); //Returns the status byte
	
	//Values in RTC are stored in Binary Coded Decimal. These functions convert to/from Decimal
	uint8_t BCDtoDEC(uint8_t val); 
	uint8_t DECtoBCD(uint8_t val);

	void reset(void); //Fully reset RTC to all zeroes
	
    uint8_t readRegister(uint8_t addr);
    void writeRegister(uint8_t addr, uint8_t val);
	void readMultipleRegisters(uint8_t addr, uint8_t * dest, uint8_t len);
	void writeMultipleRegisters(uint8_t addr, uint8_t * values, uint8_t len);
	
	private:
	uint8_t _tsCount = 0;
	uint8_t _previousTsCount = 0;
	bool _timestampInitialized = false;
};