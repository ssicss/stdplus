#include "stdplus.h"


/*---------------------------------------------*/
/*---------------static queue-------------------*/
/*---------------------------------------------*/

/*---------------------------------------------*/
/* empt*/
//   |  front	
//   |  rear
//   |    0	1	2	3	4
//   |  
/*---------------------------------------------*/
//
//
//
/*---------------------------------------------*/
/* push ABC to queue*/
//   |  front			rear	
//   |    0	1	2	3	4
//   |    A     B       C
/*---------------------------------------------*/
//
//
//
/*---------------------------------------------*/
/* push D to queue, queue is full*/
//   |  front				rear	
//   |    0	1	2	3	4
//   |    A     B       C	D
/*---------------------------------------------*/
//
//
/*---------------------------------------------*/
/* pop*/
//   |  	front			rear	
//   |    0	1	2	3	4
//   |          B       C	D
/*---------------------------------------------*/
//
//
//
/*---------------------------------------------*/
/* push E to queue, queue is full*/
//   |	rear  	front			
//   |    0	1	2	3	4
//   |          B       C	D	E
/*---------------------------------------------*/
//
//
//
//
//
//
//


struct queue{
	uint32_t front;
	uint32_t rear;

        uint32_t node_count;
        uint32_t node_size;
	uint8_t	*buf;
};

#define NODE_ADDR(node) (queue->buf +(queue->node_size * node)) 
			



struct queue *queue_new(const uint32_t node_size, const uint32_t node_count)
{
        assert(stdplus);
	if((!node_size)||(!node_count))
		return NULL;

        struct queue *queue =(struct queue *)CALLOC_METHOD(1, sizeof(struct queue)); 
        if(!queue)
		return NULL;

        uint8_t *buf=(uint8_t *)CALLOC_METHOD( node_count, 
				node_size ); 
        if(!buf)
		return NULL;
	
	queue->node_count= node_count;
	queue->node_size = node_size;
	queue->buf = buf;
	queue->front = 0;
	queue->rear = 0;

        return queue;
}

static  bool is_queue_empty(const struct queue *queue)
{
        assert(stdplus);
        assert(queue);

	return queue->front == queue->rear ? true : false;
}

static  bool is_queue_full(const struct queue *queue)
{
        assert(stdplus);
        assert(queue);

	return queue->front == ((queue->rear+1) % queue->node_count) ? true : false;
}

int8_t queue_push(struct queue *queue, const void *node)
{
        assert(stdplus);
        assert(queue);
        assert(node);

	if(is_queue_full(queue))
		return -1;

	MEMCPY_METHOD( NODE_ADDR(queue->rear), 
			node, 
			queue->node_size );
	queue->rear = (queue->rear + 1)%queue->node_count;
	
	return 0;
}

int8_t queue_pop(struct queue* queue, uint8_t *node)
{
        assert(stdplus);
        assert(queue);
        assert(node);

	if(is_queue_empty(queue))
		return -1;

	MEMCPY_METHOD( node,
			NODE_ADDR(queue->front), 
			queue->node_size );
	memset( NODE_ADDR(queue->front),
	     	0,
	     	queue->node_size );
	queue->front = (queue->front + 1)%queue->node_count;
	
	return 0;
}

uint32_t queue_node_count(const struct queue* queue)
{
	assert(queue);
	return queue->front > queue->rear ? \
		(queue->rear + queue->node_count) - queue->front: \
		queue->rear - queue->front;
}

void queue_show_allnode(struct queue *queue)
{
	assert(queue);
	
	stdplus->method.sp_printf("--queue --\n");
	stdplus->method.sp_printf("<info>--node count:%d, node size:%d, front:%d, rear:%d, buf:%d--\n",
				queue->node_count,
				queue->node_size,
				queue->front,
				queue->rear,
				queue->buf);
	stdplus->method.sp_printf("<status>--total:%d --\n", queue_node_count(queue));

}




