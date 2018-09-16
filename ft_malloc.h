	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   ft_malloc.h                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
	/*   Updated: 2018/09/12 15:59:40 by jplevy           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include "libft/libft.h"
# include <sys/mman.h>
# include <unistd.h>
// # include <pthread.h>
// # include <fcntl.h>
// # define mmap(p1,p2,p3,p4,p5,p6) NULL

typedef struct					s_addr_list
{
	void						*content;
	size_t						content_size;
	struct s_addr_list			*next;
	struct s_addr_list			*prev;
}								t_addr_list;

typedef struct					s_arena_container
{
	t_addr_list					*zones;
	t_addr_list					*first;
	size_t						nb_alloc;
	size_t						arena_id;
	struct s_arena_container	*next;
	struct s_arena_container	*prev;
}								t_arena_container;

typedef struct					s_all_infos
{
	t_arena_container			*tiny_mapping;
	t_arena_container			*small_mapping;
	t_addr_list					*other_mapping;
	size_t						tiny_node_size;
	size_t						tiny_size;
	size_t						small_size;
	size_t						small_node_size;
	size_t						page_size;
}								t_all_infos;


extern t_all_infos g_all_infos;

t_all_infos g_all_infos = {
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0,
	0
};

#endif