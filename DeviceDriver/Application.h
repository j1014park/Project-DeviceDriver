#pragma once
#include "DeviceDriver.h"


class Application
{
public:
	explicit Application(DeviceDriver* driver)
		: driver(driver) {}

	string ReadAndPrint(long startAddr, long endAddr);
	void WriteAll(int value);
private:
	DeviceDriver* driver;
};
