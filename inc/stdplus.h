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
 * @file stdplus.h
 * @brief stdplus头文件
 * @author wangkai
 * @version v0.0.1
 * @date 2019-11-29
 */
#ifndef __STD_PLUS_H
#define __STD_PLUS_H

#include "stdplus_conf.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>


/*-------------------------------------------------------------------------------*/

#ifdef USE_PREVITE_INLINE
#define SP_INLINE __inline
#else
#define SP_INLINE 
#endif

#define CHECK_METHOD \
	assert(stdplus);\
	assert(stdplus->method.sp_printf);

typedef int32_t (*sp_printf_t)(const char * restrict, ...);

struct common_method{
        sp_printf_t sp_printf;
}__attribute__((packed));

struct stdplus{
        struct common_method method;
}__attribute__((packed));


extern struct stdplus *stdplus;
extern int8_t stdplus_register(sp_printf_t sp_printf);

extern void stdplus_destory(void);


/*-------------------------------------------------------------------------------*/
struct listnode 
{
  struct listnode *next;
  struct listnode *prev;
  
  /* private member, use getdata() to retrieve, do not access directly */
  void *data;
}__attribute__((packed));
 
struct list 
{
  struct listnode *head;
  struct listnode *tail;
 
  /* invariant: count is the number of listnodes in the list */
  unsigned int count;
 
  /*
   * Returns -1 if val1 < val2, 0 if equal?, 1 if val1 > val2.
   * Used as definition of sorted for listnode_add_sort
   */
  int (*cmp) (void *val1, void *val2);
 
  /* callback to free user-owned data when listnode is deleted. supplying
   * this callback is very much encouraged!
   */
  void (*del) (void *val);
};
 
#define listnextnode(X) ((X) ? ((X)->next) : NULL)
#define listhead(X) ((X) ? ((X)->head) : NULL)
#define listtail(X) ((X) ? ((X)->tail) : NULL)
#define listcount(X) ((X)->count)
#define list_isempty(X) ((X)->head == NULL && (X)->tail == NULL)
#define listgetdata(X) ( (X)->data)
 
/* Prototypes. */
extern struct list *list_new(void); /* encouraged: set list.del callback on new lists */
extern void list_free (struct list *);
 
extern void listnode_add (struct list *, void *);
extern void listnode_add_sort (struct list *, void *);
extern void listnode_add_after (struct list *, struct listnode *, void *);
extern void listnode_delete (struct list *, void *);
extern struct listnode *listnode_lookup (struct list *, void *);
extern void *listnode_head (struct list *);
 
extern void list_delete (struct list *);
extern void list_delete_all_node (struct list *);
 
extern void list_delete_node (struct list *, struct listnode *);
extern void list_add_node_prev (struct list *, struct listnode *, void *);
extern void list_add_node_next (struct list *, struct listnode *, void *);
extern void list_add_list (struct list *, struct list *);
extern void list_show_allnode(struct list *list);
 
/* List iteration macro. 
 * Usage: for (ALL_LIST_ELEMENTS (...) { ... }
 * It is safe to delete the listnode using this macro.
 */
#define ALL_LIST_ELEMENTS(list,node,nextnode,data) \
  (node) = listhead(list), ((data) = NULL); \
  (node) != NULL && \
    ((data) = listgetdata(node),(nextnode) = node->next, 1); \
  (node) = (nextnode), ((data) = NULL)
 
/* read-only list iteration macro.
 * Usage: as per ALL_LIST_ELEMENTS, but not safe to delete the listnode Only
 * use this macro when it is *immediately obvious* the listnode is not
 * deleted in the body of the loop. Does not have forward-reference overhead
 * of previous macro.
 */
#define ALL_LIST_ELEMENTS_RO(list,node,data) \
  (node) = listhead(list), ((data) = NULL);\
  (node) != NULL && ((data) = listgetdata(node), 1); \
  (node) = listnextnode(node), ((data) = NULL)
 
/* these *do not* cleanup list nodes and referenced data, as the functions
 * do - these macros simply {de,at}tach a listnode from/to a list.
 */
 
/* List node attach macro.  */
#define LISTNODE_ATTACH(L,N) \
  do { \
    (N)->prev = (L)->tail; \
    if ((L)->head == NULL) \
      (L)->head = (N); \
    else \
      (L)->tail->next = (N); \
    (L)->tail = (N); \
    (L)->count++; \
  } while (0)
 
/* List node detach macro.  */
#define LISTNODE_DETACH(L,N) \
  do { \
    if ((N)->prev) \
      (N)->prev->next = (N)->next; \
    else \
      (L)->head = (N)->next; \
    if ((N)->next) \
      (N)->next->prev = (N)->prev; \
    else \
      (L)->tail = (N)->prev; \
    (L)->count--; \
  } while (0)



struct queue *queue_new(const uint32_t node_size, const uint32_t node_count);
int8_t queue_push(struct queue *queue, const void *node);
int8_t queue_pop(struct queue* queue, uint8_t *node);
uint32_t queue_node_count(const struct queue* queue);
void queue_show_allnode(struct queue *queue);


#endif
