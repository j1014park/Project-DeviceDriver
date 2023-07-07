#include "Application.h"

#include <string>

string Application::ReadAndPrint(long startAddr, long endAddr)
{
	string result;
	for (long addr = startAddr; addr <= endAddr; ++addr)
	{
		try
		{
			result += std::to_string(driver->read(addr));
			result += ",";
		}
		catch (ReadFailException e)
		{
			throw ReadFailException(to_string(addr).c_str());
		}
	}
	return result;
}

void Application::WriteAll(int value)
{
	for (long addr = 0; addr <= 4; ++addr)
	{
		try
		{
			driver->write(addr, value);
		}
		catch (WriteFailException e)
		{
			throw WriteFailException(to_string(addr).c_str());
		}
	}
}
