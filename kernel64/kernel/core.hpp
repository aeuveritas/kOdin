#pragma once

#include <types.hpp>
#include <keyboard.hpp>
#include <descriptionTable.hpp>
#include <PIC.hpp>
#include <interruptHandler.hpp>
#include <memoryHelper.hpp>
#include <stringHelper.hpp>
#include <console.hpp>
#include <consoleShell.hpp>
#include <PIT.hpp>
#include <TSC.hpp>
#include <RTC.hpp>

#include <debugMain.hpp>

#pragma pack(push, 1)

/// Kernel core [IA-32e Mode]
class kCore
{
    kConsole clConsole;
    kPort clPort;
    kDT clDT;
    kKeyboard clKeyboard;
    kPIC clPIC;
    kIH clIH;
    kMemoryHelper clMemoryHelper;
    kConsoleShell clConsoleShell;
    kStringHelper clStringHelper;
    kPIT clPIT;
    kTSC clTSC;
    kRTC clRTC;
    
    kDebug clDebug;
    
public:
    kCore(void);
    ~kCore(void);
    
    void kInitializeCoere(void);
};

#pragma pack(pop)