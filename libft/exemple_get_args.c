/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple_get_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:28:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/11 18:09:58 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_opt	tab[4] = {
	{"c", ""},
	{"d", "i"},
	{"f", "fis"},
	{"", ""}
};

int		main(int ac, char **av)
{
	t_list	*lst;
	t_list	*tmp;

	if (ac > 1)
	{
		lst = ft_get_args(ac, av, tab, 's');
		tmp = lst;
		while(tmp)
		{
			printf("{\n type=%d\n opt=%s\n fd=%d\n err=%d\n str=%s\n val=%d\n}\n\n", ((t_parg *)(tmp->content))->type, ((t_parg *)(tmp->content))->opt, ((t_parg *)(tmp->content))->fd,((t_parg *)(tmp->content))->err, ((t_parg *)(tmp->content))->str, ((t_parg *)(tmp->content))->val);
			tmp = tmp->next;
		}
	}
	return (0);
}
