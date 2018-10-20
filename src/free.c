/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 17:58:10 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

static int	ft_deallocate(t_addr_list **from, t_addr_list **to, \
				t_addr_list *node, t_addr_list *prev)
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
	if (prev)
		prev->next = node->next;
	ft_memset(node->content, 0, node->content_size);
	node->content_size = 0;
	ordered_put_node(to, node);
	if (clear == 1)
		ft_clear_list(to, node);
	return (1);
}

static int	ft_small_free(void *ptr, t_addr_list **map, t_addr_list **e_map)
{
	t_addr_list			*tmp;
	t_addr_list			*prev;

	tmp = *map;
	prev = NULL;
	while (tmp)
	{
		if ((long)(tmp->content) <= (long)ptr \
			&& (long)(tmp->content) + (long)(tmp->content_size) >= (long)ptr)
			return (ft_deallocate(map, e_map, tmp, prev));
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}

static int	ft_other_free(void *ptr)
{
	t_addr_list *tmp;
	t_addr_list *prev;

	prev = NULL;
	tmp = g_all_infos.other_mapping;
	while (tmp)
	{
		if ((long)(tmp->content) <= (long)ptr \
			&& (long)(tmp->content) + (long)(tmp->content_size) >= (long)ptr)
		{
			if (tmp == g_all_infos.other_mapping)
				g_all_infos.other_mapping = tmp->next;
			if (prev)
				prev->next = tmp->next;
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
	if (DEBUG)
		entry_f_log(ptr);
	if (ft_small_free(ptr, &(g_all_infos.tiny_mapping), \
		&(g_all_infos.e_tiny_mapping)) >= 0 \
		|| ft_small_free(ptr, &(g_all_infos.small_mapping), \
		&(g_all_infos.e_small_mapping)) >= 0)
	{
		if (DEBUG)
			output_f_log(ptr, " type SMALL | TINY ");
		pthread_mutex_unlock(&(g_mutex));
		return ;
	}
	if ((ft_other_free(ptr)) >= 0)
	{
		if (DEBUG)
			output_f_log(ptr, " type LARGE ");
		pthread_mutex_unlock(&(g_mutex));
		return ;
	}
	if (DEBUG)
		ft_putstr_log("Could not free ptr\n\n");
	pthread_mutex_unlock(&(g_mutex));
}
