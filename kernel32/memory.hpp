#pragma once

#include "pageManager.hpp"

#pragma pack(push, 1)

/// Class for memory [Protected Mode]
class kMemory
{
    kPageManager clPM;

public:
    bool kIsMemoryEnough(void);
    bool kInitializeKernel64Area(void);
    void kInitializePageManager(void);
    void kCopyKernel64ImageTo2MB(void);
};

#pragma pakc(pop)
