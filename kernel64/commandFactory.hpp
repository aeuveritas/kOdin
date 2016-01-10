#pragma once

#include "commandList.hpp"

#include "commandHelp.hpp"
#include "commandClearScreen.hpp"
#include "commandReboot.hpp"
#include "commandRamSize.hpp"
#include "commandStringToDecimalHex.hpp"
#include "commandSetTimer.hpp"
#include "commandWait.hpp"
#include "commandRDTSC.hpp"
#include "commandCpuSpeed.hpp"
#include "commandDate.hpp"

#pragma pack(push, 1)

/// Command factory [IA-32e Mode]
class kCommandFactory
{
    kCommandList* a_pclCommandList;
    
    kCommandHelp clCommandHelp;
    kCommandClearScreen clCommandClearScreen;
    kCommandReboot clCommandReboot;
    kCommandRamSize clCommandRamSize;
    kCommandStringToDecimalHex clCommandStringToDecimalHex;
    kCommandSetTimer clCommandSetTimer;
    kCommandWait clCommandWait;
    kCommandRDTSC clCommandRDTSC;
    kCommandCpuSpeed clCommandCpuSpeed;
    kCommandDate clCommandDate;
    
public:
    kCommandFactory(void);
    ~kCommandFactory(void);
    
    void kInitializeCommandFactory(kCommandList* _pclCommandList);

    void kUpdateCommandTable(void);
};

#pragma pack(pop)