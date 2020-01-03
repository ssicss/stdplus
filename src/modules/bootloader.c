#include "bootloader.h"


volatile struct bHalInterface bHal;
volatile struct bMemoryMap bMMap;



static void _bJumpToApp(uint32_t addr)
{
    if (((*(volatile uint32_t *)addr) & 0x2FFE0000 ) == 0x20000000)
    { 
		__asm__ __volatile__(
		"mov r0, %0\n"
		"ldr r1, [r0]\n"
		"msr msp, r1\n"
		"ldr r1, [r0, #4]\n"
		"mov pc, r1\n"
		:
		:"r"(addr)
		:"r0","r1"
		);
    }
}

int8_t bLoaderConfigure(const uint32_t mmpFw0,
						const uint32_t mmpFw1,
						const uint32_t mmpFw2,
						const uint32_t info,
						pfPrintf pPrintf,
						pfWriteInfo pWriteInfo)
{
	if((!pPrintf) || (!pWriteInfo))
		return -1;

	bMMap.fw0 = mmpFw0;
	bMMap.fw1 = mmpFw1;
	bMMap.fw2 = mmpFw2;
	bMMap.info = info;

	bHal.bPrintf = pPrintf;
	bHal.bWriteInfo = pWriteInfo;
	return 0;
}
int8_t bLoaderLoop(void)
{
	struct bInfomation bInfo;			
	uint32_t appEnter = 0;

	memcpy(&bInfo, (uint32_t *)bMMap.info, sizeof(struct bInfomation));
	if(bInfo.indification != PARAMES_INDEFICATION)
	{
		bHal.bPrintf("<bootloader>boot info error, use default parames and save it\n");
		bInfo.img = 0;
		bInfo.status = STATUS_NOTEST;
		bInfo.indification = PARAMES_INDEFICATION;

		bHal.bWriteInfo(&bInfo, bMMap.info);
	}
	bHal.bPrintf("<bootloader>status:%d\n", bInfo.status);
	bHal.bPrintf("<bootloader>img:%d\n", bInfo.img);


	switch(bInfo.status)
	{
		case STATUS_NOTEST: 
			appEnter  = bInfo.img == 0 ? bMMap.fw0 : bMMap.fw1;
			break; 
		case STATUS_TESTING: 
			appEnter  = bInfo.img == 0 ? bMMap.fw0 : bMMap.fw1;
			bInfo.status = STATUS_NOTEST;
			bHal.bWriteInfo(&bInfo, bMMap.info);
			break; 
		case STATUS_TEST_READY: 
			bInfo.status = STATUS_TESTING;
			appEnter  = bInfo.img == 0 ? bMMap.fw0 : bMMap.fw1;
			bHal.bWriteInfo(&bInfo, bMMap.info);
			break; 
		default:
			bHal.bPrintf("<bootloader>bootinfo error, fault");
			for(;;);
	}
	
	bHal.bPrintf("<bootloader>jump to 0x%08x\n", appEnter);
	_bJumpToApp(appEnter);
	return 0;
}
