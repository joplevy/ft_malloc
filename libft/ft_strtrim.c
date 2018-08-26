/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:51:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 15:31:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
		i++;
	j = ft_strlen(s);
	if (i == j)
		return (ft_strdup(""));
	while (s[j - 1] == '\n' || s[j - 1] == ' ' || s[j - 1] == '\t')
		j--;
	return (ft_strsub(s, i, j - i));
}
