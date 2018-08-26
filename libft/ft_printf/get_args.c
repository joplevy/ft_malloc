/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:11:00 by jplevy            #+#    #+#             */
/*   Updated: 2016/09/08 07:00:23 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list1	*ft_create_elem(void *data, int c)
{
	t_list1	*el;

	if ((el = (t_list1*)malloc(sizeof(t_list1))))
	{
		el->data = data;
		el->c = c;
		el->next = NULL;
	}
	return (el);
}

void	ft_list_push_back(t_list1 **begin_list, void *data, int c)
{
	t_list1 *list;

	list = *begin_list;
	if (!(list))
		*begin_list = ft_create_elem(data, c);
	else
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_elem(data, c);
	}
}

int		ft_putlist(t_list1 *str)
{
	int		i;
	t_list1	*leaks;

	i = 0;
	while (str)
	{
		if (str->data)
		{
			i += ft_strlen(str->data);
			ft_putstr(str->data);
			free(str->data);
			i += str->c;
			if (str->c == 1)
				ft_putchar(0);
		}
		else
		{
			i += 6;
			ft_putstr("(null)");
		}
		leaks = str;
		str = str->next;
		free(leaks);
	}
	return (i);
}

t_arg	ft_arginit(void)
{
	t_arg	el;

	el.flags = NULL;
	el.min = 0;
	el.precision = -1;
	el.modifier = NULL;
	el.type = '\0';
	return (el);
}

t_arg	ft_get_argtype(const char *str, int *i)
{
	int		k;
	t_arg	arg;

	arg = ft_arginit();
	k = 0;
	while (ft_strchr("#0- +", str[*i + k]) != NULL)
		k++;
	arg.flags = ft_strsub(str, *i, k);
	(*i) += k - 1;
	while (ft_isdigit(str[++(*i)]) == 1)
		arg.min = (arg.min * 10) + str[*i] - '0';
	if (str[*i] == '.')
	{
		arg.precision = 0;
		while (ft_isdigit(str[++(*i)]))
			arg.precision = (arg.precision * 10) + str[*i] - '0';
	}
	if (ft_strchr("lhjz", str[*i]) != NULL)
		arg.modifier = ft_strsub(str, (*i)++, 1);
	if ((str[*i] == 'l' || str[*i] == 'h') && str[*i] == str[*i - 1])
		arg.modifier = ft_strsub_no_leaks(str, ++(*i) - 2, 2, arg.modifier);
	if (ft_strchr("sSpdDioOuUxXcC%", str[*i]) != NULL)
		arg.type = str[*i];
	(*i)++;
	return (arg);
}
