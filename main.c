/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:38:59 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/17 18:57:17 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"
#include <stdio.h>

int			main(void)
{
	char *str = ft_malloc(5);
	str[0] = 't';
	str[1] = '0';
	str[2] = 't';
	str[3] = 'o';
	str[4] = '\n';
	ft_putstr(str);
	ft_realloc(str, 100);
	ft_putstr(str);
    return (0);
}