#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "pageManager.hpp"

class kMemory
{
	kPageManager clPM;
	
public:
	bool kIsMemoryEnough(void);
	bool kInitializeKernel64Area(void);
	void kInitializePageManager(void);
};
#endif /* __MEMORY_HPP__ */