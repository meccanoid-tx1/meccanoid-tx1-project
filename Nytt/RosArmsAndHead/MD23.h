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

#ifndef MD23_h
#define MD23_h

#include <inttypes.h>

class MD23
{
  public:
	MD23(uint8_t address);
	MD23();
    
	long getEncoder1();
	long getEncoder2();
	uint8_t getBatteryVolts();
	uint8_t getAccelerationRate();
	void setAccelerationRate(uint8_t value);
	uint8_t getMotor1Speed();
	void setMotor1Speed(uint8_t speed);
	uint8_t getMotor2Speed();
	void setMotor2Speed(uint8_t speed);
	uint8_t getMotor1Current();
	uint8_t getMotor2Current();
	uint8_t getSoftwareRevision();
	void setMode(uint8_t mode);
	uint8_t getMode();
	void enableSpeedRegulation();
	void disableSpeedRegulation();
	void resetEncoders();
	void changeAddress(uint8_t newAddress);
    
  private:
	int _address;
	void writeRegisterByte(uint8_t reg, uint8_t value);
	uint8_t readRegisterByte(uint8_t reg);
	void sendCommand(uint8_t cmd);
};

#endif

