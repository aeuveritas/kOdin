#pragma once

#include "commandList.hpp"

#include "commandHelp.hpp"
#include "commandClearScreen.hpp"
#include "commandReboot.hpp"
#include "commandRamSize.hpp"
#include "commandStringToDecimalHex.hpp"

#pragma pack(push, 1)

/// Class for command factory [IA-32e Mode]
class kCommandFactory
{
    kCommandList* a_pclCommandList;
    
    kCommandHelp clCommandHelp;
    kCommandClearScreen clCommandClearScreen;
    kCommandReboot clCommandReboot;
    kCommandRamSize clCommandRamSize;
    kCommandStringToDecimalHex clCommandStringToDecimalHex;
    
public:
    kCommandFactory(void);
    ~kCommandFactory(void);
    
    void kInitializeCommandFactory(kCommandList* _pclCommandList);

    void kUpdateCommandTable(void);
};

#pragma pack(pop)