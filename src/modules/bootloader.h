
#ifndef _BOOTLOADER_H
#define _BOOTLOADER_H

#include <stdint.h>
#include <string.h>

#define PARAMES_INDEFICATION ( 0xaabbccdd)
struct bMemoryMap{
	uint32_t fw0;
	uint32_t fw1;
	uint32_t fw2;
	uint32_t info;	
};

typedef enum{
	STATUS_NOTEST = 0,
	STATUS_TEST_READY,
	STATUS_TESTING,
}BSTATUS_Typedef;

struct bInfomation{
	uint32_t indification;
	uint8_t img;
	BSTATUS_Typedef status;
};

typedef int (*pfPrintf)(const char *, ...);
typedef	int8_t (*pfWriteInfo)(struct bInfomation *, uint32_t);

struct bHalInterface{
	pfPrintf bPrintf;
	pfWriteInfo bWriteInfo;
};


int8_t bLoaderConfigure(const uint32_t mmpFw0,
						const uint32_t mmpFw1,
						const uint32_t mmpFw2,
						const uint32_t info,
						pfPrintf pPrintf,
						pfWriteInfo pWriteInfo);
int8_t bLoaderLoop(void);

#endif


