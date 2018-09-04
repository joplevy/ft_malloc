/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/09/04 18:27:13 by jplevy           ###   ########.fr       */
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

t_list	*ft_init_one_map(size_t size)
{
	t_list	*list;
	
	if (size == g_all_infos.tiny_size)
	{
		if (!(list = g_all_infos.tiny_mapping))
		{
			if (!(g_all_infos.tiny_mapping = (t_list *)(mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
				return (NULL);
			list = g_all_infos.tiny_mapping;
		}
		else
		{
			list->next = list + sizeof(t_list);
			list = list->next;
		}
	}
	else if (size == g_all_infos.small_size)
	{
		if (!(list = g_all_infos.small_mapping))
		{
			if (!(g_all_infos.small_mapping = (t_list *)(mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
				return (NULL);
			list = g_all_infos.small_mapping;
		}
		else
		{
			list->next = list + sizeof(t_list);
			list = list->next;
		}
	}
	else
	{
		if (!(list = g_all_infos.other_mapping))
		{
			if (!(g_all_infos.other_mapping = (t_list *)(mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
				return (NULL);
			list = g_all_infos.other_mapping;
		}
		else
		{
			list->next = list + sizeof(t_list);
			list = list->next;
		}
	}
	if (!(list->content = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	list->content_size = size;
	list->next = NULL;
	
	return (list);
}

void	ft_init_sizes()
{
	size_t page_size;

	page_size = getpagesize();
	g_all_infos.tiny_size = page_size * 2;
	g_all_infos.tiny_node_size = g_all_infos.tiny_size / 128;
	g_all_infos.small_size = page_size * 32;
	g_all_infos.small_node_size = g_all_infos.small_size / 128;
}

void 	*ft_malloc(size_t size)
{
	static t_header *head =  NULL;

	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();
	if (!(head))
	{
		if (!(head = mmap(0, g_all_infos.tiny_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
			return (NULL);
		head->nb_tiny = 0;
		head->nb_small = 0;
	}
	if (size <= g_all_infos.tiny_node_size)
	{
		if (!(g_all_infos.tiny_mapping) || (head->nb_tiny != 0 && head->nb_tiny % 128 == 0))
		{
			printf("initiatizing tiny\n");
			if (!(ft_init_one_map(g_all_infos.tiny_size)))
				return (NULL);
		}
		head->nb_tiny += 1;
		printf("loaded\n");
	}
	else if (size <= g_all_infos.small_node_size)
	{
		if (!(g_all_infos.small_mapping) || (head->nb_small != 0 && head->nb_small % 128 == 0))
		{
			printf("initiatizing small\n");
			if (!(ft_init_one_map(g_all_infos.small_size)))
				return (NULL);
		}
		head->nb_small += 1;
		printf("loaded\n");
	}
	else
	{
		printf("initiatizing big\n");
		if (!(ft_init_one_map(size)))
				return (NULL);
	}
	return (NULL);
}

int			main(void)
{
	int i;

	i = -1;
	while (++i <= 128)
		ft_malloc(0);
	i = -1;
	while (++i <= 128)
		ft_malloc(150);
	ft_malloc(10000);
	ft_malloc(10000);
	ft_malloc(10000);
    return (0);
}