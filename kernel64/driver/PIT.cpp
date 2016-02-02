#include "PIT.hpp"

/// Constructor of kPIT
kPIT::kPIT(void)
{

}

/// Destructor of kPIT
kPIT::~kPIT(void)
{

}

/// Initialize kPIT
void kPIT::kInitializePIT(kPort* pclPort)
{
    a_pclPort = pclPort;

    return;
}

/// Set timer
void kPIT::kSetPIT(WORD wCount, bool bPeriodic)
{
    // To stop the counter, initialize PIT control register (port 0x43)
    // Mode 0, Binary counter
    a_pclPort->kOutPortByte(PIT_PORT_CONTROL, PIT_COUNTER0_ONCE);
    
    // Non-periodic timer is Mode 0
    // Periodic timer is Mode 2
    if (bPeriodic == true)
    {
        // Set Mode 2 and binary counter at PIC control register (port 0x43)
        a_pclPort->kOutPortByte(PIT_PORT_CONTROL, PIT_COUNTER0_PERIODIC);
    }
    
    // Initialize the counter0 (port 0x40) from LSB to MSB
    a_pclPort->kOutPortByte(PIT_PORT_COUNTER0, wCount);
    a_pclPort->kOutPortByte(PIT_PORT_COUNTER0, wCount >> 8);

    return;
}

/// Return the current value of the counter0
WORD kPIT::kReadCounter0(void)
{
    BYTE bHighByte;
    BYTE bLowByte;
    WORD wTemp = 0;
    
    // By sending latch instruction to PIT control register (port 0x43),
    // read the current value of the counter0
    a_pclPort->kOutPortByte(PIT_PORT_CONTROL, PIT_COUNTER0_LATCH);
    
    // Read the value of the counter0 (port 0x40) from LSB to MSB 
    bLowByte = a_pclPort->kInPortByte(PIT_PORT_COUNTER0);
    bHighByte = a_pclPort->kInPortByte(PIT_PORT_COUNTER0);
    
    // Translate BCD to 16 bit number
    wTemp = bHighByte;
    wTemp = (wTemp << 8) | bLowByte;
    
    return wTemp;
}

/**
 * Wait for a certain time by setting counter0 directly
 *      When this function is called, setting for PIT controller is changed
 *      Therefore, it is necessary to set again PIT controller
 *      To be more accurate, it is better to disable interrupt
 *          before calling this function
 *      It is possible to wait for about 50ms
 **/
void kPIT::kWaitUsingDirectPIT(WORD wCount)
{
    WORD wLastCounter0;
    WORD wCurrentCounter0;
    
    // Set PIT control to repeat 0x0000 ~ 0xFFFF
    kSetPIT(0, true);
    
    // Wait until the counter exceeds wCount
    wLastCounter0 = kReadCounter0();
    while (1)
    {
        // Compare the current value of the counter0
        wCurrentCounter0 = kReadCounter0();
        if (((wLastCounter0 - wCurrentCounter0) & 0xFFFF) >= wCount)
        {
            break;
        }
    }
    
    return;
}

