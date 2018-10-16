/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:38:42 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/16 21:02:51 by jplevy           ###   ########.fr       */
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

// t_addr_list				*ft_init_zones(size_t size)
// {
// 	t_addr_list	*ret;
// 	t_addr_list	*tmp;
// 	void	*map;
// 	int		i;

// 	if (!(map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) \
// 	|| !(ret =(t_addr_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
// 		return (NULL);
// 	i = -1;
// 	tmp = ret;
// 	while (++i < 128)
// 	{
// 		tmp->content = map;
// 		map += size / 128;
// 		tmp->content_size = 0;
// 		tmp->next = (i < 127) ? (t_addr_list *)((long)tmp + (long)sizeof(t_addr_list)) : ret;
// 		tmp->next->prev = tmp;
// 		// printf("tmp=%p and ret=%p and content=%p\n", tmp, ret, tmp->content);
// 		tmp = tmp->next;
// 	}
// 	// printf("tmp=%p and ret=%p\n", tmp, ret);
// 	return (ret);
// }

// t_arena_container	*ft_init_one_map(size_t size)
// {
// 	t_arena_container	*cont;
	
// 	cont = NULL;
// 	if (size == g_all_infos.tiny_size || size == g_all_infos.small_size)
// 	{
// 		if ((cont = (size == g_all_infos.tiny_size) ? g_all_infos.tiny_mapping : g_all_infos.small_mapping) == NULL || cont->arena_id % (g_all_infos.page_size / sizeof(t_arena_container)) == 0)
// 		{
// 			if (!(cont = (t_arena_container *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
// 				return (NULL);
// 		}
// 		else
// 		{
// 			cont = (t_arena_container *)((long)cont + (long)sizeof(t_arena_container));
// 		}
// 	}
// 	if (!(cont->zones = ft_init_zones(size)))
// 		return (NULL);
// 	cont->first = cont->zones;
// 	cont->next = NULL;
// 	cont->prev = NULL;
// 	cont->arena_id = 0;
// 	cont->nb_alloc = 0;
// 	return (cont);
// }

// t_addr_list		*ft_init_big(size_t size)
// {
// 	t_addr_list	*ret;

// 	if (!(ret = (t_addr_list *)(mmap(0, size + sizeof(t_addr_list), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
// 		return (NULL);
// 	ret->content = (void*)((long)ret + (long)sizeof(t_addr_list));
// 	ret->content_size = size;
// 	ret->next = NULL;
// 	ret->prev = NULL;
// 	return (ret);
// }

#include <stdio.h>

