/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 15:55:27 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 15:51:30 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(int n)
{
	size_t		nb;

	nb = 1;
	while (n >= 10 || n <= -10)
	{
		nb++;
		n = n / 10;
	}
	return (nb);
}

char			*ft_itoa(int n)
{
	size_t	size;
	char	*ret;

	size = ft_size(n) + ((n < 0) ? 1 : 0);
	if (!(ret = ft_strnew(size)))
		return (NULL);
	while (size > 0)
	{
		size--;
		ret[size] = ((n == 0 && ret[size + 1] != '\0') ? \
				'-' : ft_abs(n % 10) + '0');
		n = n / 10;
	}
	return (ret);
}
