/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:38:42 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 17:53:24 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_all_infos g_all_infos = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0,
	0
};
pthread_mutex_t	g_mutex;

void		*ft_allocate(t_addr_list **from, t_addr_list **to, size_t size)
{
	t_addr_list	*node;

	node = *from;
	node->content_size = size;
	*from = node->next;
	ordered_put_node(to, node);
	if (DEBUG)
		output_m_log(node->content, node->content_size);
	return (node->content);
}

static void	*manage_smalls(size_t size, t_addr_list **map, \
	t_addr_list **e_map, size_t node_size)
{
	if (!(*e_map))
		*e_map = ft_init_one_map(node_size);
	return (ft_allocate(e_map, map, size));
}

void		*malloc(size_t size)
{
	t_addr_list	*big;
	void		*ret;

	pthread_mutex_lock(&(g_mutex));
	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();
	if (DEBUG)
		entry_m_log(size);
	if (size <= g_all_infos.tiny_node_size - sizeof(t_addr_list))
		ret = manage_smalls(size, &(g_all_infos.tiny_mapping), \
			&(g_all_infos.e_tiny_mapping), g_all_infos.tiny_node_size);
	else if (size <= g_all_infos.small_node_size - sizeof(t_addr_list))
		ret = manage_smalls(size, &(g_all_infos.small_mapping), \
			&(g_all_infos.e_small_mapping), g_all_infos.small_node_size);
	else
	{
		big = ft_init_big(size);
		ordered_put_node(&(g_all_infos.other_mapping), big);
		if (DEBUG && big)
			output_m_log(big->content, big->content_size);
		ret = (big) ? big->content : NULL;
	}
	pthread_mutex_unlock(&(g_mutex));
	return (ret);
}

void		*calloc(size_t count, size_t size)
{
	void	*ret;

	if (DEBUG)
		ft_putstr_log("calloc call\n");
	ret = malloc(count * size);
	if (DEBUG)
		ft_putstr_log("calloc ret\n");
	return (ret);
}
