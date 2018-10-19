/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/18 15:46:12 by jplevy           ###   ########.fr       */
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
	ft_putstr(str);
	str = realloc(str, 100);
	// show_mapping();
	ft_putstr(str);
    return (0);
}