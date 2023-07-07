#pragma once
#include "FlashMemoryDevice.h"

using namespace std;


class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public exception
{
public:
	explicit ReadFailException(char const* _Message)
		: exception(_Message)
	{
	}

};

class WriteFailException : public exception
{
public:
	explicit WriteFailException(char const* _Message)
		: exception(_Message)
	{
	}
};
