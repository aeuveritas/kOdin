#pragma once

#include "types.hpp"

extern "C" {
    BYTE _kInPortByte(WORD wPort);
    void _kOutPortByte(WORD wPort, BYTE bData);
};
