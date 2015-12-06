#pragma once

#include "types.hpp"

extern "C" {
    BYTE _kInPortByte(WORD wPort);
    void _kOutPortByte(WORD wPort, BYTE bData);
    void _kLoadGDTR(QWORD qwGDTRAddress);
    void _kLoadTR(WORD wTSSSegmentOffset);
    void _kLoadIDTR(QWORD qwIDTRAddress);
};

#pragma pack(push, 1)
