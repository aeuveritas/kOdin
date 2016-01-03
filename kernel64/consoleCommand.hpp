#pragma once

#include "commandTask.hpp"
#include "commandFactory.hpp"
#include "commandList.hpp"

#pragma pack(push, 1)

/// Class of consol command [IA-32e Mode]
class kConsoleCommand
{    
    kCommandFactory clCommandFactory;
    kCommandList clCommandList;
    
public:
    kConsoleCommand(void);
    ~kConsoleCommand(void);
    
    void kInitializeConsoleCommand(void);
    
    kCommandTask* kGetTask(int iIndex);
    int kGetNumEntry(void);
    int kGetLongestCommandLength(void);
    
    void kExecuteCommand(const char* pcCommandBuffer);
};

#pragma pack(pop)