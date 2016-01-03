#pragma once

#pragma pack(push, 1)

/// Interface of command task [IA-32e Mode]
class kCommandTask
{
protected:
    const char* pcCommandName;
    const char* pcHelp;
    
public:
    virtual void kTask_do(const char* pcParameter) = 0;
    virtual void kTask_help(void);
    virtual const char* kTask_getName(void);
};

#pragma pack(pop)