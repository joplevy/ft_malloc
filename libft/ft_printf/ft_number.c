/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:54:10 by jplevy            #+#    #+#             */
/*   Updated: 2016/06/17 14:41:54 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_types				ft_va_arg_2(t_arg argtype, va_list ap)
{
	t_types	ret;

	if (ft_strchr("di", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "l") == 0)
		ret.l = va_arg(ap, long int);
	else if (ft_strchr("ouxX", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "l") == 0)
		ret.ul = va_arg(ap, unsigned long);
	else if (ft_strchr("di", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "j") == 0)
		ret.im = va_arg(ap, long long int);
	else if (ft_strchr("ouxX", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "j") == 0)
		ret.uim = va_arg(ap, unsigned long long);
	else if (ft_strchr("di", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "ll") == 0)
		ret.ll = va_arg(ap, long long int);
	else if (ft_strchr("ouxX", argtype.type) != NULL &&\
		ft_strcmp(argtype.modifier, "ll") == 0)
		ret.ull = va_arg(ap, unsigned long long);
	else if (ft_strchr("sp", argtype.type) != NULL)
		ret.p = va_arg(ap, void*);
	else
		ret.p = NULL;
	return (ret);
}

t_types				ft_va_arg(t_arg at, va_list ap)
{
	t_types	ret;

	if (ft_strchr("di", at.type) != NULL && at.modifier == NULL)
		ret.i = va_arg(ap, int);
	else if ((ft_strchr("ouxX", at.type) != NULL && !(at.modifier)) ||\
		(at.type == 'c' && ft_strcmp(at.modifier, "l") == 0))
		ret.ui = va_arg(ap, unsigned int);
	else if (at.type == 'c' || (ft_strchr("di", at.type) &&\
		ft_strcmp(at.modifier, "hh") == 0))
		ret.c = (char)va_arg(ap, int);
	else if (ft_strchr("ouxX", at.type) && ft_strcmp(at.modifier, "hh") == 0)
		ret.uc = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strchr("di", at.type) && ft_strcmp(at.modifier, "h") == 0)
		ret.s = (short int)va_arg(ap, int);
	else if (ft_strchr("ouxX", at.type) && ft_strcmp(at.modifier, "h") == 0)
		ret.us = (unsigned short)va_arg(ap, int);
	else if (ft_strchr("di", at.type) && ft_strcmp(at.modifier, "z") == 0)
		ret.st = va_arg(ap, long int);
	else if (ft_strchr("ouxX", at.type) && ft_strcmp(at.modifier, "z") == 0)
		ret.sst = va_arg(ap, unsigned long);
	else
		ret = ft_va_arg_2(at, ap);
	return (ret);
}

char				*ft_get_base(char type)
{
	if (type == 'o')
		return ("01234567");
	else if (type == 'u')
		return ("0123456789");
	else if (type == 'x')
		return ("0123456789abcdef");
	else if (type == 'X')
		return ("0123456789ABCDEF");
	else
		return (NULL);
}

unsigned long long	ft_get_mask(char *modifier)
{
	if (modifier == NULL)
		return (0x00000000ffffffff);
	else if (modifier[0] == 'h' && modifier[1] == 'h')
		return (0x00000000000000ff);
	else if (modifier[0] == 'h' && !(modifier[1]))
		return (0x000000000000ffff);
	else if (modifier[0] == 'l' && !(modifier[1]))
		return (0xffffffffffffffff);
	else
		return (0xffffffffffffffff);
}

char				*ft_right_itoa(t_types val, char *modifier)
{
	if (modifier == NULL)
		return (ft_itoa_base(val.i, "0123456789"));
	else if (modifier[0] == 'h' && modifier[1] == 'h')
		return (ft_itoa_base(val.c, "0123456789"));
	else if (modifier[0] == 'h')
		return (ft_itoa_base(val.s, "0123456789"));
	else if (modifier[0] == 'l' && modifier[1] == 'l')
		return (ft_itoa_base(val.ll, "0123456789"));
	else if (modifier[0] == 'j')
		return (ft_itoa_base(val.im, "0123456789"));
	else if (modifier[0] == 'z')
		return (ft_itoa_base(val.st, "0123456789"));
	else
		return (ft_itoa_base(val.l, "0123456789"));
}
