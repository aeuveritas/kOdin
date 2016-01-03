#pragma once

#include "commandTask.hpp"
#include "commandList.hpp"

#pragma pack(push, 1)

/// Class of command to print help message [IA-32e Mode]
class kCommandHelp: public kCommandTask
{
    kCommandList* a_pclCommandList;
    
public:
    void kTask_do(const char* pcParameterBuffer) override;
    
    kCommandHelp(void);
    ~kCommandHelp(void);
    
    void kInitializeCommandHelp(kCommandList* pclCommandList);
};

#pragma pack(pop)