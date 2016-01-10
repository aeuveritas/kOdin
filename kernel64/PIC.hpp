#pragma once

#include "types.hpp"
#include "port.hpp"

extern kPort clPort;

/// Macro

/// Define I/O port
#define PIC_MASTER_PORT1            0x20
#define PIC_MASTER_PORT2            0x21
#define PIC_SLAVE_PORT1             0xA0
#define PIC_SLAVE_PORT2             0xA1

/// Start point of interrupt vectors in IDT
#define PIC_IRQSTARTVECTOR          0x20

#pragma pack(push, 1)

/// Programmable Interrupt Controller [IA-32e Mode]
class kPIC
{
    kPort* a_pclPort;
    
public:
    kPIC(void);
    ~kPIC(void);
    
    void kInitializePIC(kPort* pclkPort);
    void kMaskPICInterrupt(WORD wIRQBitmask);
    void kSendEOIToPIC(int iIRQNumber);
};

#pragma pack(pop)
