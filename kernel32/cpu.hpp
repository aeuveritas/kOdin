#pragma once

#include "types.hpp"

extern "C" {
    void _kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, 
                     DWORD* pdwECX, DWORD* pdwEDX);
    void _kSwitchAndExecute64bitsKernel(void);
}

#pragma pack(push, 1)

/// Class for CPU registers [Protected Mode]
class k32Cpu
{
public:
    void kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, 
                    DWORD* pdwECX, DWORD* pdwEDX);
    void kSwitchAndExecute64bitsKernel(void);
};

#pragma pack(pop)
