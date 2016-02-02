#pragma once

// Array of function pointers
// typedef void (*pISRVector)();
// pISRVector A[100];

#pragma pack(push, 1)

extern "C" 
{
    // Exception handling functions
    void _kISRDivideError(void);                /* 1 */
    void _kISRDebug(void);
    void _kISRNMI(void);
    void _kISRBreakPoint(void);
    void _kISROverflow(void);
    void _kISRBoundRangeExceeded(void);
    void _kISRInvalidOpcode(void);
    void _kISRDeviceNotAvailable(void);
    void _kISRDoubleFault(void);
    void _kISRCoprocessorSegmentOverrun(void);
    void _kISRInvalidTSS(void);
    void _kISRSegmentNotPresent(void);
    void _kISRStackSegmentFault(void);
    void _kISRGeneralProtection(void);
    void _kISRPageFault(void);
    void _kISR15(void);
    void _kISRFPUError(void);
    void _kISRAlignmentCheck(void);
    void _kISRMachineCheck(void);
    void _kISRSIMDError(void);
    void _kISRETCException(void);
    
    // Interrupt handling functions
    void _kISRTimer(void);
    void _kISRKeyboard(void);
    void _kISRSlavePIC(void);
    void _kISRSerial1(void);
    void _kISRSerial2(void);
    void _kISRParallel1(void);
    void _kISRParallel2(void);
    void _kISRFloppy(void);
    void _kISRRTC(void);
    void _kISRReserved(void);
    void _kISRNotUsed1(void);
    void _kISRNotUsed2(void);
    void _kISRMouse(void);
    void _kISRCoprocessor(void);
    void _kISRHDD1(void);
    void _kISRHDD2(void);
    void _kISRETCInterrupt(void);
};

#pragma pack(pop)
