/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/02 18:45:43 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int		ft_tiny_free(void *ptr)
{
	t_arena_container *tmp;

	tmp = g_all_infos.tiny_mapping;
	while (tmp)
	{
		if (tmp->first->content <= ptr && tmp->first->content + g_all_infos.tiny_size > ptr)
		{
			ft_printf("ptr found on tiny !\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		ft_free(void *ptr)
{
// dans malloc si le container est full, verifier que les autres ont pas eu de free depuis avant de refaire un container
	if (ft_tiny_free(ptr))
		return;
}
