/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_leaks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:11:00 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/28 17:13:09 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_no_leaks(char *s1, char *s2, char *tofree)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (tofree)
		free(tofree);
	return (ret);
}
