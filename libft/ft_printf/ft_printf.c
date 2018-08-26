/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:54:10 by jplevy            #+#    #+#             */
/*   Updated: 2016/09/08 08:16:25 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_get_str(t_arg argtype, t_types val)
{
	char	*ret;

	ret = NULL;
	if (argtype.type == 'd' || argtype.type == 'i')
		ret = ft_right_itoa(val, argtype.modifier);
	else if (ft_strchr("ouxX", argtype.type) != NULL)
		ret = ft_unsigned_itoa_base(val.ull, ft_get_base(argtype.type),\
			ft_get_mask(argtype.modifier));
	else if (argtype.type == 's' && ft_strcmp(argtype.modifier, "l") == 0)
		ret = ft_get_wstr((wchar_t*)val.p);
	else if (argtype.type == 's')
		ret = (val.p) ? ft_strdup(val.p) : NULL;
	else if (argtype.type == 'c' && ft_strcmp(argtype.modifier, "l") == 0)
		ret = ft_get_wchar(val.ui);
	else if (argtype.type == 'c')
		ret = ft_mal_char(val.c);
	else if (argtype.type == '%')
		ret = ft_mal_char('%');
	else if (argtype.type == 'p')
		ret = ft_get_adress(val.p, argtype);
	return (ret);
}

void	ft_check_argtype(t_arg *argtype)
{
	if (ft_strchr("SCDOU", argtype->type) != NULL)
	{
		argtype->type = argtype->type + 32;
		argtype->modifier = ft_strdup("l");
	}
}

int		ft_get_arg(t_arg *argtype, va_list ap, t_list1 **str)
{
	t_types	val;
	char	*tmp;
	int		c;

	ft_check_argtype(argtype);
	val = ft_va_arg(*argtype, ap);
	c = (val.c == 0 && argtype->type == 'c') ? 1 : 0;
	tmp = ft_get_str(*argtype, val);
	if (tmp)
	{
		tmp = ft_precision(tmp, *argtype);
		tmp = ft_min(tmp, *argtype, c);
		tmp = ft_att(tmp, *argtype);
	}
	ft_list_push_back(str, tmp, c);
	return (0);
}

t_list1	*ft_get_list(const char *format, va_list ap)
{
	int		i;
	int		s;
	t_list1	*str;
	t_arg	args;

	i = 0;
	str = NULL;
	while (format[i])
	{
		s = 0;
		while (format[i + s] != '%' && format[i + s])
			s++;
		if (s > 0)
			ft_list_push_back(&str, ft_strsub(format, i, s), 0);
		i += s;
		if (format[i] == '%')
		{
			i++;
			args = ft_get_argtype(format, &i);
			if (ft_get_arg(&args, ap, &str) == -1)
				return (NULL);
			free_flags(args);
		}
	}
	return (str);
}

int		ft_printf(const char *format, ...)
{
	t_list1	*str;
	va_list	ap;

	va_start(ap, format);
	str = ft_get_list(format, ap);
	if (!str)
		return (0);
	va_end(ap);
	return (ft_putlist(str));
}
