/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 22:56:05 by pgourran          #+#    #+#             */
/*   Updated: 2016/11/17 01:51:25 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	join_free_ext(char *s1, char *s2, char mode)
{
	if (s1 && mode == 1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 && mode == 2)
	{
		free(s2);
		s2 = NULL;
	}
	if (s1 && s2 && mode == 0)
	{
		free(s1);
		free(s2);
		s1 = NULL;
		s2 = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, char mode)
{
	int		i;
	int		j;
	char	*out;

	if (((out = ft_strnew(ft_strlen(s1) + ft_strlen((char *)s2))))
		&& mode >= 0 && mode <= 2)
	{
		i = 0;
		j = 0;
		while (s1[i])
		{
			out[i] = s1[i];
			i++;
		}
		while (s2[j])
			out[i++] = s2[j++];
		out[i] = '\0';
		join_free_ext(s1, s2, mode);
		return (out);
	}
	return (NULL);
}
