#pragma once

#pragma pack(push, 1)

/// Debug module [IA-32e Mode]
class kDebug
{
public:
    kDebug(void);
    ~kDebug(void);
    
    void kInitializeDebug(void);
    void kLock(void);
};

#pragma pack(pop)