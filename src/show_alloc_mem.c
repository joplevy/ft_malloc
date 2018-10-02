/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:41:21 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/02 18:45:49 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>


static size_t		print_mem(t_arena_container *zones, char *type)
{
	t_arena_container	*tmp;
	t_addr_list				*tmp_l;
	t_addr_list				*st_tmp_l;
	size_t 				tot_size;

	tmp = zones;
	while (tmp->next)
		tmp = tmp->next;
	tot_size = 0;
	while (tmp)
	{
		ft_printf("%s : %p\n", type, (((t_addr_list *)tmp->first)->content));
		tmp_l = tmp->zones;
		st_tmp_l = tmp_l;
		while(tmp_l)
		{
			tot_size += tmp_l->content_size;
			if (tmp_l->content_size > 0)
				ft_printf("%p - %p : %zu octets\n", (tmp_l->content), (tmp_l->content + tmp_l->content_size), tmp_l->content_size);
			tmp_l = (tmp_l->next == st_tmp_l) ? NULL : tmp_l->next;
		}
		tmp = tmp->prev;
	}
	return (tot_size);
}

static size_t		print_big_mem(t_addr_list *zones, char *type)
{
	t_addr_list		*tmp;
	size_t 				tot_size;

	tmp = zones;
	while (tmp->next)
		tmp = tmp->next;
	tot_size = 0;
	while (tmp)
	{
		ft_printf("%s : %p\n%p - %p : %zu octets\n", type, tmp, tmp->content, tmp->content + tmp->content_size, tmp->content_size);
		tot_size += tmp->content_size;
		tmp = tmp->prev;
	}
	return (tot_size);
}

void		show_alloc_mem()
{
	// faire le tri des zones
	size_t 				tot_size;

	tot_size = 0;	
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping, "TINY");
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL");
	if (g_all_infos.other_mapping)
		tot_size += print_big_mem(g_all_infos.other_mapping, "LARGE");
	ft_printf("Total : %zu octets\n", tot_size);
}
