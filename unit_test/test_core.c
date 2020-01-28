#include "stdplus.h"
#include "test_linklist.h"
#include "test_queue.h"
#include <string.h>


int main(int argc, char *argv[])
{
        stdplus_register(printf);

	test_linklist_main();
	test_queue_main();

        stdplus_destory();
        return 0;
}
