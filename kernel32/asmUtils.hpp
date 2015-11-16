#ifndef __ASM_UTILS_HPP__
#define __ASM_UTILS_HPP__

#include "types.hpp"

extern "C" {
    void _kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX);
    void _kSwitchAndExecute64bitsKernel(void);
}

#endif /* __ASM_UTILS_HPP__ */