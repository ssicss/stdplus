#include "stdplus.h"
#include <string.h>


int main(int argc, char *argv[])
{
        stdplus_register(calloc, free, printf);
        stdplus_destory();
        return 0;
}
