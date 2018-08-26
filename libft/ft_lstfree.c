/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:44:08 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/06/30 20:00:40 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lstfree(t_list **lst, void (*ft_free_node)(void **))
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = *lst;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		if (ft_free_node)
			ft_free_node(&(tmp1->content));
		if (tmp1->content)
			free(tmp1->content);
		free(tmp1);
	}
	return (NULL);
}
