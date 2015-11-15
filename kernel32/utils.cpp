#include "utils.hpp"

// Print message
bool kUtils::kPrintString(int iX, int iY, const char* pcString)
{
	CHARACTER* pstScreen = (CHARACTER*) 0xB8000;
	
	pstScreen += (iY * 80) + iX;
	
	for(int i=0; pcString[i] != 0; i++)
	{
		pstScreen[i].bCharactor = pcString[i];
	}
	
	return true;
}

// Read information of the processor
void kUtils::kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX)
{
	_kReadCPUID(dwEAX, pdwEAX, pdwEBX, pdwECX, pdwEDX);
	
	return;
}

void kUtils::kSwitchAndExecute64bitsKernel(void)
{
	_kSwitchAndExecute64bitsKernel();
	
	return;
}


// Copy IA-32e mode kernel to 0x200000 (= 2 MB)
void kUtils::kCopyKernel64ImageTo2MB(void)
{
	WORD wKernel32SectorCount;
	WORD wTotalKernelSectorCount;
	DWORD* pdwSourceAddress;
	DWORD* pdwDestinationAddress;
	
	// Read the number of total sectors from 0x7C05
	wTotalKernelSectorCount = *((WORD*) 0x7C05);
	
	// Read the number of protected mode kernel sectors
	wKernel32SectorCount = *((WORD*) 0x7C07);
	
	pdwSourceAddress = (DWORD*) (0x10000 + wKernel32SectorCount * 512);
	pdwDestinationAddress = (DWORD*) 0x200000;
	
	// Copy IA-32e mode kernel sectors as the size
	for (int i = 0; i < 512 * (wTotalKernelSectorCount - wKernel32SectorCount) / 4; i++)
	{
		*pdwDestinationAddress = *pdwSourceAddress;
		pdwDestinationAddress++;
		pdwSourceAddress++;
	}
}
