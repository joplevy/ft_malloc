/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:06:13 by jplevy            #+#    #+#             */
/*   Updated: 2016/01/11 19:29:18 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	if ((tmp = (void*)malloc(sizeof(void) * size)))
		return (ft_memset(tmp, 0, size));
	return (0);
}
