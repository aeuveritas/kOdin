#include "cmdDate.hpp"
#include "commandParameter.hpp"
#include "console.hpp"
#include "RTC.hpp"

extern kConsole* g_pclConsole;
extern kRTC* g_pclRTC;

/// Constructor of kCommandDate
kCommandDate::kCommandDate(void)
{
    // Command name
    pcCommandName = "date";
    
    // Help message
    pcHelp = "Show date and time";
    
    // Example message
    pcExample = "ex) date";
}

/// Destructor of kCommandDate
kCommandDate::~kCommandDate(void)
{

}

/// Initialize kCommandDate
void kCommandDate::kInitializeCommandDate(void)
{

}

/// Execute to set timer
void kCommandDate::kTask_do(const char* pcParameter)
{
    BYTE bSecond;
    BYTE bMinute;
    BYTE bHour;
    
    BYTE bDayOfWeek;
    BYTE bDayOfMonth;
    BYTE bMonth;
    WORD wYear;
    
    if (pcParameter == nullptr)
    {
        return;
    }
    
    // Read date and day of week
    g_pclRTC->kReadRTCTime(&bHour, &bMinute, &bSecond);
    g_pclRTC->kReadRTCDate(&wYear, &bMonth, &bDayOfMonth, &bDayOfWeek);
    
    g_pclConsole->kPrintf("Date: %d/%d/%d %s, ",
                          wYear,
                          bMonth,
                          bDayOfMonth,
                          g_pclRTC->kConvertDayOfWeekToString(bDayOfWeek));
    g_pclConsole->kPrintf("Time: %d:%d:%d\n",
                          bHour,
                          bMinute,
                          bSecond);
    
    return;
}

