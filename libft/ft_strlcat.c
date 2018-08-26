/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:48:51 by jplevy            #+#    #+#             */
/*   Updated: 2016/01/11 15:18:06 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && str && str[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	s_s1;
	size_t	s_s2;
	size_t	n_size;

	s_s1 = ft_strnlen(s1, n);
	s_s2 = ft_strlen(s2);
	n_size = n - s_s1;
	s1 += s_s1;
	if (n_size > 0)
	{
		ft_strncpy(s1, s2, n_size);
		s1[n_size - 1] = '\0';
	}
	return (s_s1 + s_s2);
}
