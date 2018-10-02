/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/02 19:06:27 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int			main(void)
{
	int i;
	void *ptr;	
	// t_arena_container *list;

	i = -1;
	while (++i <= 129)
	{
		if (i == 127)
			ptr = ft_malloc(i);
		else
			ft_malloc(i);
	}
	show_alloc_mem();
	ft_free(ptr);
    return (0);
}