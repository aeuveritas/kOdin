#pragma once

#pragma pack(push, 1)

/// Command task interface [IA-32e Mode]
class kCommandTask
{
protected:
    const char* pcCommandName;
    const char* pcHelp;
    const char* pcExample;
    
public:
    virtual void kTask_do(const char* pcParameter) = 0;
    virtual void kTask_help(void);
    virtual const char* kTask_getName(void);
    virtual void kTask_example(void);
};

#pragma pack(pop)