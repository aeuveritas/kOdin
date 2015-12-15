#include "PIC.hpp"

/// Constructor of PIC
kPIC::kPIC(void)
{
    a_pclPort = nullptr;
}

/// Deconstructor of PIC
kPIC::~kPIC(void)
{
    a_pclPort = nullptr;
}

/// Initialize PIC
void kPIC::kInitializePIC(kPort* _kPort)
{
    // Set the object of kPort
    a_pclPort = _kPort;
    
    // Initialize the master PIC
    // ICW1 (Port 0x20), IC4 bit (Bit 0) = 1
    a_pclPort->kOutPortByte(PIC_MASTER_PORT1, 0x11);
    
    // ICW2 (Port 0x21), Interrupt vector (0x20)
    a_pclPort->kOutPortByte(PIC_MASTER_PORT2, PIC_IRQSTARTVECTOR);
    
    // ICW2 (Port 0x21), Connection pin of the slave PIC
    // Bitmap for the slave PIC (0x04)
    a_pclPort->kOutPortByte(PIC_MASTER_PORT2, 0x04);
    
    // ICW4 (Port 0x21(, uPM bit (BIT 0) = 1
    a_pclPort->kOutPortByte(PIC_MASTER_PORT2, 0x01);
    
    // Initialize the slave PIC
    // ICW1 (Port 0xA0), IC4 bit (BIT 0) = 1
    a_pclPort->kOutPortByte(PIC_SLAVE_PORT1, 0x11);
    
    // ICW2 (Port 0xA1), Interrupt vector (0x20 + 8)
    a_pclPort->kOutPortByte(PIC_SLAVE_PORT2, PIC_IRQSTARTVECTOR + 8);
    
    // ICW3 (Port 0xA1), Connection pin of the master PIC
    // Pin number for the slave PIC (0x02)
    a_pclPort->kOutPortByte(PIC_SLAVE_PORT2, 0x02);
    
    // ICW4 (Port 0xA1), uPM bit (Bit 0) = 1
    a_pclPort->kOutPortByte(PIC_SLAVE_PORT2, 0x01);
}

/// Mask interrupt to ignore it
void kPIC::kMaskPICInterrupt(WORD wIRQBitmask)
{
    // Set IMR of the master PIC
    // OCW1 (Port 0x21), IRQ 0 ~ IRQ 7
    a_pclPort->kOutPortByte(PIC_MASTER_PORT2, (BYTE)wIRQBitmask);
    
    // Set IMR of the slave PIC
    // OCW1 (Port 0xA1), IRQ 8 ~ IRQ 15
    a_pclPort->kOutPortByte(PIC_SLAVE_PORT2, (BYTE)(wIRQBitmask >> 8));
}

/** Send EOI to notify an interrupt finish
  *     For an interrupt of the master PIC,
  *         send EOI to only the master PIC
  *     For an interrupt of the slave PIC,
  *         send EOI to the master and the slave PIC
  */
void kPIC::kSendEOIToPIC(int iIRQNumber)
{
    // Send EOI to the master PIC
    // OCW2 (Port 0x20), EOI bit (Bit 5) = 1
    a_pclPort->kOutPortByte(PIC_MASTER_PORT1, 0x20);
    
    // If the interrupt is for the slave PIC, send EOI to the slave PIC
    if (iIRQNumber >= 8)
    {
        // OCW2 (Port 0xA0), EOI bit (Bit 5) = 1
        a_pclPort->kOutPortByte(PIC_SLAVE_PORT1, 0x20);
    }
}

/// Enable interrupt
void kPIC::kEnableInterrupt(void)
{
    _kEnableInterrupt();
}

/// Disable interrupt
void kPIC::kDisableInterrupt(void)
{
    _kDisableInterrupt();
}

/// Read RFLGAS and return it
QWORD kPIC::kReadRFLAGS(void)
{
    return _kReadRFLAGS();
}
