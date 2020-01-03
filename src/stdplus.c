#include "stdplus.h"


struct stdplus *stdplus = NULL;

int8_t stdplus_register(sp_calloc_t sp_calloc,
                        sp_free_t sp_free,
                        sp_printf_t sp_printf)
{
        assert(sp_calloc);
        assert(sp_free);
        assert(sp_printf);

        stdplus = (struct stdplus *)sp_calloc(1, sizeof(struct stdplus)); 
        if(!stdplus)
                return -1;

        stdplus->hook.sp_calloc = sp_calloc;
        stdplus->hook.sp_free = sp_free;
        stdplus->hook.sp_printf = sp_printf;
        return 0;
}

void stdplus_destory(void)
{
        if((stdplus) && (stdplus->hook.sp_free))
               stdplus->hook.sp_free(stdplus); 
                
}

