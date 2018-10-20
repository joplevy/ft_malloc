/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:41:21 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 16:30:01 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

static size_t	print_mem(t_addr_list *zones, char *type, int fd)
{
	void			*last_addr;
	t_addr_list		*tmp;
	size_t			tot_size;

	tot_size = 0;
	tmp = zones;
	last_addr = NULL;
	while (tmp)
	{
		if (last_addr != tmp->arena)
		{
			last_addr = tmp->arena;
			ft_print_head(type, tmp->arena, fd);
		}
		ft_print_line(tmp->content, tmp->content + tmp->content_size, \
			tmp->content_size, fd);
		tot_size += tmp->content_size;
		tmp = tmp->next;
	}
	return (tot_size);
}

void			show_alloc_mem(void)
{
	size_t	tot_size;

	pthread_mutex_lock(&(g_mutex));
	tot_size = 0;
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping, "TINY : ", 1);
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL : ", 1);
	if (g_all_infos.other_mapping)
		tot_size += print_mem(g_all_infos.other_mapping, "LARGE : ", 1);
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(tot_size, 1);
	ft_putstr_fd(" octets\n", 1);
	pthread_mutex_unlock(&(g_mutex));
}

void			show_freed_mem(void)
{
	size_t	tot_size;

	pthread_mutex_lock(&(g_mutex));
	tot_size = 0;
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.e_tiny_mapping, "TINY : ", 1);
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.e_small_mapping, "SMALL : ", 1);
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(tot_size, 1);
	ft_putstr_fd(" octets\n", 1);
	pthread_mutex_unlock(&(g_mutex));
}

void			show_mapping(int fd)
{
	size_t	tot_size;

	pthread_mutex_lock(&(g_mutex));
	tot_size = 0;
	if (g_all_infos.tiny_mapping)
		tot_size += print_mem(g_all_infos.tiny_mapping, "TINY : ", fd);
	if (g_all_infos.e_tiny_mapping)
		tot_size += print_mem(g_all_infos.e_tiny_mapping, "EMPTY TINY : ", fd);
	if (g_all_infos.small_mapping)
		tot_size += print_mem(g_all_infos.small_mapping, "SMALL : ", fd);
	if (g_all_infos.e_small_mapping)
		tot_size += print_mem(g_all_infos.e_small_mapping, "EMPTY SMALL : ", \
			fd);
	if (g_all_infos.other_mapping)
		tot_size += print_mem(g_all_infos.other_mapping, "LARGE : ", fd);
	ft_putstr_fd("Total : ", fd);
	ft_putnbr_fd(tot_size, fd);
	ft_putstr_fd(" octets\n", fd);
	pthread_mutex_unlock(&(g_mutex));
}
