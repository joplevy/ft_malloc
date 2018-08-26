/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 16:10:48 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 09:37:35 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*temp1;
	unsigned char			*temp2;
	size_t					i;

	i = 0;
	temp1 = (unsigned char *)src;
	temp2 = (unsigned char *)dst;
	while (i < n)
	{
		temp2[i] = temp1[i];
		if (temp2[i] == (unsigned char)c)
			return ((void *)&(temp2[i + 1]));
		i++;
	}
	return (NULL);
}
