/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:05:22 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 14:37:56 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	length;

	if (*s2 == '\0')
		return ((char *)s1);
	length = ft_strlen(s2);
	while (*s1 != '\0' && n-- >= length)
	{
		if (*s1 == *s2 && ft_strncmp(s1, s2, length) == 0)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
