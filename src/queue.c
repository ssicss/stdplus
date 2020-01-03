#include "stdplus.h"

struct node{
        struct node *next;
        void *buf;
};

struct queue{
        struct node *front;
        struct node *rear;

        uint32_t size;
};



struct queue *queue_new(uint32_t node_size)
{
        assert(stdplus);
        struct queue *queue =(struct queue *)stdplus->hook.sp_calloc(1, sizeof(struct queue)); 
        if(queue)
                queue->size = node_size;
        return queue;
}

void queue_free(struct queue *queue)
{
        assert(stdplus);
        assert(queue);
        stdplus->hook.sp_free(queue);
}


int8_t queue_push(struct queue *queue, void *date)
{
        assert(stdplus);
        assert(queue);

        struct node *node = (struct node *)stdplus->hook.sp_calloc(1, sizeof(struct node));        
        if(!node)
                return -1;

        node->buf = date;
        queue->rear->next = node;
        queue->rear = node;
        return 0;
}

int8_t queue_pop(struct queue *queue, void *date)
{
        assert(stdplus);
        assert(queue);
        assert(date);

        if(queue->rear == queue->front)
                return -1;
        
        memcpy(date, queue->front->buf, queue->size );
        stdplus->hook.sp_free(queue->front);
        queue->front = queue->front->next;
        return 0;
}




