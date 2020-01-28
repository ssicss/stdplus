#include "test_linklist.h"
#include "stdplus.h"


int test_linklist_main(void)
{
	
	struct list *list = list_new();

	printf("1> begin list test\n");
	list_show_allnode(list);


	printf("\n2> add node to list\n");
	struct  private_date{
		int a;
		//...
	};
	struct private_date node0 = {
		0
	};
	struct private_date node1 = {
		0
	};
	listnode_add(list, &node0);
	listnode_add(list, &node1);
	list_show_allnode(list);

	printf("\n3> delete node0\n");
	listnode_delete(list, &node0);
	list_show_allnode(list);

	return 0;
}
