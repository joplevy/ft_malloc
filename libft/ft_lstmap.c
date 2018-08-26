/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 20:12:00 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 20:18:43 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *l;

	if (!lst)
		return (NULL);
	if (!lst->next)
		return (f(lst));
	l = ft_lstmap(lst->next, f);
	ft_lstadd(&l, f(lst));
	return (l);
}
