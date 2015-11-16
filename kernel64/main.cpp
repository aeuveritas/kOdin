#include "types.hpp"
#include "utils.hpp"

void main(void)
{
    DWORD dwLine;
    kUtils clUtils;

    dwLine = 10;

    clUtils.kPrintString(2, dwLine++,
                         "PASS");
    clUtils.kPrintString(0, dwLine++,
                         "[ PASS ]  IA-32e C++ Language Kernel Start");
}