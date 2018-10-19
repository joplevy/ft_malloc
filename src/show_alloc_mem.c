/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:41:21 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/19 15:48:47 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

static void			ft_print_head(char *str, void *ptr)
{
	ft_putstr_fd(str, 1);
	ft_putstr_fd("0x", 1);
	ft_putptr_fd(ptr, 1);
	ft_putstr_fd("\n", 1);
}

static void			ft_print_line(void *ptr1, void *ptr2, size_t size)
{
	ft_putstr_fd("0x", 1);
	ft_putptr_fd(ptr1, 1);
	ft_putstr_fd(" - 0x", 1);
	ft_putptr_fd(ptr2, 1);
	ft_putstr_fd(" : ", 1);
	ft_putnbr_fd(size, 1);
	ft_putstr_fd(" octets\n", 1);
}

static size_t		print_mem(t_addr_list *zones, char *type)
{
	void			*last_addr;
	t_addr_list		*tmp;
	size_t 			tot_size;

	tot_size = 0;
	tmp = zones;
	last_addr = NULL;
	while (tmp)
	{
		if (last_addr != tmp->arena)
		{
			last_addr = tmp->arena;
			ft_print_head(type, tmp->arena);
		}
		ft_print_line(tmp->content, tmp->content + tmp->content_size, tmp->content_size);
		tot_size +=tmp->content_size;
		tmp = tmp->next;
	}
	return (tot_size);
}

void		show_alloc_mem()
{
	// faire le tri des zones
	size_t 				tot_size;

	tot_size = 0;	
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping,  "TINY : ");
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL : ");
	if (g_all_infos.other_mapping)
		tot_size += print_mem(g_all_infos.other_mapping, "LARGE : ");
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(tot_size, 1);
	ft_putstr_fd(" octets\n", 1);
}

void		show_freed_mem()
{
	// faire le tri des zones
	size_t 				tot_size;

	tot_size = 0;	
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.e_tiny_mapping,  "TINY : ");
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.e_small_mapping, "SMALL : ");
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(tot_size, 1);
	ft_putstr_fd(" octets\n", 1);
}

void		show_mapping()
{
	// faire le tri des zones
	size_t 				tot_size;

	tot_size = 0;	
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping,  "TINY : ");
	else
		ft_putstr_fd("NO TINY MAPPING\n", 1);
	if (g_all_infos.e_tiny_mapping)
		tot_size += print_mem(g_all_infos.e_tiny_mapping,  "EMPTY TINY : ");
	else
		ft_putstr_fd("NO EMPTY TINY MAPPING\n", 1);
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL : ");
	else
		ft_putstr_fd("NO SMALL MAPPING\n", 1);
	if (g_all_infos.e_small_mapping)
		tot_size += print_mem(g_all_infos.e_small_mapping, "EMPTY SMALL : ");
	else
		ft_putstr_fd("NO EMPTY SMALL MAPPING\n", 1);
	if (g_all_infos.other_mapping)
		tot_size += print_mem(g_all_infos.other_mapping, "LARGE : ");
	else
		ft_putstr_fd("NO LARGE MAPPING\n", 1);
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(tot_size, 1);
	ft_putstr_fd(" octets\n", 1);
}
