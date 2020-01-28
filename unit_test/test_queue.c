#include "test_queue.h"


int test_queue_main(void)
{
	struct node{
		int a;
		//...
	};

	struct queue *queue = queue_new( sizeof(struct node), 5);

	printf("1> begin queue test\n");
	queue_show_allnode(queue);


	printf("1> push node\n");
	struct node node0 = {100};
	struct node node1 = {101};
	struct node node2 = {102};
	queue_push(queue, &node0);
	queue_push(queue, &node1);
	queue_push(queue, &node2);
	queue_show_allnode(queue);

	printf("2> pop node\n");
	uint8_t buf[sizeof(struct node)];
	queue_pop(queue, buf);
	printf("pop data:%d\n", ((struct node *)buf)->a);
	queue_show_allnode(queue);

	printf("3> end\n");
	return 0;

}
