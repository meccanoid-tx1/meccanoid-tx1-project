/*
  MD23.h - Library for interfacing Devantech MD23 Dual 12Volt 3Amp H Bridge Motor Drive 
  Technical reference: http://www.robot-electronics.co.uk/htm/md23tech.htm
  Created by Nicola Lugato, September 2008.
  Contacts: nicola.lugato@gmail.com

  Released into the public domain.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "Wire.h"
#include "MD23.h"
#include "Arduino.h"

#define DEF_ADDRESS (0xB0 >> 1)

#define SPEED_1_REGISTER 0
#define SPEED_2_REGISTER 1

#define ENC_1_A_REGISTER 2
#define ENC_2_A_REGISTER 6

#define BATTERY_VOLTS_REGISTER 10
#define MOTOR_1_CURRENT_REGISTER 11
#define MOTOR_2_CURRENT_REGISTER 12
#define SOFTWARE_REVISION_REGISTER 13
#define ACCELERATION_RATE_REGISTER 14
#define MODE_REGISTER 15
#define COMMAND_REGISTER 16

MD23::MD23(uint8_t address)
{
	// store i2c address
  _address = address;
}

MD23::MD23()
{
	// use i2c default address
  _address = DEF_ADDRESS;
}

void MD23::writeRegisterByte(uint8_t reg, uint8_t value)
{
	// write a value to a specified register
  Wire.beginTransmission(_address);
  Wire.write(reg); // choose register
  Wire.write(value); // send value
  Wire.endTransmission();
}

uint8_t MD23::readRegisterByte(uint8_t reg)
{
  uint8_t data = -1;
  // to read a register, we actually write which register we want to read
  Wire.beginTransmission(_address);
  Wire.write(reg); // choose register
  Wire.endTransmission();
  // now request a uint8_t from it. MD23 always reply with a single uint8_t
  Wire.requestFrom(_address, 1);

  if (Wire.available()) 
  {
    data = Wire.read();
  }
 
  return data;
}

long MD23::getEncoder1()
{
	// read a 32bit long value containing the encoder reading.
	// the reading of the highest uint8_t capture the value.
	long first = readRegisterByte(ENC_1_A_REGISTER);
	
	return (first << 24) || 
         (((long)readRegisterByte(ENC_1_A_REGISTER+1)) << 16) ||
         (((long)readRegisterByte(ENC_1_A_REGISTER+2)) << 8) ||
         (((long)readRegisterByte(ENC_1_A_REGISTER+3)) );
}

long MD23::getEncoder2()
{
	// read a 32bit long value containing the encoder reading.
	// the reading of the highest uint8_t capture the value.
	long first = readRegisterByte(ENC_2_A_REGISTER);
	
	return (first << 24) || 
         (((long)readRegisterByte(ENC_2_A_REGISTER+1)) << 16) ||
         (((long)readRegisterByte(ENC_2_A_REGISTER+2)) << 8) ||
         (((long)readRegisterByte(ENC_2_A_REGISTER+3)) );
}

uint8_t MD23::getBatteryVolts()
{
	// read battery voltage, return 10 times the voltage (121 for 12.1 V).
	return readRegisterByte(BATTERY_VOLTS_REGISTER);
}

uint8_t MD23::getAccelerationRate()
{
		return readRegisterByte(ACCELERATION_RATE_REGISTER);
}
void MD23::setAccelerationRate(uint8_t value)
{
  writeRegisterByte(ACCELERATION_RATE_REGISTER, value);
}

uint8_t MD23::getMotor1Speed()
{
		return readRegisterByte(SPEED_1_REGISTER);
}
void MD23::setMotor1Speed(uint8_t speed)
{
  writeRegisterByte(SPEED_1_REGISTER, speed);
}

uint8_t MD23::getMotor2Speed()
{
		return readRegisterByte(SPEED_2_REGISTER);
}
void MD23::setMotor2Speed(uint8_t speed)
{
  writeRegisterByte(SPEED_2_REGISTER, speed);
}

uint8_t MD23::getMotor1Current()
{
	// returns 10 times the amperes for the motor (25 at 2.5A).	
	return readRegisterByte(MOTOR_1_CURRENT_REGISTER);
}
uint8_t MD23::getMotor2Current()
{
		return readRegisterByte(MOTOR_2_CURRENT_REGISTER);
}
uint8_t MD23::getSoftwareRevision()
{
		return readRegisterByte(SOFTWARE_REVISION_REGISTER);
}

void MD23::setMode(uint8_t mode)
{
  writeRegisterByte(MODE_REGISTER, mode);
}
uint8_t MD23::getMode()
{
	return readRegisterByte(MODE_REGISTER);
}
void MD23::sendCommand(uint8_t cmd)
{
  writeRegisterByte(COMMAND_REGISTER, cmd);
}

void MD23::enableSpeedRegulation()
{
  sendCommand(0x31);
}
void MD23::disableSpeedRegulation()
{
  sendCommand(0x30);
}
void MD23::resetEncoders()
{
  sendCommand(0x20);
}
void MD23::changeAddress(uint8_t newAddress)
{
  sendCommand(0xA0);
  delay(6);
  sendCommand(0xAA);
  delay(6);
  sendCommand(0xA5);
  delay(6);
  sendCommand(newAddress);
  delay(6);
}
