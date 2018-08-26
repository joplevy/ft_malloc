/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:47:13 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/06/30 01:29:15 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <errno.h>

static int		ft_match(char *str, t_opt *tab)
{
	int		i;

	i = -1;
	while (ft_strlen(tab[++i].name) > 0)
		if (ft_strcmp(str, tab[i].name) == 0)
			return (i);
	return (-1);
}

static t_parg	ft_newarg(char type, char *str)
{
	t_parg	ret;

	if (type == 'o')
		ret.type = opt;
	else if (type == 'i')
		ret.type = number;
	else if (type == 's')
		ret.type = string;
	else if (type == 'f')
		ret.type = file;
	ret.opt = (type == 'o') ? str + 1 : NULL;
	ret.fd = (type == 'f') ? open((const char*)str, O_RDONLY) : 0;
	ret.err = (type == 'f') ? errno : 0;
	ret.str = str;
	ret.val = (type == 'i') ? ft_atoi(str) : 0;
	return (ret);
}

static int		ft_get_opt_args(char **av, int *i, t_list **lst, t_opt o)
{
	int		j;
	t_parg	arg;

	j = -1;
	while ((o.args)[++j])
	{
		if ((o.args)[j] == 'i')
		{
			arg = ft_newarg('i', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_parg)));
		}
		else if ((o.args)[j] == 's')
		{
			arg = ft_newarg('s', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_parg)));
		}
		else if ((o.args)[j] == 'f')
		{
			arg = ft_newarg('f', av[++(*i)]);
			ft_lstadd_back(lst, ft_lstnew(&arg, sizeof(t_parg)));
		}
		else
			return (0);
	}
	return (1);
}

t_list			*ft_get_args(int ac, char **av, t_opt *tab, char elsetype)
{
	t_list	*ret;
	int		i;
	int		opt;
	t_parg	arg;

	i = 0;
	ret = NULL;
	while (++i < ac && (elsetype == 'i' || elsetype == 'f' || elsetype == 's'))
	{
		if (av[i][0] == '-' && (opt = ft_match(av[i] + 1, tab)) >= 0)
		{
			arg = ft_newarg('o', av[i]);
			ft_lstadd_back(&ret, ft_lstnew(&arg, sizeof(t_parg)));
			if ((int)(i + ft_strlen(tab[opt].args)) >= ac || \
				!(ft_get_opt_args(av, &i, &ret, tab[opt])))
				return (ft_lstfree(&ret, NULL));
		}
		else
		{
			arg = ft_newarg(elsetype, av[i]);
			ft_lstadd_back(&ret, ft_lstnew(&(arg), sizeof(t_parg)));
		}
	}
	return (ret);
}
