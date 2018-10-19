/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/19 14:25:42 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>
// #include <stdio.h>
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
	// if (last_node && last_node->next)
		// last_node->next->prev = first_node->prev;
	munmap(first_node, (size_t)(((long)(first_node->next) - (long)first_node) * 128));
}

int		ft_deallocate(t_addr_list **from, t_addr_list **to, t_addr_list *node,  t_addr_list *prev)
{
	int		clear;

	clear = 0;
	if (*from == node)
		*from = node->next;
	if (((prev && prev->arena != node->arena) \
		|| !(prev))
		&& ((node->next && node->next->arena != node->arena) \
		|| !(node->next)))
		clear = 1;
	// if (node->next)
	// 	node->next->prev = prev;
	if (prev)
		prev->next = node->next;
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
	t_addr_list			*prev;

	// if (*map == g_all_infos.tiny_mapping)
		// printf("ptr to be freed is tiny\n");
	// else
		// printf("ptr to be freed is small\n");
	tmp = *map;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == ptr)
			return (ft_deallocate(map, e_map, tmp, prev));
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}

int		ft_other_free(void *ptr)
{
	t_addr_list *tmp;
	t_addr_list *prev;

	// printf("ptr to be freed is big\n");
	tmp = g_all_infos.other_mapping;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (tmp == g_all_infos.other_mapping)
				g_all_infos.other_mapping = tmp->next;
			if (prev)
				prev->next = tmp->next;
			// if (tmp->next)
				// tmp->next->prev = tmp->prev;
			munmap(tmp, tmp->content_size + sizeof(t_addr_list));
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&(g_mutex));
	if (ft_small_free(ptr, &(g_all_infos.tiny_mapping), &(g_all_infos.e_tiny_mapping)) >= 0 || ft_small_free(ptr, &(g_all_infos.small_mapping), &(g_all_infos.e_small_mapping)) >= 0)
	{
		pthread_mutex_unlock(&(g_mutex));
		return;
	}
	ft_other_free(ptr);
	pthread_mutex_unlock(&(g_mutex));
}
