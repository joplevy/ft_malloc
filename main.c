/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/09/14 14:41:49 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_list				*ft_init_zones(size_t size)
{
	t_list	*ret;
	t_list	*tmp;
	void	*map;
	int		i;

	if (!(map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) \
	|| !(ret =(t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	i = -1;
	tmp = ret;
	while (++i < 128)
	{
		tmp->content = map;
		map += size / 128;
		tmp->content_size = 0;
		tmp->next = (i < 127) ? (t_list *)((long)tmp + (long)sizeof(t_list)) : ret;
		// printf("tmp=%p and ret=%p and content=%p\n", tmp, ret, tmp->content);
		tmp = tmp->next;
	}
	// printf("tmp=%p and ret=%p\n", tmp, ret);
	return (ret);
}

t_arena_container	*ft_init_one_map(size_t size)
{
	t_arena_container	*cont;
	
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
	cont->arena_id = 0;
	cont->nb_alloc = 0;
	return (cont);
}

void	ft_init_sizes()
{
	size_t		page_size;

	page_size = getpagesize();
	g_all_infos.page_size = page_size;
	g_all_infos.tiny_size = page_size * 2;
	g_all_infos.tiny_node_size = g_all_infos.tiny_size / 128;
	g_all_infos.small_size = page_size * 32;
	g_all_infos.small_node_size = g_all_infos.small_size / 128;
}

void 	*ft_malloc(size_t size)
{
	t_arena_container	*cont;
	void				*ret;

	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();

	if (size <= g_all_infos.tiny_node_size)
	{
		if (!(g_all_infos.tiny_mapping) || g_all_infos.tiny_mapping->nb_alloc == 128)
		{
			// printf("initiatizing tiny sizeof (t_list) is %d\n", (int)sizeof(t_arena_container));
			if (!(cont = ft_init_one_map(g_all_infos.tiny_size)))
				return (NULL);
			cont->next = g_all_infos.tiny_mapping;
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
			// printf("initiatizing small sizeof (t_list) is %d\n", (int)sizeof(t_arena_container));
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
		printf("initiatizing big\n");
	}
	return (NULL);
}

void		print_mem(t_arena_container *zones, char *type)
{
	t_arena_container	*tmp;
	t_list				*tmp_l;

	// TINY : 0xA0000
	// 0xA0020 - 0xA004A : 42 octets
	// 0xA006A - 0xA00BE : 84 octets
	// SMALL : 0xAD000
	// 0xAD020 - 0xADEAD : 3725 octets
	// LARGE : 0xB0000
	// 0xB0020 - 0xBBEEF : 48847 octets
	// Total : 52698 octets
	tmp = zones;
	while (tmp)
	{
		printf("%s : 0x%05X\n", type, (long)(((t_list *)tmp->first)->content) & 0xFFFFF);
		tmp_l = tmp->zones;
		while(tmp_l)
		{
			printf("0x%05X - 0x%05X : %d octets\n", (long)tmp_l->content & 0xFFFFF, (long)(tmp_l->content + tmp_l->content_size) & 0xFFFFF, tmp_l->content_size);
			tmp_l = (tmp_l->next == tmp->first) ? NULL : tmp_l->next;
		}
		tmp = tmp->next;
	}
}

void		show_alloc_mem()
{
	// faire le tri des zones
	if (g_all_infos.tiny_mapping)
		print_mem(g_all_infos.tiny_mapping, "TINY");
	if (g_all_infos.small_mapping)
		print_mem(g_all_infos.small_mapping, "SMALL");
}

int			main(void)
{
	int i;
	t_arena_container *list;

	i = -1;
	while (++i <= 128)
		ft_malloc(i);
	show_alloc_mem();
		// printf("malloc nb %i at %p\n", i, ft_malloc(i));
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