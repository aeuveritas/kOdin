#include "types.hpp"

bool kPrintString(int iX, int iY, const char* pcString);
bool kInitializeKernel64Area(void);
bool kIsMemoryEnough(void);

void main(void)
{
	DWORD i;
	
	kPrintString(0, 3, "C++ Language Kernel Start.................................................[PASS]");
	
	// Check the memory is larger than the minimum size
	kPrintString(0, 4, "Minimum Memory Size Check.................................................[    ]");
	if (kIsMemoryEnough() == false)
	{
		kPrintString(75, 4, "FAIL");
		kPrintString(0, 5, "Not Enough Memory!! kOdin Requires Over 64 MB!!");
		
		while (1);
	}
	else
	{
		kPrintString(75, 4, "PASS");
	}
	
	// Initialize kernel area for IA-32e mode
	kPrintString(0, 5, "IA-32e Kernel Area Initialize.............................................[    ]");
	if (kInitializeKernel64Area() == false)
	{
		kPrintString(75, 5, "FAIL");
		kPrintString(0, 6, "Kernel Area initialization Fail!!");
		
		while (1);
	}
	kPrintString(75, 5, "PASS");
	
	while (1);
}

// Print message
bool kPrintString(int iX, int iY, const char* pcString)
{
	CHARACTER* pstScreen = (CHARACTER*) 0xB8000;
	
	pstScreen += (iY * 80) + iX;
	
	for (int i=0; pcString[i] != 0; i++)
	{
		pstScreen[i].bCharactor = pcString[i];
	}
}

// Initialize kernel area for IA-32e with 0
bool kInitializeKernel64Area(void)
{
	DWORD* pdwCurrentAddress;
	
	// Start point of initialization, 1 MB
	pdwCurrentAddress = (DWORD*) 0x100000;
	
	// Until 6 MB, initialize every 4 byte with 0
	while ((DWORD)pdwCurrentAddress < 0x600000)
	{
		*pdwCurrentAddress = 0x00;
		
		// After writing, check the written value.
		// If it is not the same, there is a problem.
		if (*pdwCurrentAddress != 0)
		{
			return false;
		}
		
		// Move to the next address
		pdwCurrentAddress++;
	}
	
	return true;
}

// Check the size of memory is larget than the minimum
bool kIsMemoryEnough(void)
{
	DWORD* pdwCurrentAddress;
	
	// From 0x100000 (= 1MB)
	pdwCurrentAddress = (DWORD*) 0x100000;
	
	// Util 64 MB, check the memory
	while ((DWORD)pdwCurrentAddress < 0x4000000)
	{
		// Write an temporary value
		*pdwCurrentAddress = 0x12345678;
		
		// Read the address,
		// and if the value is not the same as what I write,
		// there is a a problem
		if(*pdwCurrentAddress != 0x12345678)
		{
			return false;	
		}
		
		// Move to the next 1 MB
		pdwCurrentAddress += (0x100000 / 4);
	}
	
	return true;
}
