#include "page.hpp"

void kPageTableEntry::setDwAttributeAndLowerBaseAddress(DWORD input)
{
    dwAttributeAndLowerBaseAddress = input;
}

void kPageTableEntry::setDwUpperBaseAddressAndEXB(DWORD input)
{
    dwUpperBaseAddressAndEXB = input;
}
