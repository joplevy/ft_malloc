/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/08/26 17:02:13 by jplevy           ###   ########.fr       */
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

typedef struct	s_mapping
{
	void		*arena;
	size_t		size;
	size_t		node_size;
}				t_mapping;

typedef struct	s_all_infos
{
	t_mapping	tiny_mapping;
	t_mapping	small_mapping;
	char		loaded;
}				t_all_infos;

extern t_all_infos g_all_infos;

t_all_infos g_all_infos = {
	{NULL, 0, 0},
	{NULL, 0, 0},
	0
};

#endif