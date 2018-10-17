/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/17 19:02:03 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_addr_list	*get_last_node(t_addr_list *tmp, t_addr_list *arena)
{
	while(tmp)
	{
		if  (!(tmp->next) || tmp->next->arena != arena)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_clear_list(t_addr_list **empty, t_addr_list *node)
{
	t_addr_list *tmp;
	t_addr_list *first_node;
	t_addr_list *last_node;
	
	tmp = *empty;
	while (tmp && tmp->arena != node->arena)
		tmp = tmp->next;
	first_node = tmp;
	last_node = get_last_node(tmp, node->arena);
	if (first_node == *empty)
		*empty = last_node->next;
	if (first_node && first_node->prev)
		first_node->prev->next = last_node->next;
	if (last_node && last_node->next)
		last_node->next->prev = first_node->prev;
	munmap(first_node, (size_t)(((long)(first_node->next) - (long)first_node) * 128));
}

int		ft_deallocate(t_addr_list **from, t_addr_list **to, t_addr_list *node)
{
	int		clear;

	clear = 0;
	if (*from == node)
		*from = node->next;
	if (((node->prev && node->prev->arena != node->arena) \
		|| !(node->prev))
		&& ((node->next && node->next->arena != node->arena) \
		|| !(node->next)))
		clear = 1;
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	ft_memset(node->content, 0, node->content_size);
	node->content_size = 0;
	ordered_put_node(to, node);
	if (clear == 1)
		ft_clear_list(to, node);
	return (1);
}

int		ft_small_free(void *ptr, t_addr_list **map, t_addr_list **e_map)
{
	t_addr_list			*tmp;

	tmp = *map;
	while (tmp)
	{
		if (tmp->content == ptr)
			return (ft_deallocate(map, e_map, tmp));
		tmp = tmp->next;
	}
	return (-1);
}

int		ft_other_free(void *ptr)
{
	t_addr_list *tmp;

	tmp = g_all_infos.other_mapping;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (tmp == g_all_infos.other_mapping)
				g_all_infos.other_mapping = tmp->next;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			munmap(tmp, tmp->content_size + sizeof(t_addr_list));
			return (0);
		}
		tmp = tmp->next;
	}
	return (-1);
}

void		ft_free(void *ptr)
{
	if (ft_small_free(ptr, &(g_all_infos.tiny_mapping), &(g_all_infos.e_tiny_mapping)) >= 0 || ft_small_free(ptr, &(g_all_infos.small_mapping), &(g_all_infos.e_small_mapping)) >= 0)
		return;
	if (ft_other_free(ptr) >= 0)
		return;
}
