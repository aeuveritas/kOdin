#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BYTESOFSECTOR 512

// Define functions
int adjustInSectorSize(int iFd, int iSourceSize);
void writeKernelInformation(int iTargetFd, int iKernelSectorCount,
                            int iKernel32SectorCount);
int copyFile(int iSourceFd, int iTargetFd);

// Main
int main(int argc, char* argv[])
{
    int iSourceFd;
    int iTargetFd;
    int iBootLoaderSize;
    int iKernel32SectorCount;
    int iKernel64SectorCount;
    int iSourceSize;

    // Check command line option
    if (argc < 4) {
        fprintf(stderr, "[ERROR] imageMaker BootLoader.bin Kernel32.bin Kernel64.bin\n");
        exit(-1);
    }

    // Create Disk.img
    if ((iTargetFd = open("./OUT/kOdin.img", O_RDWR | O_CREAT | O_TRUNC,
                          S_IREAD | S_IWRITE)) == -1) {
        fprintf(stderr, "[ERROR] %s open fail\n", argv[1]);
        exit(-1);
    }

    /*
     * Open bootloader file and copy it to image file
     */
    printf("[INFO] Copy bootloader to image file\n");

    if ((iSourceFd = open(argv[1], O_RDONLY)) == -1) {
        fprintf(stderr, "[ERROR} %s open fail\n", argv[1]);
        exit(-1);
    }

    iSourceSize = copyFile(iSourceFd, iTargetFd);
    close(iSourceFd);

    // Fill rest of section with 0
    iBootLoaderSize = adjustInSectorSize(iTargetFd, iSourceSize);
    printf("[INFO] %s size = [%d] and sector count = [%d]\n",
           argv[1], iSourceSize, iBootLoaderSize);

    /*
     * Open 32 bits kernel and copy it to image file
     */
    printf("[INFO] Copy the protected mode kernel to image file\n");

    if ((iSourceFd = open(argv[2], O_RDONLY)) == -1) {
        fprintf(stderr, "[ERROR] %s open fail\n", argv[2]);
        exit(-1);
    }

    iSourceSize = copyFile(iSourceFd, iTargetFd);
    close(iSourceFd);

    // Fill rest of section with 0
    iKernel32SectorCount = adjustInSectorSize(iTargetFd, iSourceSize);
    printf("[INFO] %s size = [%d] and sector count = [%d]\n",
           argv[2], iSourceSize, iKernel32SectorCount);

    /*
     * Open 64 bits kernel and copy it to image file
     */
    printf("[INFO] Copy the IA-32e mode kernel to image file\n");

    if ((iSourceFd = open(argv[3], O_RDONLY)) == -1) {
        fprintf(stderr, "[ERROR] %s open fail\n", argv[3]);
        exit(-1);
    }

    iSourceSize = copyFile(iSourceFd, iTargetFd);
    close(iSourceFd);

    // Fill rest of section with 0
    iKernel64SectorCount = adjustInSectorSize(iTargetFd, iSourceSize);
    printf("[INFO] %s size = [%d] and sector count = [%d]\n",
           argv[3], iSourceSize, iKernel64SectorCount);

    /*
     * Update kernel information to disk image
     */
    printf("[INFO] Start to write kernel information\n");
    // Write information to 5th byte of boot sector
    writeKernelInformation(iTargetFd, iKernel32SectorCount + iKernel64SectorCount,
                           iKernel32SectorCount);
    printf("[INFO] Image file create complete\n");

    close(iTargetFd);
    return 0;
}

// Fill 0 from cuurent point to multiple of 512 bytes
int adjustInSectorSize(int iFd, int iSourceSize)
{
    int i;
    int iAdjustSizeToSector;
    char cCh;
    int iSectorCount;

    iAdjustSizeToSector = iSourceSize % BYTESOFSECTOR;
    cCh = 0x00;

    if (iAdjustSizeToSector != 0) {
        iAdjustSizeToSector = 512 - iAdjustSizeToSector;
        printf("[INFO] File size [%u] and fill [%u] byte\n", iSourceSize,
               iAdjustSizeToSector);
        for (i = 0; i < iAdjustSizeToSector; i++) {
            write(iFd, &cCh, 1);
        }
    } else {
        printf("[INFO] File size is aligned 512 byte\n");
    }

    // Return the number of sectors
    iSectorCount = (iSourceSize + iAdjustSizeToSector) / BYTESOFSECTOR;
    return iSectorCount;
}

// Insert kernel information to bootloader
void writeKernelInformation(int iTargetFd, int iTotalKernelSectorCount,
                            int iKernel32SectorCount)
{
    unsigned short usData;
    long lPosition;

    // The 5th byte is the number of total sectors
    lPosition = lseek(iTargetFd, 5, SEEK_SET);
    if (lPosition == -1) {
        fprintf(stderr, "lseek fail, Return value = %ld, errno = %d, %d\n",
                lPosition, errno, SEEK_SET);
        exit(-1);
    }

    // Store the numbeer of total sectors except for bootloader
    usData = (unsigned short)iTotalKernelSectorCount;
    write(iTargetFd, &usData, 2);
    // Store the numbeer of protected mode kernel sectors
    usData = (unsigned short)iKernel32SectorCount;
    write(iTargetFd, &usData, 2);

    printf("[INFO] Total sector count except bootloader[%d]\n",
           iTotalKernelSectorCount);
    printf("[INFO] Total sector count of protected mode kernel[%d]\n",
           iKernel32SectorCount);
}

// Copy the source file to the targer file and return the size
int copyFile(int iSourceFd, int iTargetFd)
{
    int iSourceFileSize;
    int iRead;
    int iWrite;
    char vcBuffer[BYTESOFSECTOR];

    iSourceFileSize = 0;
    while (1) {
        iRead = read(iSourceFd, vcBuffer, sizeof(vcBuffer));
        iWrite = write(iTargetFd, vcBuffer, iRead);

        if (iRead != iWrite) {
            fprintf(stderr, "[ERROR] iRead != iWrite..\n");
            exit(-1);
        }
        iSourceFileSize += iRead;

        if (iRead != sizeof(vcBuffer)) {
            break;
        }
    }

    return iSourceFileSize;
}
