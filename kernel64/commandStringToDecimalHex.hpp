#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Class of command to convert string to number [IA-32e Mode]
class kCommandStringToDecimalHex: public kCommandTask
{
public:
    void kTask_do(const char* pcParameterBuffer) override;
    
    kCommandStringToDecimalHex(void);
    ~kCommandStringToDecimalHex(void);
    
    void kInitializeCommandStringToDecimalHex(void);
};

#pragma pack(pop)