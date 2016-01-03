#include "debug.hpp"

/// Wait for GDB
void kDebug::kLock(void)
{
    volatile unsigned int k;

    for (k=0; k < 0xFFFFFFFF; k++);

    return;
}