#include "stdplus.h"


struct stdplus *stdplus = NULL;

int8_t stdplus_register(sp_printf_t sp_printf)
{
        assert(sp_printf);

        stdplus = (struct stdplus *)CALLOC_METHOD(1, sizeof(struct stdplus)); 
        if(!stdplus)
                return -1;

        stdplus->method.sp_printf = sp_printf;
        return 0;
}

void stdplus_destory(void)
{
	FREE_METHOD(stdplus); 
}

