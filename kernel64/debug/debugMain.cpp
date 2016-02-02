#include "debugMain.hpp"

kDebug::kDebug(void)
{

}

kDebug::~kDebug(void)
{

}

void kDebug::kInitializeDebug(void)
{

}


/// Wait for GDB
void kDebug::kLock(void)
{
    volatile unsigned int k;

    for (k=0; k < 0xFFFFFFFF; k++);

    return;
}