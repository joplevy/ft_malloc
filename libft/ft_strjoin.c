/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:24:28 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 15:06:32 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *s;

	if ((s = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		ft_strcat(s, s1);
		ft_strcat(s, s2);
	}
	return (s);
}
