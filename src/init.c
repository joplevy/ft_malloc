/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:24:39 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 17:36:08 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_addr_list	*ft_init_big(size_t size)
{
	t_addr_list	*ret;

	if (!(ret = (t_addr_list *)(mmap(0, size + sizeof(t_addr_list), PROT_READ \
	| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ret->content = (void*)((long)ret + (long)sizeof(t_addr_list));
	ret->content_size = size;
	ret->arena = ret;
	ret->next = NULL;
	return (ret);
}

t_addr_list	*ft_init_one_map(size_t node_size)
{
	t_addr_list	*ret;
	t_addr_list	*tmp;
	int			i;

	if (!(ret = (t_addr_list *)(mmap(0, node_size * 128, \
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ft_memset(ret, 0, node_size * 128);
	i = -1;
	tmp = ret;
	while (++i < 128)
	{
		tmp->content = (void*)((long)tmp + (long)sizeof(t_addr_list));
		tmp->content_size = 0;
		tmp->next = (i == 127) ? NULL : (void *)((long)tmp + (long)node_size);
		tmp->arena = (void *)ret;
		tmp = (void *)((long)tmp + (long)node_size);
	}
	return (ret);
}

void		ft_init_sizes(void)
{
	size_t		page_size;

	page_size = getpagesize();
	g_all_infos.page_size = page_size;
	g_all_infos.tiny_size = page_size * 3;
	g_all_infos.tiny_node_size = g_all_infos.tiny_size / 128;
	g_all_infos.small_size = page_size * 33;
	g_all_infos.small_node_size = g_all_infos.small_size / 128;
	if (DEBUG)
		globals_var_log();
}
