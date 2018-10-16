/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:40:34 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/16 17:02:05 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int		ft_to_start(t_arena_container *arena, t_addr_list	*node, size_t size)
{
	int		ret;

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
		ret = munmap(arena->first->content, size);
		arena->next->prev = arena->prev;
		return (ret);
	}
	return(1);
}

int		ft_small_free(void *ptr, t_arena_container *cont)
{
	size_t 				size;
	t_arena_container	*tmp;
	t_addr_list			*tmp1;

	tmp = cont;
	size = (tmp == g_all_infos.small_mapping) ? g_all_infos.small_size  : g_all_infos.tiny_size;
	while (tmp)
	{
		// print_mem(tmp, "TINY");
		if (tmp->first->content <= ptr && tmp->first->content + size > ptr)
		{
			tmp1 = tmp->zones;
			while (tmp1)
			{
				if (tmp1->content == ptr)
				{
					int ret = ft_to_start(tmp, tmp1, size);
					if (ret == 0)
					{
						if (tmp == g_all_infos.tiny_mapping)
							g_all_infos.tiny_mapping = tmp->next;
						else if (tmp == g_all_infos.small_mapping)
							g_all_infos.small_mapping = tmp->next;
						else
						{
							ft_putstr("toto \n");
							tmp->prev->next = tmp->next;
							// tmp->next->prev = tmp->next;
						}
						ft_memset(tmp, 0, sizeof(t_arena_container));
					}
					ft_putnbr(ret);
					ft_putstr("tmp : ");
					ft_putptr(tmp);
					ft_putstr("\n");
					ft_putstr("global : ");
					ft_putptr(g_all_infos.tiny_mapping);
					ft_putstr("\n");
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

void		ft_free(void *ptr)
{
	ft_putptr(ptr);
		ft_putstr(" <====\n");
// dans malloc si le container est full, verifier que les autres ont pas eu de free depuis avant de refaire un container
	if (ft_small_free(ptr, g_all_infos.tiny_mapping) >= 0 || ft_small_free(ptr, g_all_infos.small_mapping) >= 0)
		return;
	ft_other_free(ptr);
}
