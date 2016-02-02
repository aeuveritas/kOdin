#pragma once

#include <types.hpp>

#pragma pack(push, 1)

extern "C" {
    BYTE _kInPortByte(WORD wPort);
    void _kOutPortByte(WORD wPort, BYTE bData);
};

/// Port  [IA-32e Mode]
class kPort
{
public:
    BYTE kInPortByte(WORD wPort);
    void kOutPortByte(WORD wPort, BYTE bData);
};

#pragma pack(pop)