/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/05 19:00:23 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int		ft_small_free(void *ptr, t_arena_container *tmp)
{
	size_t size;

	size = (tmp == g_all_infos.small_mapping) ? g_all_infos.small_size  : g_all_infos.tiny_size;
	while (tmp)
	{
		if (tmp->first->content <= ptr && tmp->first->content + size > ptr)
		{
			ft_putnbr(size);
			ft_putstr(" o ptr found ");
			ft_putptr(ptr);
			ft_putstr("\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		ft_other_free(void *ptr)
{
	t_addr_list *tmp;

	tmp = g_all_infos.other_mapping;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			// printf("ptr found on big  %zu!\n", tmp->content_size);
			ft_putnbr(tmp->content_size);
			ft_putstr(" o big ptr found ");
			ft_putptr(tmp->content);
			ft_putstr("\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		free(void *ptr)
{
// dans malloc si le container est full, verifier que les autres ont pas eu de free depuis avant de refaire un container
	if (ft_small_free(ptr, g_all_infos.tiny_mapping) || ft_small_free(ptr, g_all_infos.small_mapping))
		return;
	ft_other_free(ptr);
}
