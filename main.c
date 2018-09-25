/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/09/16 17:51:39 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_addr_list				*ft_init_zones(size_t size)
{
	t_addr_list	*ret;
	t_addr_list	*tmp;
	void	*map;
	int		i;

	if (!(map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) \
	|| !(ret =(t_addr_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	i = -1;
	tmp = ret;
	while (++i < 128)
	{
		tmp->content = map;
		map += size / 128;
		tmp->content_size = 0;
		tmp->next = (i < 127) ? (t_addr_list *)((long)tmp + (long)sizeof(t_addr_list)) : ret;
		tmp->next->prev = tmp;
		// printf("tmp=%p and ret=%p and content=%p\n", tmp, ret, tmp->content);
		tmp = tmp->next;
	}
	// printf("tmp=%p and ret=%p\n", tmp, ret);
	return (ret);
}

t_arena_container	*ft_init_one_map(size_t size)
{
	t_arena_container	*cont;
	
	cont = NULL;
	if (size == g_all_infos.tiny_size || size == g_all_infos.small_size)
	{
		if ((cont = (size == g_all_infos.tiny_size) ? g_all_infos.tiny_mapping : g_all_infos.small_mapping) == NULL || cont->arena_id % (g_all_infos.page_size / sizeof(t_arena_container)) == 0)
		{
			if (!(cont = (t_arena_container *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
				return (NULL);
		}
		else
		{
			cont = (t_arena_container *)((long)cont + (long)sizeof(t_arena_container));
		}
	}
	if (!(cont->zones = ft_init_zones(size)))
		return (NULL);
	cont->first = cont->zones;
	cont->next = NULL;
	cont->prev = NULL;
	cont->arena_id = 0;
	cont->nb_alloc = 0;
	return (cont);
}

t_addr_list		*ft_init_big(size_t size)
{
	t_addr_list	*ret;

	if (!(ret = (t_addr_list *)(mmap(0, size + sizeof(t_addr_list), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ret->content = (void*)((long)ret + (long)sizeof(t_addr_list));
	ret->content_size = size;
	ret->next = NULL;
	ret->prev = NULL;
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

void 	*ft_malloc(size_t size)
{
	t_arena_container	*cont;
	t_addr_list			*big;
	void				*ret;

	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();

	if (size <= g_all_infos.tiny_node_size)
	{
		if (!(g_all_infos.tiny_mapping) || g_all_infos.tiny_mapping->nb_alloc == 128)
		{
			// printf("initiatizing tiny sizeof (t_addr_list) is %d\n", (int)sizeof(t_arena_container));
			if (!(cont = ft_init_one_map(g_all_infos.tiny_size)))
				return (NULL);
			cont->next = g_all_infos.tiny_mapping;
			if (g_all_infos.tiny_mapping)
				g_all_infos.tiny_mapping->prev = cont;
			cont->arena_id = (cont->next) ? cont->next->arena_id + 1 : 1;
			g_all_infos.tiny_mapping = cont;
		}
		g_all_infos.tiny_mapping->nb_alloc += 1;
		g_all_infos.tiny_mapping->zones->content_size = (size > 0) ? size : 1;
		ret = g_all_infos.tiny_mapping->zones->content;
		g_all_infos.tiny_mapping->zones = g_all_infos.tiny_mapping->zones->next;
		return (ret);
	}
	else if (size <= g_all_infos.small_node_size)
	{
		if (!(g_all_infos.small_mapping) || g_all_infos.small_mapping->nb_alloc == 128)
		{
			// printf("initiatizing small sizeof (t_addr_list) is %d\n", (int)sizeof(t_arena_container));
			if (!(cont = ft_init_one_map(g_all_infos.small_size)))
				return (NULL);
			cont->next = g_all_infos.small_mapping;
			cont->arena_id = (cont->next) ? cont->next->arena_id + 1 : 1;
			g_all_infos.small_mapping = cont;
		}
		g_all_infos.small_mapping->nb_alloc += 1;
		g_all_infos.small_mapping->zones->content_size = size;
		ret = g_all_infos.small_mapping->zones->content;
		g_all_infos.small_mapping->zones = g_all_infos.small_mapping->zones->next;
		return (ret);
	}
	else
	{
		// printf("initiatizing big\n");
		if (!(big = ft_init_big(size)))
			return (NULL);
		if (g_all_infos.other_mapping)
			g_all_infos.other_mapping->prev = big;
		big->next = g_all_infos.other_mapping;
		g_all_infos.other_mapping = big;
	}
	return (NULL);
}

size_t		print_mem(t_arena_container *zones, char *type)
{
	t_arena_container	*tmp;
	t_addr_list				*tmp_l;
	t_addr_list				*st_tmp_l;
	size_t 				tot_size;

	tmp = zones;
	while (tmp->next)
		tmp = tmp->next;
	tot_size = 0;
	while (tmp)
	{
		ft_printf("%s : %p\n", type, (((t_addr_list *)tmp->first)->content));
		tmp_l = tmp->zones;
		st_tmp_l = tmp_l;
		while(tmp_l)
		{
			tot_size += tmp_l->content_size;
			if (tmp_l->content_size > 0)
				ft_printf("%p - %p : %zu octets\n", (tmp_l->content), (tmp_l->content + tmp_l->content_size), tmp_l->content_size);
			tmp_l = (tmp_l->next == st_tmp_l) ? NULL : tmp_l->next;
		}
		tmp = tmp->prev;
	}
	return (tot_size);
}

size_t		print_big_mem(t_addr_list *zones, char *type)
{
	t_addr_list		*tmp;
	size_t 				tot_size;

	tmp = zones;
	while (tmp->next)
		tmp = tmp->next;
	tot_size = 0;
	while (tmp)
	{
		ft_printf("%s : %p\n%p - %p : %zu octets\n", type, tmp, tmp->content, tmp->content + tmp->content_size, tmp->content_size);
		tot_size += tmp->content_size;
		tmp = tmp->prev;
	}
	return (tot_size);
}

void		show_alloc_mem()
{
	// faire le tri des zones
	size_t 				tot_size;

	tot_size = 0;	
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping, "TINY");
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL");
	if (g_all_infos.other_mapping)
		tot_size += print_big_mem(g_all_infos.other_mapping, "LARGE");
	ft_printf("Total : %zu octets\n", tot_size);
}

// void		free(void *ptr)
// {
// dans malloc si le container est full, verifier que les autres ont pas eu de free depuis avant de refaire un container
// }

int			main(void)
{
	int i;
	// t_arena_container *list;

	i = -1;
	while (++i <= 50)
		ft_malloc(i + 2048);
		// printf("malloc nb %i at %p\n", i, ft_malloc(i));
	show_alloc_mem();
	// list = g_all_infos.tiny_mapping;
	// i = 0;
	// while (list->next)
	// {
	// 	printf("i = %d list = %p nb_aloc = %d id = %d\n", i, list, list->nb_alloc, list->arena_id);
	// 	list = list->next;
	// 	i++;
	// }
	// printf("i = %d list = %p nb_aloc = %d id = %d\n", i, list, list->nb_alloc, list->arena_id);
	// i = -1;
	// while (++i <= 10 * 128)
	// 	ft_malloc(150);
	// i = -1;
	// while (++i <= 170 * 128)
	// 	ft_malloc(1500);
	// ft_malloc(10000);
	// ft_malloc(10000);
	// ft_malloc(10000);
    return (0);
}