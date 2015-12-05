#include "cpu.hpp"

// Read information of the processor
void kCpu::kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX)
{
    _kReadCPUID(dwEAX, pdwEAX, pdwEBX, pdwECX, pdwEDX);

    return;
}

// Switch to the IA-32e mode
void kCpu::kSwitchAndExecute64bitsKernel(void)
{
    _kSwitchAndExecute64bitsKernel();

    return;
}
