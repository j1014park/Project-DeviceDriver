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
}
