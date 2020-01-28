/* This file is part of stdplus.
 * 
 * 
 * stdplus is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * stdplus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 * 
 * You should have received a copy of the Lesser GNU General Public License
 * along with stdplus.  If not, see <https://www.gnu.org/licenses/>.
 */
/**
 * @file stdplus_linklist.c
 * @brief 链表功能实现
 * @author wangkai
 * @version v0.1
 * @date 2019-07-24
 */

#include "stdplus.h"
 

static SP_INLINE struct listnode *listnode_new (void)
{
        assert(stdplus);
        return (struct listnode *)CALLOC_METHOD(1,sizeof (struct listnode));
}
 
static SP_INLINE void listnode_free (struct listnode *node)
{
        assert(stdplus);
        assert(node);
        FREE_METHOD(node);
}

struct list *list_new (void)
{
        assert(stdplus);
        return (struct list *)CALLOC_METHOD(1, sizeof(struct list));
}
 
void list_free (struct list *list)
{
        assert(stdplus);
        assert(list);
        FREE_METHOD(list);
}

void listnode_add (struct list *list, void *val)
{
        assert (list);
        assert (val);

        struct listnode *node;
        node = listnode_new ();
 
        node->prev = list->tail;
        node->data = val;

        if (list->head == NULL)
                list->head = node;
        else
                list->tail->next = node;

        list->tail = node;
        list->count++;
}
 
void listnode_add_sort (struct list *list, void *val)
{
        assert(list);
        assert(val);

        struct listnode *n;
        struct listnode *new;

        assert (val != NULL);

        new = listnode_new ();
        new->data = val;

        if (list->cmp)
        {
                for (n = list->head; n; n = n->next)
                {
                        if ((*list->cmp) (val, n->data) < 0)
                        {	    
                                new->next = n;
                                new->prev = n->prev;

                                if (n->prev)
                                        n->prev->next = new;
                                else
                                        list->head = new;
                                n->prev = new;
                                list->count++;
                                return;
                        }
                }
        }

        new->prev = list->tail;

        if (list->tail)
        list->tail->next = new;
        else
        list->head = new;

        list->tail = new;
        list->count++;
}
 
void listnode_add_after (struct list *list, struct listnode *pp, void *val)
{
        assert (list);
        assert (pp);
        assert (val);

        struct listnode *nn;
  
  
        nn = listnode_new ();
        nn->data = val;

        if (pp == NULL)
        {
                if (list->head)
                        list->head->prev = nn;
                else
                        list->tail = nn;

                nn->next = list->head;
                nn->prev = pp;

                list->head = nn;
        }
        else
        {
                if (pp->next)
                        pp->next->prev = nn;
                else
                        list->tail = nn;

                nn->next = pp->next;
                nn->prev = pp;

                pp->next = nn;
        }
        list->count++;
}
 
 
void listnode_delete (struct list *list, void *val)
{
        assert(list);
        assert(val);
        struct listnode *node;

        for (node = list->head; node; node = node->next)
        {
                if (node->data == val)
                {
                        if (node->prev)
                                node->prev->next = node->next;
                        else
                                list->head = node->next;

                        if (node->next)
                                node->next->prev = node->prev;
                        else
                                list->tail = node->prev;

                        list->count--;
                        listnode_free (node);
                        return;
                }
        }
}
 
void *listnode_head (struct list *list)
{
        assert(list);
        struct listnode *node;

        node = list->head;

        if (node)
                return node->data;
        return NULL;
}
 
void list_delete_all_node (struct list *list)
{
        assert(list);

        struct listnode *node;
        struct listnode *next;

        for (node = list->head; node; node = next)
        {
                next = node->next;
                if (list->del)
                        (*list->del) (node->data);
                listnode_free (node);
        }
        list->head = list->tail = NULL;
        list->count = 0;
}
 
void list_delete (struct list *list)
{
        assert(list);
        list_delete_all_node (list);
        list_free (list);
}
 
struct listnode *listnode_lookup (struct list *list, void *data)
{
        assert(list);
        assert(data);
        struct listnode *node;

        for (node = listhead(list); node; node = listnextnode (node))
        if (data == listgetdata (node))
                return node;
        return NULL;
}
 
void list_delete_node (struct list *list, struct listnode *node)
{
        assert(list);
        assert(node);

        if (node->prev)
                node->prev->next = node->next;
        else
                list->head = node->next;
        if (node->next)
                node->next->prev = node->prev;
        else
        list->tail = node->prev;
        list->count--;
        listnode_free (node);
}
 
void list_add_node_prev (struct list *list, struct listnode *current, void *val)
{
        assert(list);
        assert(current);
        assert(val);

        struct listnode *node;

        node = listnode_new ();
        node->next = current;
        node->data = val;

        if (current->prev == NULL)
                list->head = node;
        else
                current->prev->next = node;

        node->prev = current->prev;
        current->prev = node;
        list->count++;
}
 
void list_add_node_next (struct list *list, struct listnode *current, void *val)
{
        assert(list);
        assert(current);
        assert(val);
        struct listnode *node;

        node = listnode_new ();
        node->prev = current;
        node->data = val;

        if (current->next == NULL)
                list->tail = node;
        else
                current->next->prev = node;

        node->next = current->next;
        current->next = node;

        list->count++;
}
 
void list_add_list (struct list *list, struct list *m)
{
        struct listnode *n;

        for (n = listhead (m); n; n = listnextnode (n))
                listnode_add (list, n->data);
}

void list_show_allnode(struct list *list)
{
	int i = 0;

        assert(list);
	CHECK_METHOD
	if(list->count == 0){
		stdplus->method.sp_printf("no node is this list\n");
		return;
	}

	struct listnode *node = list->head;
	stdplus->method.sp_printf("<node>\t<point>\n");
	while(node->next != NULL)
	{
		stdplus->method.sp_printf("  %d   0x%x\n", i++, node);
		node = node->next;
	}
	stdplus->method.sp_printf("  %d   0x%x\n", i++, node);
}

