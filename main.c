/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/09/07 19:30:06 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <sys/mman.h>
// #include <sys/resource.h>

// int main(void)
// {
//     // struct rlimit limit;
//     int limit_ret = getrlimit(RLIMIT_DATA);
//     void *toto = mmap(0, 4046, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//     printf("%p, %d\n", toto, limit_ret);
//     return (0);
// }
#include "ft_malloc.h"

t_arena_container	*ft_init_one_map(size_t size)
{
	t_arena_container	*cont;
	// int		i;
	
	printf("start\n");
	if (size == g_all_infos.tiny_size)
	{
		if ((cont = g_all_infos.tiny_mapping) == NULL)
		{
			printf("lol\n");
			if (!(cont = (t_arena_container *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
				return (NULL);
		}
		else
		{
			cont = (t_arena_container *)((long)cont + (long)sizeof(t_arena_container));
			printf("%p\n", cont);
		}
	}
	cont->zones = NULL;
	// cont->next = NULL;
	cont->nb_alloc = 0;
	return (cont);
	// 		if (!(g_all_infos.tiny_mapping = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = g_all_infos.tiny_mapping;
	// 	}
	// 	else
	// 	{
	// 		i = 0;
	// 		while (++i && list->next)
	// 			list = list->next;
	// 		if (i == 0 || i != (g_all_infos.page_size / (sizeof(t_list))))
	// 			list->next = (void*)((long)list + (long)sizeof(t_list));
	// 		else if (!(list->next = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = list->next;
	// 	}
	// }
	// else if (size == g_all_infos.small_size)
	// {
	// 	if (!(list = g_all_infos.small_mapping))
	// 	{
	// 		if (!(g_all_infos.small_mapping = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = g_all_infos.small_mapping;
	// 	}
	// 	else
	// 	{
	// 		i = 0;
	// 		while (++i && list->next)
	// 			list = list->next;
	// 		if (i == 0 || i != (g_all_infos.page_size / (sizeof(t_list))))
	// 			list->next = (void*)((long)list + (long)sizeof(t_list));
	// 		else if (!(list->next = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = list->next;
	// 	}
	// }
	// else
	// {
	// 	if (!(list = g_all_infos.other_mapping))
	// 	{
	// 		if (!(g_all_infos.other_mapping = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = g_all_infos.other_mapping;
	// 	}
	// 	else
	// 	{
	// 		i = 0;
	// 		while (++i && list->next)
	// 			list = list->next;
	// 		if (i == 0 || i != (g_all_infos.page_size / (sizeof(t_list))))
	// 			list->next = (void*)((long)list + (long)sizeof(t_list));
	// 		else if (!(list->next = (t_list *)(mmap(0, g_all_infos.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
	// 			return (NULL);
	// 		list = list->next;
	// 	}
	// }
	// if (!(list->content = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
	// {
	// 	printf("cant allocate\n");
	// 	return (NULL);
	// }
	// list->content_size = size;
	// list->next = NULL;
	// printf("end\n");	
	// return (list);
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
	printf("page_size = %zu\ntiny_size = %zu\ntiny_node_size = %zu\nsmall_size = %zu\nsmall_node_size = %zu\n",\
	g_all_infos.page_size,
	g_all_infos.tiny_size,
	g_all_infos.tiny_node_size,
	g_all_infos.small_size,
	g_all_infos.small_node_size
	);
}

void 	*ft_malloc(size_t size)
{
	// static t_header head = {0, 0, NULL, NULL, NULL, 0, 0, 0, 0, 0};
	t_arena_container	*cont;
	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();
	// if (!(g_all_infos))
	// {
	// 	if (!(g_all_infos = mmap(0, g_all_infoss.tiny_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
	// 		return (NULL);
	// 	g_all_infos->nb_tiny = 0;
	// 	g_all_infos->nb_small = 0;
	// }
	if (size <= g_all_infos.tiny_node_size)
	{
		if (!(g_all_infos.tiny_mapping) || g_all_infos.tiny_mapping->nb_alloc == 128)
		{
			printf("initiatizing tiny sizeof (t_list) is %d\n", (int)sizeof(t_arena_container));
			if (!(cont = ft_init_one_map(g_all_infos.tiny_size)))
				return (NULL);
			cont->next = g_all_infos.tiny_mapping;
			printf("%p %p %p\n", cont, cont->next, g_all_infos.tiny_mapping);
			g_all_infos.tiny_mapping = cont;
			printf("%p %p %p\n", cont, cont->next, g_all_infos.tiny_mapping);
			
			// int j = -1;
			// t_list *li = g_all_infos.tiny_mapping;
			// while (++j < g_all_infos.nb_tiny / 128)
			// {
			// 	// printf("node nb %i at %p is %p\n", j, li, li->content);
			// 	li = li->next;
			// }
			// printf("node nb %i at %p is %p\n", j, li, li->content);
		}
		g_all_infos.tiny_mapping->nb_alloc += 1;
		// printf("give tiny malloc");
		// g_all_infos.nb_tiny += 1;
		// printf("loaded\n");
	}
	// else if (size <= g_all_infos.small_node_size)
	// {
	// 	if (!(g_all_infos.small_mapping) || (g_all_infos.nb_small != 0 && g_all_infos.nb_small % 128 == 0))
	// 	{
	// 		printf("initiatizing small\n");
	// 		if (!(ft_init_one_map(g_all_infos.small_size)))
	// 			return (NULL);
	// 		int i = -1;
	// 		t_list *l = g_all_infos.small_mapping;
	// 		while (++i < g_all_infos.nb_small / 128)
	// 		{
	// 			// printf("node nb %i at %p is %p\n", i, l, l->content);
	// 			l = l->next;
	// 		}
	// 		printf("node nb %i at %p is %p\n", i, l, l->content);
	// 	}
	// 	g_all_infos.nb_small += 1;
	// 	// printf("loaded\n");
	// }
	// else
	// {
	// 	printf("initiatizing big\n");
	// 	if (!(ft_init_one_map(size)))
	// 			return (NULL);
	// }
	return (NULL);
}

int			main(void)
{
	int i;
	t_arena_container *list;

	i = -1;
	while (++i <= 1256)
		ft_malloc(0);
	list = g_all_infos.tiny_mapping;
	i = -1;
	while (++i  && list->next)
	{
		printf("i = %d list = %p nb_aloc = %d\n", i, list, list->nb_alloc);
		list = list->next;
	}
	printf("i = %d list = %p nb_aloc = %d\n", i, list, list->nb_alloc);
	i = -1;
	while (++i <= 170 * 128)
		ft_malloc(150);
		i = -1;
	while (++i <= 170 * 128)
		ft_malloc(1500);
	// ft_malloc(10000);
	// ft_malloc(10000);
	// ft_malloc(10000);
    return (0);
}