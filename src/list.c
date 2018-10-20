/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:12:40 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 17:51:45 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_addr_list	*ft_find_node(void *ptr, t_addr_list *map)
{
	t_addr_list			*tmp;

	tmp = map;
	while (tmp)
	{
		if (tmp->content == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_addr_list	*get_last_node(t_addr_list *tmp, t_addr_list *arena)
{
	while (tmp)
	{
		if (!(tmp->next) || tmp->next->arena != arena)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void		ft_clear_list(t_addr_list **empty, t_addr_list *node)
{
	t_addr_list *tmp;
	t_addr_list *first_node;
	t_addr_list *last_node;
	t_addr_list *prev;

	prev = NULL;
	tmp = *empty;
	while (tmp && tmp->arena != node->arena)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	first_node = tmp;
	last_node = get_last_node(tmp, node->arena);
	if (first_node == *empty)
		*empty = last_node->next;
	if (prev)
		prev->next = last_node->next;
	munmap(first_node, (size_t)(((long)(first_node->next) - \
		(long)first_node) * 128));
}

void		put_node_after(t_addr_list *node, t_addr_list *ref)
{
	if (ref->next)
	{
		node->next = ref->next;
	}
	ref->next = node;
}

void		ordered_put_node(t_addr_list **to, t_addr_list *node)
{
	t_addr_list	*tmp;

	if (!(node))
		return ;
	node->next = ((*to) && (long)((*to)->content) > (long)(node->content)) \
		? (*to) : NULL;
	if (!(*to) || (long)((*to)->content) > (long)(node->content))
	{
		*to = node;
		return ;
	}
	tmp = *to;
	while (tmp->next && (long)(tmp->next->content) < (long)(node->content))
		tmp = tmp->next;
	put_node_after(node, tmp);
}
