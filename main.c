/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/19 19:07:50 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"
#include <stdio.h>

int			main(void)
{
	char *str = malloc(5);
	str[0] = 't';
	str[1] = '0';
	str[2] = 't';
	str[3] = 'o';
	str[4] = '\n';
	// show_mapping();
	ft_putstr_fd(str, 1);
	malloc(1025);
	str = realloc(str, 1030);
	str = realloc(str, 1030);
	str = realloc(str, 1030);
	// show_mapping();
	// show_alloc_mem();
	// show_freed_mem();
	// ft_putstr_fd(str, 1);
	// free(NULL);
	free(str);
	str = malloc(1025);
	free(str);

    return (0);
}