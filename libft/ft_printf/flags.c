/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:54:10 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/28 17:46:09 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_precision(char *str, t_arg at)
{
	char	*ret;
	int		sign;

	if (at.precision < 0)
		return (str);
	ret = str;
	if (ft_strchr("diouxX", at.type))
	{
		sign = ret[0] == '-' ? 1 : 0;
		if (sign == 1)
		{
			ret++;
			ret = ft_strdup(ret);
			free(str);
		}
		while ((int)ft_strlen(ret) < at.precision)
			ret = ft_strjoin_no_leaks("0", ret, ret);
		if (sign == 1)
			ret = ft_strjoin_no_leaks("-", ret, ret);
	}
	if (at.precision == 0 && ft_strchr("diouxX", at.type) && ft_atoi(str) == 0)
		ret = ft_mal_char('\0');
	if (at.type == 's')
		ret = ft_strsub(ret, 0, at.precision);
	return (ret);
}

char	*ft_att(char *str, t_arg at)
{
	char	*ret;

	ret = str;
	if (at.min > 0 && ft_strchr("diouxX", at.type))
		while (*ret == ' ')
			ret++;
	ret = ft_strdup(ret);
	free(str);
	if (ft_strchr(at.flags, '#') && at.type == 'o' && \
		(ft_atoi(ret) != 0 || at.precision != -1))
		ret = ft_strjoin_no_leaks("0", ret, ret);
	if (ft_strchr(at.flags, '#') && at.type == 'x' && ft_atoi(ret) != 0)
		ret = ft_strjoin_no_leaks("0x", ret, ret);
	if (ft_strchr(at.flags, '#') && at.type == 'X' && ft_atoi(ret) != 0)
		ret = ft_strjoin_no_leaks("0X", ret, ret);
	if (ft_strchr(at.flags, '+') && ft_strchr("diu", at.type)\
		&& ft_atoi(ret) >= 0)
		ret = ft_strjoin_no_leaks("+", ret, ret);
	else if (ft_strchr(at.flags, ' ') && ft_strchr("di", at.type) &&\
	ft_atoi(ret) > 0)
		ret = ft_strjoin_no_leaks(" ", ret, ret);
	if (at.min > 0 && ft_strchr("diouxX", at.type))
		while ((int)ft_strlen(ret) < at.min)
			ret = ft_strjoin_no_leaks(" ", ret, ret);
	return (ret);
}

int		ft_before(t_arg at, char *str)
{
	int		sign;

	sign = (ft_strchr(at.flags, '+') || ft_strchr(at.flags, ' ')) &&\
	ft_atoi(str) >= 0 ? 1 : 0;
	sign += ((ft_strchr(at.flags, '#')) ? 1 : 0);
	sign += ((ft_strchr(at.flags, '#') && ft_strchr("xX", at.type)) ? 1 : 0);
	return (sign);
}

char	*ft_min(char *str, t_arg at, int c)
{
	char	*ret;
	int		sign;
	int		s1;

	ret = str;
	s1 = 0;
	if (ft_strchr(at.flags, '0') && !(ft_strchr(at.flags, '-')) &&
		ft_strchr("diouxX", at.type) && at.precision < 0 && str[0] == '-')
		s1 = ft_min_sub(&ret);
	sign = ft_before(at, str);
	while ((int)ft_strlen(ret) + sign + s1 + c < at.min)
	{
		if (ft_strchr(at.flags, '0') && !(ft_strchr(at.flags, '-')) &&\
			((ft_strchr("diouxX", at.type) && at.precision < 0) ||\
			(ft_strchr("sc", at.type))))
			ret = ft_strjoin_no_leaks("0", ret, ret);
		else if (ft_strchr(at.flags, '-'))
			ret = ft_strjoin_no_leaks(ret, " ", ret);
		else
			ret = ft_strjoin_no_leaks(" ", ret, ret);
	}
	return (s1 == 1 ? ft_strjoin_no_leaks("-", ret, ret) : ret);
}

char	*ft_get_adress(void *p, t_arg at)
{
	unsigned long	val;
	char			*ret;
	char			*nb;

	val = (unsigned long)p;
	nb = ft_unsigned_itoa_base((unsigned long long)val,\
		"0123456789abcdef", 0x0000ffffffffffff);
	if (at.precision == 0 && ft_atoi(nb) == 0)
		nb = ft_mal_char(0);
	ret = ft_strjoin_no_leaks("0x", nb, nb);
	return (ret);
}
