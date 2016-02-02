#include "IDT.hpp"

/// Constructor of kIDT
kIDT::kIDT(void)
{
    pstIDTR = nullptr;
    pstIDTEntry = nullptr;
}

/// Destructor of kIDT
kIDT::~kIDT(void)
{
    pstIDTR = nullptr;
    pstIDTEntry = nullptr;
}

/// Initialize kIDT
void kIDT::kInitializeIDT(void)
{   
    // Start address of IDTR
    pstIDTR = (DTR*)IDTR_STARTADDRESS;
    // Set IDT information
    pstIDTEntry = (IDTENTRY*)(IDTR_STARTADDRESS + sizeof(DTR));
    pstIDTR->qwBaseAddress = (QWORD)pstIDTEntry;
    pstIDTR->wLimit = IDT_TABLESIZE - 1;
    
    // Register exception ISR
    kSetIDTEntry(&(pstIDTEntry[0]), _kISRDivideError, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[1]), _kISRDebug, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[2]), _kISRNMI, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[3]), _kISRBreakPoint, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[4]), _kISROverflow, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[5]), _kISRBoundRangeExceeded, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[6]), _kISRInvalidOpcode, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[7]), _kISRDeviceNotAvailable, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[8]), _kISRDoubleFault, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[9]), _kISRCoprocessorSegmentOverrun, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[10]), _kISRInvalidTSS, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[11]), _kISRSegmentNotPresent, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[12]), _kISRStackSegmentFault, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[13]), _kISRGeneralProtection, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[14]), _kISRPageFault, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[15]), _kISR15, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[16]), _kISRFPUError, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[17]), _kISRAlignmentCheck, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[18]), _kISRMachineCheck, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[19]), _kISRSIMDError, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[20]), _kISRETCException, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    
    for (int iEntryNum = 21; iEntryNum < 32; iEntryNum++)
    {
        kSetIDTEntry(&(pstIDTEntry[iEntryNum]), _kISRETCException, 0x08,
                     IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
    
    // Register interrupt ISR
    kSetIDTEntry(&(pstIDTEntry[32]), _kISRTimer, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[33]), _kISRKeyboard, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[34]), _kISRSlavePIC, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[35]), _kISRSerial2, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[36]), _kISRSerial1, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[37]), _kISRParallel2, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[38]), _kISRFloppy, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[39]), _kISRParallel1, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[40]), _kISRRTC, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[41]), _kISRReserved, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[42]), _kISRNotUsed1, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[43]), _kISRNotUsed2, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[44]), _kISRMouse, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[45]), _kISRCoprocessor, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[46]), _kISRHDD1, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    kSetIDTEntry(&(pstIDTEntry[47]), _kISRHDD2, 0x08,
                 IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    
    for (int iEntryNum = 48; iEntryNum < IDT_MAXENTRYCOUNT; iEntryNum++)
    {
        kSetIDTEntry(&(pstIDTEntry[iEntryNum]), _kISRETCInterrupt, 0x08,
                     IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
    
}

/// Set IDT gate descriptor
void kIDT::kSetIDTEntry(IDTENTRY* pstEntry, void (*pvHandler)(), 
                       WORD wSelector, BYTE bIST, BYTE bFlags, BYTE bType)
{
    pstEntry->wLowerBaseAddress = (QWORD)pvHandler & 0xFFFF;
    pstEntry->wSegmentSelector = wSelector;
    pstEntry->bIST = bIST & 0x3;
    pstEntry->bTypeAndFlags = bType | bFlags;
    pstEntry->wMiddleBaseAddress = ((QWORD)pvHandler >> 16) & 0xFFFF;
    pstEntry->dwUpperBaseAddress = (QWORD)pvHandler >> 32;
    pstEntry->dwReserved = 0;
}

void kIDT::kLoadIDTR(QWORD qwIDTRAddress)
{
    _kLoadIDTR(qwIDTRAddress);
}