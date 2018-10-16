/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:41:21 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/16 21:23:43 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

static void			ft_print_head(char *str, void *ptr)
{
	ft_putstr(str);
	ft_putstr("0x");
	ft_putptr(ptr);
	ft_putstr("\n");
}

static void			ft_print_line(void *ptr1, void *ptr2, size_t size)
{
	ft_putstr("0x");
	ft_putptr(ptr1);
	ft_putstr(" - 0x");
	ft_putptr(ptr2);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

// size_t		print_mem(t_arena_container *zones, char *type)
// {
// 	t_arena_container	*tmp;
// 	t_addr_list				*tmp_l;
// 	t_addr_list				*st_tmp_l;
// 	size_t 				tot_size;

// 	tmp = zones;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tot_size = 0;
// 	while (tmp)
// 	{
// 		ft_print_head(type, (((t_addr_list *)tmp->first)->content));
// 		tmp_l = tmp->zones;
// 		st_tmp_l = tmp_l;
// 		while(tmp_l)
// 		{
// 			tot_size += tmp_l->content_size;
// 			if (tmp_l->content_size > 0)
// 				ft_print_line(tmp_l->content, tmp_l->content + tmp_l->content_size, tmp_l->content_size);
// 			tmp_l = (tmp_l->next == st_tmp_l) ? NULL : tmp_l->next;
// 		}
// 		tmp = tmp->prev;
// 	}
// 	return (tot_size);
// }


static size_t		print_mem(t_addr_list *zones, size_t arena_size, char *type)
{
	t_addr_list		*last_addr;
	t_addr_list		*tmp;
	t_addr_list		*tmp_addr;
	size_t 			tot_size;

	tot_size = 0;
	tmp = zones;
	last_addr = NULL;
	while (tmp)
	{
		tmp_addr = (void *)((long)tmp - ((long)tmp % (long)arena_size));
		if (last_addr != tmp_addr)
		{
			last_addr = tmp_addr;
			ft_print_head(type, tmp_addr);
		}
		ft_print_line(tmp->content, tmp->content + tmp->content_size, tmp->content_size);
		tot_size +=tmp->content_size;
		tmp = tmp->next;
	}
	return (tot_size);
}

static size_t		print_big_mem(t_addr_list *zones, char *type)
{
	t_addr_list			*tmp;
	size_t 				tot_size;

	tmp = zones;
	while (tmp->next)
		tmp = tmp->next;
	tot_size = 0;
	while (tmp)
	{
		ft_print_head(type, tmp);
		ft_print_line(tmp->content, tmp->content + tmp->content_size, tmp->content_size);
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
		tot_size += print_mem(g_all_infos.tiny_mapping, g_all_infos.tiny_size, "TINY : ");
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, g_all_infos.small_size, "SMALL : ");
	if (g_all_infos.other_mapping)
		tot_size += print_big_mem(g_all_infos.other_mapping, "LARGE : ");
	ft_putstr("Total : ");
	ft_putnbr(tot_size);
	ft_putstr(" octets\n");
}
