#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Enum of command
enum COMMAND_TASK_TYPE
{
    COMMAND_HELP,
    COMMAND_CLS,
    COMMAND_REBOOT,
    COMMAND_RAMSIZE,
    COMMAND_STRTOD,
    COMMAND_SETTIMER,
    COMMAND_WAIT,
    COMMAND_RDTSC,
    COMMAND_CPUSPEED,
    COMMAND_DATE
};

/// Command list [IA-32e Mode]
class kCommandList
{
    /// Shell command structure
    typedef struct kShellCommandEntryStruct
    {
        // Command type
        COMMAND_TASK_TYPE eCommandType;
    
        // Command class
        kCommandTask* pclCommandTask;
    } SHELLCOMMAND;
    
    SHELLCOMMAND aCommandTable[10] = {
        {COMMAND_HELP, nullptr},
        {COMMAND_CLS, nullptr},
        {COMMAND_REBOOT, nullptr},
        {COMMAND_RAMSIZE, nullptr},
        {COMMAND_STRTOD, nullptr},
        {COMMAND_SETTIMER, nullptr},
        {COMMAND_WAIT, nullptr},
        {COMMAND_RDTSC, nullptr},
        {COMMAND_CPUSPEED, nullptr},
        {COMMAND_DATE, nullptr},
    };
    
    int iNumEntry;
    int iLongestCommandLength;

public:
    kCommandList(void);
    ~kCommandList(void);
    
    void kInitializeCommandList(void);
    
    void kCountCommandTableEntry(void);
    void kCountLongestCommandLength(void);
    
    bool kSetTask(COMMAND_TASK_TYPE _eCommandType, kCommandTask* pclTask);
    
    int kGetNumEntry(void);
    int kGetLongestCommandLength(void);   
    
    kCommandTask* kGetTask(int iCount);
};

#pragma pack(pop)