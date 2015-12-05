#pragma once

#include "pageManager.hpp"

/// Class for memory
class kMemory
{
    kPageManager clPM;

public:
    bool kIsMemoryEnough(void);
    bool kInitializeKernel64Area(void);
    void kInitializePageManager(void);
    void kCopyKernel64ImageTo2MB(void);
};
