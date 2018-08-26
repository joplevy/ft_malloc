/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 08:42:40 by pgourran          #+#    #+#             */
/*   Updated: 2017/02/15 23:28:06 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **lst, void const *cont, size_t cont_size)
{
	t_list		*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_lstnew(cont, cont_size);
	}
	else
		*lst = ft_lstnew(cont, cont_size);
}
