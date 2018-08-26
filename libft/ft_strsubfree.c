/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 23:02:38 by pgourran          #+#    #+#             */
/*   Updated: 2016/05/25 23:18:42 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char	*out;
	int		i;

	i = 0;
	if ((out = ft_strnew(len)))
	{
		while (len-- > 0)
			out[i++] = s[start++];
		out[i] = '\0';
		if (s)
			free(s);
		return (out);
	}
	return (NULL);
}
