#include "RTC.hpp"
#include "TSC.hpp"

/// Constructor of kRTC
kRTC::kRTC(void)
{

}

/// Destructor of kRTC
kRTC::~kRTC(void)
{

}

/// Initialize kRTC
void kRTC::kIntializeRTC(kPort* pclPort)
{
    a_pclPort = pclPort;
}

/// Read the current time from CMOS memory
void kRTC::kReadRTCTime(BYTE* pbHour, BYTE* pbMinute, BYTE* pbSecond)
{
    BYTE bData;
    
    // Set the register storing hour 
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_HOUR);
    // Read hour from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbHour = RTC_BCDTOBINARY(bData);
    
    // Set the register storing minute
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_MINUTE);
    // Read minute from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbMinute = RTC_BCDTOBINARY(bData);
    
    // Set the register storing second
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_SECOND);
    // Read second from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbSecond = RTC_BCDTOBINARY(bData);
    
    return;
}

/// Read the current data from CMOS memory
void kRTC::kReadRTCDate(WORD* pwYear, BYTE* pbMonth, BYTE* pbDayOfMonth, 
                        BYTE* pbDayOfWeek)
{
    BYTE bData;
    
    // Set the register storing year 
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_YEAR);
    // Read year from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pwYear = RTC_BCDTOBINARY(bData) + 2000;
    
    // Set the register storing month
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_MONTH);
    // Read month from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbMonth = RTC_BCDTOBINARY(bData);
    
    // Set the register storing day
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_DAYOFMONTH);
    // Read day from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbDayOfMonth = RTC_BCDTOBINARY(bData);
    
    // Set the register storing day of week
    // to CMOS memory address register (port 0x70)
    a_pclPort->kOutPortByte(RTC_CMOSADDRESS, RTC_ADDRESS_DAYOFWEEK);
    // Read week from CMOS data register (port 0x71)
    bData = a_pclPort->kInPortByte(RTC_CMOSDATA);
    *pbDayOfWeek = RTC_BCDTOBINARY(bData);
    
    return;
}

/// Translate day of week from number to string
const char* kRTC::kConvertDayOfWeekToString(BYTE bDayOfWeek)
{
    // bDayOfWeek should not exceed 8,
    // because one week consists of 7 days
    if (bDayOfWeek >= 8)
    {
        return pcDayOfWeekString[0];
    }
    
    // Return day of week
    return pcDayOfWeekString[bDayOfWeek];
}
