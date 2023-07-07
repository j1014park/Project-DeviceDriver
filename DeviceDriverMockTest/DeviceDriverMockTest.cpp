#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include <vector>

using namespace testing;
using namespace std;



class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
	
};


TEST(FlashMockInjectionTest, readNornalTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(1L)).WillRepeatedly(Return(1));
	
	DeviceDriver driver(&flash_mock);
	EXPECT_THAT(1, Eq(driver.read(1L)));
}


TEST(FlashMockInjectionTest, readException)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(1L))
	.WillOnce(Return(0x2)).WillRepeatedly(Return(1));

	DeviceDriver driver(&flash_mock);
	EXPECT_THROW(driver.read(0x1), ReadFailException);
}