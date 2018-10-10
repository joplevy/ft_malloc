/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/10 17:35:28 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int			main(void)
{
	int i;
	void *ptr;	
	// t_arena_container *list;

	i = -1;
	while (++i < 124)
		malloc(i);
	show_alloc_mem();
	ptr = malloc(0);
	ft_putptr(ptr);
	ft_putstr("\n");
	free(ptr);
	ptr = malloc(0);
	ft_putptr(ptr);
	ft_putstr("\n");
	free(ptr);
	// show_alloc_mem();
    return (0);
}