t_addr_list		*ft_init_one_map(size_t node_size)
{
	t_addr_list	*ret;
	t_addr_list	*tmp;
	int			i;

	if (!(ret = (t_addr_list *)(mmap(0, node_size * 128, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ft_memset(ret, 0, node_size * 128);
	i = -1;
	tmp = ret;
	while (++i < 128)
	{
		tmp->content = (void*)((long)tmp + (long)sizeof(t_addr_list));
		tmp->content_size = 0;
		tmp->next = (i == 127) ? NULL : (void *)((long)tmp + (long)node_size);
		tmp->prev = (i == 0) ? NULL : (void *)((long)tmp - (long)node_size);
		// printf("%p, %p, %zu, %p, %p, %zu, %zu\n", tmp, tmp->content, tmp->content_size, tmp->next, tmp->prev, sizeof(t_addr_list), node_size);
		tmp = (void *)((long)tmp + (long)node_size);
	
	}
	return (ret);
}

void	ft_init_sizes()
{
	size_t		page_size;

	page_size = getpagesize();
	g_all_infos.page_size = page_size;
	g_all_infos.tiny_size = page_size * 4;
	g_all_infos.tiny_node_size = g_all_infos.tiny_size / 128;
	g_all_infos.small_size = page_size * 64;
	g_all_infos.small_node_size = g_all_infos.small_size / 128;
}

// void 	*ft_malloc(size_t size)
// {
// 	t_arena_container	*cont;
// 	t_addr_list			*big;
// 	void				*ret;

// 	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
// 		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
// 		ft_init_sizes();

// 	if (size <= g_all_infos.tiny_node_size)
// 	{
// 		if (!(g_all_infos.tiny_mapping) || g_all_infos.tiny_mapping->nb_alloc == 128)
// 		{
// 			// printf("initiatizing tiny sizeof (t_addr_list) is %d\n", (int)sizeof(t_arena_container));
// 			if (!(cont = ft_init_one_map(g_all_infos.tiny_size)))
// 				return (NULL);
// 			cont->next = g_all_infos.tiny_mapping;
// 			if (g_all_infos.tiny_mapping)
// 				g_all_infos.tiny_mapping->prev = cont;
// 			cont->arena_id = (cont->next) ? cont->next->arena_id + 1 : 1;
// 			g_all_infos.tiny_mapping = cont;
// 		}
// 		g_all_infos.tiny_mapping->nb_alloc += 1;
// 		g_all_infos.tiny_mapping->zones->content_size = (size > 0) ? size : 1;
// 		ret = g_all_infos.tiny_mapping->zones->content;
// 		g_all_infos.tiny_mapping->zones = g_all_infos.tiny_mapping->zones->next;
// 		return (ret);
// 	}
// 	else if (size <= g_all_infos.small_node_size)
// 	{
// 		if (!(g_all_infos.small_mapping) || g_all_infos.small_mapping->nb_alloc == 128)
// 		{
// 			// printf("initiatizing small sizeof (t_addr_list) is %d\n", (int)sizeof(t_arena_container));
// 			if (!(cont = ft_init_one_map(g_all_infos.small_size)))
// 				return (NULL);
// 			cont->next = g_all_infos.small_mapping;
// 			cont->arena_id = (cont->next) ? cont->next->arena_id + 1 : 1;
// 			g_all_infos.small_mapping = cont;
// 		}
// 		g_all_infos.small_mapping->nb_alloc += 1;
// 		g_all_infos.small_mapping->zones->content_size = size;
// 		ret = g_all_infos.small_mapping->zones->content;
// 		g_all_infos.small_mapping->zones = g_all_infos.small_mapping->zones->next;
// 		return (ret);
// 	}
// 	else
// 	{
// 		// printf("initiatizing big\n");
// 		if (!(big = ft_init_big(size)))
// 			return (NULL);
// 		if (g_all_infos.other_mapping)
// 			g_all_infos.other_mapping->prev = big;
// 		big->next = g_all_infos.other_mapping;
// 		g_all_infos.other_mapping = big;
// 		return (g_all_infos.other_mapping->content);
// 	}
// 	return (NULL);
// }

void	*ft_allocate(t_addr_list **from, t_addr_list **to, size_t size)
{
	t_addr_list	*node;

	node = *from;
	node->content_size = size;
	// ft_change_list();
	*from = node->next;
	if (*from)
		(*from)->prev = NULL;
	node->next = *to;
	if (*to)
		(*to)->prev = node;
	*to = node;
	return (node->content);
}

void 	*ft_malloc(size_t size)
{
	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();

	if (size <= g_all_infos.tiny_node_size - sizeof(t_addr_list))
	{
		if (!(g_all_infos.e_tiny_mapping))
			g_all_infos.e_tiny_mapping = ft_init_one_map(g_all_infos.tiny_node_size);
		return (ft_allocate(&(g_all_infos.e_tiny_mapping), &(g_all_infos.tiny_mapping), size));
	}
	else if (size <= g_all_infos.small_node_size - sizeof(t_addr_list))
	{
		if (!(g_all_infos.e_small_mapping))
			g_all_infos.e_small_mapping = ft_init_one_map(g_all_infos.small_node_size);
		return (ft_allocate(&(g_all_infos.e_small_mapping), &(g_all_infos.small_mapping), size));
	}
	else
		return (NULL);
}