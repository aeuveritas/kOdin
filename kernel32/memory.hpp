#pragma once

#include "pageManager.hpp"

class kMemory
{
    kPageManager clPM;

public:
    bool kIsMemoryEnough(void);
    bool kInitializeKernel64Area(void);
    void kInitializePageManager(void);
    void kCopyKernel64ImageTo2MB(void);
};
