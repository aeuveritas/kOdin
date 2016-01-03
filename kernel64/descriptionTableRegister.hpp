#pragma once

#include "types.hpp"

#pragma pack(push, 1)

/// structures for descriptor table register, GDTR and IDTR [IA-32e Mode]
typedef struct kDTRStruct
{
    WORD wLimit;
    QWORD qwBaseAddress;
    // Address padding
    WORD wPadding;
    DWORD dwPadding;
} DTR;

#pragma pack(pop)

