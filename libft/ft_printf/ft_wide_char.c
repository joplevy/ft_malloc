/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wide_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:21:10 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/30 14:17:57 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned char	ft_get_oct(int c, int i, int j)
{
	if (i == 0 && j == 1)
		return ((unsigned char)c);
	if (i == j - 1)
		return ((unsigned char)((c & 63) + 128));
	if (j == 2 && i == 0)
		return ((unsigned char)(((c >> 6) & 95) + 192));
	if (i == j - 2)
		return ((unsigned char)(((c >> 6) & 63) + 128));
	if (j == 3 && i == 0)
		return ((unsigned char)(((c >> 12) & 15) + 224));
	if (i == j - 3)
		return ((unsigned char)(((c >> 12) & 63) + 128));
	else
		return ((unsigned char)(((c >> 18) & 7) + 240));
}

char			*ft_get_wstr(wchar_t *s)
{
	char	*ret;
	char	*tmp;
	char	*tmp1;

	ret = NULL;
	while (*s)
	{
		tmp = ret;
		tmp1 = ft_get_wchar(*s);
		if (ret)
		{
			ret = ft_strjoin(ret, tmp1);
			free(tmp);
		}
		else
			ret = ft_strdup(tmp1);
		free(tmp1);
		s++;
	}
	return (ret);
}

char			*ft_get_wchar(unsigned int c)
{
	int				l;
	int				i;
	unsigned char	*ret;

	if (c <= 127)
		l = 1;
	else if (c <= 2047)
		l = 2;
	else if (c <= 65535)
		l = 3;
	else
		l = 4;
	ret = malloc(l);
	i = -1;
	while (++i < l)
		ret[i] = ft_get_oct(c, i, l);
	return ((char *)ret);
}
