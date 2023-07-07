#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}


int DeviceDriver::read(long address)
{
	int result = (int)(m_hardware->read(address));
	for (int repeat = 0; repeat < 4; ++repeat)
	{
		if (result != (int)(m_hardware->read(address))) 
			throw ReadFailException("ReadError");
	}
	return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}