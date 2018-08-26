/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 15:13:30 by jplevy            #+#    #+#             */
/*   Updated: 2016/01/05 17:05:06 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp1;
	char	*temp2;

	temp1 = (char *)src;
	temp2 = (char *)dst;
	while (n > 0)
	{
		temp2[n - 1] = temp1[n - 1];
		n--;
	}
	return (dst);
}
