/*
 * Part of the Conic project - robot arm controller
 *
 * Generic list implementation, inspired by linux kernel lists
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_LIST_H
#define MISC_LIST_H

struct list_node {
	struct list_node *next;
	struct list_node *prev;
};

#define INIT_LIST_NODE(name) \
	{ \
		.next = &(name), \
		.prev = &(name) \
	}

#define DECLARE_LIST(name) \
	struct list_node name = INIT_LIST_NODE(name)

static inline void list_insert(struct list_node *prev, \
		struct list_node *next, struct list_node *node)
{
	prev->next = node;
	node->prev = prev;
	next->prev = node;
	node->next = next;
}

static inline void list_add_before(struct list_node *head, struct list_node *node)
{
	list_insert(head->prev, head, node);
}

static inline void list_add_after(struct list_node *head, struct list_node *node)
{
	list_insert(head, head->next, node);
}

static inline void list_delete(struct list_node *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;

	node->prev = NULL;
	node->next = NULL;
}

static inline struct list_node *list_first(struct list_node *node)
{
	return node->next;
}

static inline struct list_node *list_last(struct list_node *node)
{
	return node->prev;
}

static inline bool list_next_node(struct list_node *head, \
					struct list_node **node_pointer)
{
	if ((*node_pointer)->next != head) {
		*node_pointer = (*node_pointer)->next;
		return true;
	}

	return false;
}

#define list_forward(ptr, list) \
	for (ptr = (list)->next; ptr != (list); ptr = ptr->next)

#define list_backward(ptr, list) \
	for (ptr = (list)->prev; ptr != (list); ptr = ptr->prev)

#define list_forward_safe(ptr, n, list) \
	for (ptr = (list)->next, n = ptr->next; ptr != (list); \
		ptr = n, n = ptr->next)

#define list_backward_safe(ptr, n, list) \
	for (ptr = (list)->prev, n = ptr->prev; ptr != (list); \
		ptr = n, n = ptr->prev)

#endif

