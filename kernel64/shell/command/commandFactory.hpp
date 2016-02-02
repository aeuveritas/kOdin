#pragma once

#include "commandList.hpp"

#include "cmdHelp.hpp"
#include "cmdClearScreen.hpp"
#include "cmdReboot.hpp"
#include "cmdRamSize.hpp"
#include "cmdStringToDecimalHex.hpp"
#include "cmdSetTimer.hpp"
#include "cmdWait.hpp"
#include "cmdRDTSC.hpp"
#include "cmdCpuSpeed.hpp"
#include "cmdDate.hpp"

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