/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altnorme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:11:00 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/28 17:13:09 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_min_sub(char **ret)
{
	char	*tmp;

	tmp = *ret;
	(*ret)++;
	*ret = ft_strdup(*ret);
	free(tmp);
	return (1);
}

void	free_flags(t_arg args)
{
	if (args.flags)
		free(args.flags);
	if (args.modifier)
		free(args.modifier);
}

char	*ft_strjoin_no_leaks(char *s1, char *s2, char *tofree)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (tofree)
		free(tofree);
	return (ret);
}

char	*ft_strsub_no_leaks(char const *s, unsigned int start, size_t len, \
	char *tofree)
{
	char	*ret;

	ret = ft_strsub(s, start, len);
	if (tofree)
		free(tofree);
	return (ret);
}
