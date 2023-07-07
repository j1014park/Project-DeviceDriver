#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"
#include <vector>

using namespace testing;
using namespace std;



class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
	
};


TEST(FlashMockInjectionTest, readNormalTest)
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


TEST(FlashMockInjectionTest, WriteNormalTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(1L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, write(1L,100)).Times(1);
	DeviceDriver driver(&flash_mock);
	driver.write(1L, 100);
}


TEST(FlashMockInjectionTest, WriteException)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(1L)).Times(1).WillRepeatedly(Return(1));
	EXPECT_CALL(flash_mock, write(1L, 100)).Times(0);
	DeviceDriver driver(&flash_mock);
	EXPECT_THROW(driver.write(1L, 100), WriteFailException);

}

TEST(FlashMockInjectionTest, ApplicationReadTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0L)).WillRepeatedly(Return(0));
	EXPECT_CALL(flash_mock, read(1L)).WillRepeatedly(Return(1));
	EXPECT_CALL(flash_mock, read(2L)).WillRepeatedly(Return(2));

	Application app(new DeviceDriver(&flash_mock));
	EXPECT_THAT("0,1,2,", Eq(app.ReadAndPrint(0L,2L)));

}

TEST(FlashMockInjectionTest, ApplicationReadExceptionTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0L)).WillOnce(Return(0x2)).WillRepeatedly(Return(0));
	EXPECT_CALL(flash_mock, read(1L)).WillRepeatedly(Return(1));
	EXPECT_CALL(flash_mock, read(2L)).WillRepeatedly(Return(2));

	Application app(new DeviceDriver(&flash_mock));
	EXPECT_THROW(app.ReadAndPrint(0L, 2L),ReadFailException);

}

TEST(FlashMockInjectionTest, ApplicationWriteTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(1L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(2L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(3L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(4L)).Times(1).WillRepeatedly(Return(0xFF));

	EXPECT_CALL(flash_mock, write(0L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(1L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(2L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(3L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(4L, 999)).Times(1);

	Application app(new DeviceDriver(&flash_mock));
	app.WriteAll(999);


}

TEST(FlashMockInjectionTest, ApplicationWriteExceptionTest)
{
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(1L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(2L)).Times(1).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, read(3L)).Times(1).WillRepeatedly(Return(0x1));
	EXPECT_CALL(flash_mock, read(4L)).Times(0).WillRepeatedly(Return(0xFF));

	EXPECT_CALL(flash_mock, write(0L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(1L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(2L, 999)).Times(1);
	EXPECT_CALL(flash_mock, write(3L, 999)).Times(0);
	EXPECT_CALL(flash_mock, write(4L, 999)).Times(0);

	Application app(new DeviceDriver(&flash_mock));
	EXPECT_THROW(app.WriteAll(999), WriteFailException);
}

