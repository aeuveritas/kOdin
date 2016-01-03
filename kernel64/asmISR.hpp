#pragma once

#include "descriptionForInterrupt.hpp"

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

/** ISR class is not used,
  * because C++ stack is remained after interrupt.
/// class for ISR
class kISR
{
public: 
    // Functions
    // Exception handling ISR
    static void kISRDivideError(void);
    static void kISRDebug(void);
    static void kISRNMI(void);
    static void kISRBreakPoint(void);
    static void kISROverflow(void);
    static void kISRBoundRangeExceeded(void);
    static void kISRInvalidOpcode(void);
    static void kISRDeviceNotAvailable(void);
    static void kISRDoubleFault(void);
    static void kISRCoprocessorSegmentOverrun(void);
    static void kISRInvalidTSS(void);
    static void kISRSegmentNotPresent(void);
    static void kISRStackSegmentFault(void);
    static void kISRGeneralProtection(void);
    static void kISRPageFault(void);
    static void kISR15(void);
    static void kISRFPUError(void);
    static void kISRAlignmentCheck(void);
    static void kISRMachineCheck(void);
    static void kISRSIMDError(void);
    static void kISRETCException(void);
    
    // Interrupt handling ISR
    static void kISRTimer(void);
    static void kISRKeyboard(void);
    static void kISRSlavePIC(void);
    static void kISRSerial1(void);
    static void kISRSerial2(void);
    static void kISRParallel1(void);
    static void kISRParallel2(void);
    static void kISRFloppy(void);
    static void kISRRTC(void);
    static void kISRReserved(void);
    static void kISRNotUsed1(void);
    static void kISRNotUsed2(void);
    static void kISRMouse(void);
    static void kISRCoprocessor(void);
    static void kISRHDD1(void);
    static void kISRHDD2(void);
    static void kISRETCInterrupt(void);
};
**/

#pragma pack(pop)
