/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/10 17:36:18 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int		ft_to_start(t_arena_container *arena, t_addr_list	*node, size_t size)
{
	ft_memset(node->content, 0, node->content_size);
	node->content_size = 0;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->next = arena->zones;
	node->prev = arena->zones->prev;
	arena->zones->prev->next = node;
	arena->zones->next->prev = node;
	arena->zones = node;
	arena->nb_alloc -= 1;
	if (arena->nb_alloc == 0)
	{
		return (munmap(arena->first->content, size));
	}
	return(1);
}

int		ft_small_free(void *ptr, t_arena_container *tmp)
{
	size_t 		size;
	t_addr_list	*tmp1;

	size = (tmp == g_all_infos.small_mapping) ? g_all_infos.small_size  : g_all_infos.tiny_size;
	while (tmp)
	{
		if (tmp->first->content <= ptr && tmp->first->content + size > ptr)
		{
			tmp1 = tmp->zones;
			while (tmp1)
			{
				if (tmp1->content == ptr)
				{
					ft_putnbr(size);
					ft_putstr(" o ptr found ");
					ft_putptr(ptr);
					ft_putstr("\n");
					int ret = ft_to_start(tmp, tmp1, size);
					ft_putstr("\n");
					ft_putnbr(ret);
					ft_putstr("\n");
					return (ret);
				}
				tmp1=tmp1->next;
			}
		}
		tmp = tmp->next;
	}
	return (-1);
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
			return (0);
		}
		tmp = tmp->next;
	}
	return (-1);
}

void		free(void *ptr)
{
// dans malloc si le container est full, verifier que les autres ont pas eu de free depuis avant de refaire un container
	if (ft_small_free(ptr, g_all_infos.tiny_mapping) >= 0 || ft_small_free(ptr, g_all_infos.small_mapping) >= 0)
		return;
	ft_other_free(ptr);
}
