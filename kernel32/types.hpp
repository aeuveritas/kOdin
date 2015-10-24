#ifndef __TYPES_H__
#define __TYPES_H__

#define BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned int
#define QWORD	unsigned long
#define BOOL	unsigned char

#pragma pack(push, 1)

// Data structure for text to print in video mode
typedef struct kCharactorStruct
{
  BYTE bCharactor;
  BYTE bAttribute;
} CHARACTER;

#pragma pack(pop)

#endif /* __TYPES_H__ */
