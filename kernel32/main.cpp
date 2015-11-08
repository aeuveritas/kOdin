#include "types.hpp"
#include "utils.hpp"
#include "memory.hpp"

void main(void)
{
	int iline;
	kMemory clMem;
	kUtils clUtils;
	
	iline = 3;
	clUtils.kPrintString(0, iline++, 
							"[ PASS ]  C++ Language Kernel Start");
	
	// Check the memory is larger than the minimum size
	clUtils.kPrintString(0, iline, 
							"[      ]  Minimum Memory Size Check");
	if(clMem.kIsMemoryEnough() == false)
	{
		clUtils.kPrintString(2, iline++, "FAIL");
		clUtils.kPrintString(0, iline, 
							"Not Enough Memory!! Over 64 MB is required!!");
		
		while(1);
	}
	else
	{
		clUtils.kPrintString(2, iline++, 
							"PASS");
	}
	
	// Initialize kernel area for IA-32e mode
	clUtils.kPrintString(0, iline, 
							"[      ]  IA-32e Kernel Area Initialize");
	if(clMem.kInitializeKernel64Area() == false)
	{
		clUtils.kPrintString(2, iline++, 
							 "FAIL");
		clUtils.kPrintString(0, iline, 
							"Kernel Area initialization Fail!!");
		
		while(1);
	}
	clUtils.kPrintString(2, iline++, 
							"PASS");
	
	// Create the page tables for IA-32e mode
	clUtils.kPrintString(0, iline, 
							"[      ]  IA-32e Page Tables Initialize");
	clMem.kInitializePageManager();
	clUtils.kPrintString(2, iline++, 
							"PASS");
	
	while(1);
}


