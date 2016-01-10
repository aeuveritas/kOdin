#pragma once

#include "pageManager.hpp"

#pragma pack(push, 1)

/// Memory [Protected Mode]
class k32Memory
{
    k32PageManager clPM;

public:
    bool kIsMemoryEnough(void);
    bool kInitializeKernel64Area(void);
    void kInitializePageManager(void);
    void kCopyKernel64ImageTo2MB(void);
};

#pragma pakc(pop)
