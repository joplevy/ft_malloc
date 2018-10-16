/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/16 21:25:01 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"
#include <stdio.h>

int			main(void)
{
	int i;
	// void *ptr[128];	
	// t_arena_container *list;
	i = -1;
	while (++i < 100)
	{
		printf("%p\n", ft_malloc(100));
	}
	// ft_malloc(2047);
	show_alloc_mem();
	// ptr[0] = malloc(0);
	// show_alloc_mem();
	// i = -1;
	// while (++i < 128)
	// {
	// 	ft_free(ptr[i]);
	// }
	// show_alloc_mem();
	// ptr[0] = malloc(0);
	// ft_putstr("\na\n");
	// ft_putptr(ptr);
	// ft_putstr("\n");
	// ft_putstr("\nb\n");
	// free(ptr);
	// show_alloc_mem();
    return (0);
}