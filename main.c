/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/08/26 17:03:04 by jplevy           ###   ########.fr       */
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

t_mapping ft_init_one_map(size_t size)
{
	t_mapping	ret;
	
	ret.arena = NULL;
	ret.size = 0;
	ret.node_size = 0;
	if ((ret.arena = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		ret.size = size;
		ret.node_size = size / 128;
	}
	return (ret);
}

int	ft_init_mapping()
{
	size_t page_size;

	page_size = getpagesize();
	if ((g_all_infos.tiny_mapping = ft_init_one_map(page_size * 2)).arena == NULL)
		return (-1);
	if ((g_all_infos.small_mapping = ft_init_one_map(page_size * 32)).arena == NULL)
	{
		munmap(g_all_infos.tiny_mapping.arena, g_all_infos.tiny_mapping.size);
		return (-1);
	}
	printf("tiny mapping:\n\t\t%p\n\t\t%zu\n\t\t%zu\nsmall mapping:\n\t\t%p\n\t\t%zu\n\t\t%zu\n", g_all_infos.tiny_mapping.arena, g_all_infos.tiny_mapping.size, g_all_infos.tiny_mapping.node_size, g_all_infos.small_mapping.arena, g_all_infos.small_mapping.size, g_all_infos.small_mapping.node_size);
	return (0);
}

void *ft_malloc(size_t size)
{
	// g_all_infos.first = 1;
	if (!g_all_infos.loaded && ft_init_mapping() < 0)
	{
		printf("failed loading\n");
		return(NULL);
	}
	else
		printf("loaded\n");
	if (size > 0)
		return (mmap(0, 4046, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
	return (NULL);
}

int			main(void)
{
	ft_malloc(0);
	printf("%p\n", ft_malloc(1));
	printf("%p\n", ft_malloc(0));
	ft_malloc(0);
	ft_malloc(0);
    return (0);
}