#include "queue.hpp"

#include "memoryHelper.hpp"

extern kMemoryHelper* g_pclMemoryHelper;

/// Constructor of kQueue
kQueue::kQueue(void)
{
    iMaxDataCount = 0;
    iDataSize = 0;
    pvQueueArray = nullptr;
    
    iPushIndex = 0;
    iPopIndex = 0;
    
    bLastOperationPush = false;
}

/// Destructor of kQueue
kQueue::~kQueue(void)
{
    iMaxDataCount = 0;
    iDataSize = 0;
    pvQueueArray = nullptr;
    
    iPushIndex = 0;
    iPopIndex = 0;
    
    bLastOperationPush = false;
}

/// Initialize kQueue
void kQueue::kInitializeQueue(void* _pvQueueBuffer, int _iMaxDataCount,
                              int _iDataSize)
{
    // Set the max number of data, size, and buffer address of this queue
    iMaxDataCount = _iMaxDataCount;
    iDataSize = _iDataSize;
    pvQueueArray = _pvQueueBuffer;
    
    // Initialize the indexes of push and pop
    iPushIndex = 0;
    iPopIndex = 0;
    
    // Set the last operation as pop to inform this queue is empty
    bLastOperationPush = false;
}

/// Check whether or not this queue is full
bool kQueue::kIsQueueFull(void)
{
    // If the indexes of push and pop are the same and the last operation is push,
    // this queue is full
    if ((iPushIndex == iPopIndex) && (bLastOperationPush == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// Check whether or not this queue is empty
bool kQueue::kIsQueueEmpty(void)
{
    // IF the indexes of push and pop are the same and 
    // the last operation is pop,
    // this queue is empty
    if ((iPushIndex == iPopIndex) && (bLastOperationPush == false))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// Push data
bool kQueue::kPushQueue(const void* pvData)
{
    char* dest;
    
    // Check the queue is full or not
    if (kIsQueueFull() == true)
    {
        return false;
    }
    
    // Calculate target address
    dest = (char*) pvQueueArray + (iDataSize * iPushIndex);
    
    // Copy data to the queue memory
    g_pclMemoryHelper->kMemCpy(dest, pvData, iDataSize);
    
    // Update the index of push and the last operation flag
    iPushIndex = (iPushIndex + 1) % iMaxDataCount;
    bLastOperationPush = true;
    
    return true;
}

/// Pop data
bool kQueue::kPopQueue(void* pvData)
{
    char* src;
    
    // Check the queue is empty or not
    if (kIsQueueEmpty() == true)
    {
        return false;
    }
    
    // Calculate targer address
    src = (char*) pvQueueArray + (iDataSize * iPopIndex);
    
    // Copy data from the queue memory
    g_pclMemoryHelper->kMemCpy(pvData, src, iDataSize);
    
    // Update the index of pop and the last operation flag
    iPopIndex = (iPopIndex + 1) % iMaxDataCount;
    bLastOperationPush = false;
    
    return true;
}

