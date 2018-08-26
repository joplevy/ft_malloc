/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:47:20 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/02 18:21:14 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*el;

	if ((el = (t_list*)malloc(sizeof(t_list))))
	{
		if (!(content) || content_size == 0)
		{
			el->content = NULL;
			el->content_size = 0;
		}
		else
		{
			if (!(el->content = ft_memalloc(content_size)))
				return (NULL);
			ft_memcpy((el->content), content, content_size);
			el->content_size = content_size;
			el->next = NULL;
		}
	}
	return (el);
}
