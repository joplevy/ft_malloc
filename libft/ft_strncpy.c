/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 18:19:11 by jplevy            #+#    #+#             */
/*   Updated: 2016/01/05 18:22:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	int		isend;

	i = 0;
	isend = 0;
	while (i < n)
	{
		if (isend == 0 && src[i] == '\0')
			isend = 1;
		dst[i] = (isend == 1) ? '\0' : src[i];
		i++;
	}
	return (dst);
}
