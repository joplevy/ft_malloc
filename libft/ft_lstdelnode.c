/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 20:05:55 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/30 20:07:15 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			ft_lstdelnode(t_list **lst, t_list *node, void (*f)(void *))
{
	t_list	*tmp;

	if (lst && *lst && node)
	{
		tmp = *lst;
		if (*lst == node)
			*lst = node->next;
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		if (tmp)
			tmp->next = node->next;
		if (f)
			f(node->content);
		if (node->content)
			free(node->content);
		free(node);
	}
}
