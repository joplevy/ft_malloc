/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 13:43:20 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 14:27:41 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cur;

	cur = (char *)s + ft_strlen(s);
	while (*cur != c)
	{
		if (cur == s)
			return (NULL);
		cur--;
	}
	return (cur);
}
