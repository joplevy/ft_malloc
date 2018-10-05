/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/05 19:15:35 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int			main(void)
{
	int i;
	void *ptr;	
	// t_arena_container *list;

	i = -1;
	show_alloc_mem();
	while (++i <= 2)
	{
		if (i == 2)
			ptr = malloc(i);
		else
		{
			ptr = ptr;
			malloc(i);
		}
	}
	show_alloc_mem();
	free(ptr);
    return (0);
}