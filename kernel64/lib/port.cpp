#include "port.hpp"

BYTE kPort::kInPortByte(WORD wPort)
{
    return _kInPortByte(wPort);
}

void kPort::kOutPortByte(WORD wPort, BYTE bData)
{
    return _kOutPortByte(wPort, bData);
}
