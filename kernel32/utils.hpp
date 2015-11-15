#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "types.hpp"
#include "asmUtils.hpp"

class kUtils
{
public:
	bool kPrintString(int iX, int iY, const char* pcString);
	
	void kReadCPUID(DWORD dwEAX, DWORD* pdwEAX, DWORD* pdwEBX, DWORD* pdwECX, DWORD* pdwEDX);
	void kSwitchAndExecute64bitsKernel(void);
	void kCopyKernel64ImageTo2MB(void);
};

#endif /* __UTIL_HPP__ */
