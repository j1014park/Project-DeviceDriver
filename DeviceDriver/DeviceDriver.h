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
    ReadFailException(const char* str) {}
};

class WriteFailException : public exception
{
public:
    WriteFailException(const char* str) {}
};
