/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:18:07 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 18:28:48 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

static void	*hard_realloc(void *ptr, size_t size, size_t n_size)
{
	void	*ret;
	size_t	final_size;

	if (size == n_size)
	{
		if (DEBUG)
			output_r_log("SAME SIZE ", ret, size);
		return (ptr);
	}
	ret = malloc(size);
	final_size = (size > n_size) ? n_size : size;
	ret = ft_memcpy(ret, ptr, final_size);
	free(ptr);
	if (DEBUG)
		output_r_log("HARD ", ret, size);
	return (ret);
}

static void	smooth_realloc(t_addr_list *node, size_t size)
{
	pthread_mutex_lock(&(g_mutex));
	if (size < node->content_size)
		ft_memset((void*)((long)(node->content) + (long)size), 0, \
			node->content_size - size);
	node->content_size = size;
	if (DEBUG)
		output_r_log("TINY OR SMALL ", node->content, node->content_size);
	pthread_mutex_unlock(&(g_mutex));
}

void		*realloc(void *ptr, size_t size)
{
	t_addr_list	*node;
	size_t		node_size;

	if (DEBUG)
		entry_r_log(ptr, size);
	if (((node = ft_find_node(ptr, g_all_infos.tiny_mapping))
			&& (node_size = g_all_infos.tiny_node_size)) \
		|| ((node = ft_find_node(ptr, g_all_infos.small_mapping))
			&& (node_size = g_all_infos.small_node_size)))
	{
		if (DEBUG)
			sizes_r_log(size, node_size);
		if (size > node_size - sizeof(t_addr_list))
			return (hard_realloc(ptr, size, node->content_size));
		smooth_realloc(node, size);
		return (node->content);
	}
	if (ptr)
	{
		return (hard_realloc(ptr, size, ((t_addr_list*)((long)ptr - \
			(long)sizeof(t_addr_list)))->content_size));
	}
	return (hard_realloc(ptr, size, 0));
}
