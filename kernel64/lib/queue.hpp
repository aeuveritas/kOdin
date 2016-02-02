#pragma once

#include <types.hpp>

#pragma pack(push, 1)

/// General queue [IA-32e Mode]
class kQueue
{
    /// Member variables
    int iDataSize;                  /// Data size
    int iMaxDataCount;              /// The max number of data
    
    void* pvQueueArray;             /// Pointer of this queue
    int iPushIndex;                 /// Index of push
    int iPopIndex;                  /// Index of pop
    
    bool bLastOperationPush;        /// If the last operation is push, 1
                                    /// If not, 0
    
public:
    kQueue(void);
    ~kQueue(void);
    
    void kInitializeQueue(void* _pvQueueBuffer, int _iMaxDataCount,
                          int _iDataSize);
    bool kIsQueueFull(void);
    bool kIsQueueEmpty(void);
    bool kPushQueue(const void* pvData);
    bool kPopQueue(void* pvData);
};

#pragma pack(pop)