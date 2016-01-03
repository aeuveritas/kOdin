#pragma once

#pragma pack(push, 1)

/// Class of command parameter [IA-32e Mode]
class kCommandParameter
{
    // Address for the parameter
    const char* pcBuffer;
    
    // The length of the parameter
    int iLength;
    
    // The start point of the current parameter
    int iCurrentPosition;

public:
    kCommandParameter(void);
    ~kCommandParameter(void);
    
    void kInitializeCommandParameter(const char* pcParameter);
    int kGetNextParameter(char* pcParameter);
};

#pragma pack(pop)