/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 12:18:08 by jplevy            #+#    #+#             */
/*   Updated: 2016/06/16 13:48:09 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_lenght(int base, long long int nb)
{
	int			len;
	long long	weight;

	len = 1;
	weight = 1;
	while (nb / weight >= (long long int)base ||\
		nb / weight <= -(long long int)base)
	{
		weight *= base;
		len += 1;
	}
	return (len);
}

int		ft_unsigned_lenght(int base, long long unsigned nb)
{
	int					len;
	long long unsigned	weight;

	len = 1;
	weight = 1;
	while (nb / weight >= (long long unsigned)base)
	{
		weight *= base;
		len += 1;
	}
	return (len);
}

char	*ft_itoa_base(long long int nb, char *base)
{
	int		l;
	int		sign;
	char	*str;

	l = 0;
	sign = nb < 0 ? 1 : 0;
	nb = nb > 0 ? -nb : nb;
	if (nb == 0)
		return (ft_mal_char('0'));
	l = ft_lenght(ft_strlen(base), nb);
	str = (char*)malloc(sizeof(char) * (l + sign + 1));
	str[l + sign] = '\0';
	while (nb != 0)
	{
		str[--l + sign] = base[-(nb % (long long int)ft_strlen(base))];
		nb = nb / (long long int)ft_strlen(base);
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_unsigned_itoa_base(unsigned long long nb, char *base,\
		unsigned long long mask)
{
	int		l;
	char	*str;

	l = 0;
	nb = nb & mask;
	if (nb == 0)
		return (ft_mal_char('0'));
	l = ft_unsigned_lenght(ft_strlen(base), nb);
	str = (char*)malloc(sizeof(char) * (l + 1));
	str[l] = '\0';
	while (nb != 0)
	{
		str[--l] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
	}
	return (str);
}

char	*ft_mal_char(char c)
{
	char	*ret;

	ret = malloc(2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
