/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/09/04 17:59:20 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include "libft/libft.h"
# include <sys/mman.h>
# include <unistd.h>
// # include <pthread.h>
// # include "libft/libft.h"
// # include <unistd.h>
// # include <sys/mman.h>
// # include <fcntl.h>
// # define mmap(p1,p2,p3,p4,p5,p6) NULL

typedef struct	s_header
{
	int			nb_tiny;
	int			nb_small;
}				t_header;

typedef struct	s_all_infos
{
	t_list		*tiny_mapping;
	t_list		*small_mapping;
	t_list		*other_mapping;
	size_t		tiny_size;
	size_t		tiny_node_size;
	size_t		small_size;
	size_t		small_node_size;
}				t_all_infos;

extern t_all_infos g_all_infos;

t_all_infos g_all_infos = {
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0
};

#endif