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

// # include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# define HEXCHARS "0123456789ABCDEF"
# include <fcntl.h>
# define DEBUG 1
// #include <stdlib.h>
// # include <pthread.h>
// # include <fcntl.h>
// # define mmap(p1,p2,p3,p4,p5,p6) NULL

typedef struct					s_addr_list
{
	void						*content;
	size_t						content_size;
	struct s_addr_list			*next;
	// struct s_addr_list			*prev;
	void						*arena;
	// void						*arena_end;
}								t_addr_list;

// typedef struct					s_arena_container
// {
// 	t_addr_list					*zones;
// 	t_addr_list					*first;
// 	size_t						nb_alloc;
// 	size_t						arena_id;
// 	struct s_arena_container	*next;
// 	struct s_arena_container	*prev;
// }								t_arena_container;

typedef struct					s_all_infos
{
	t_addr_list					*tiny_mapping;
	t_addr_list					*e_tiny_mapping;
	t_addr_list					*small_mapping;
	t_addr_list					*e_small_mapping;
	t_addr_list					*other_mapping;
	size_t						tiny_node_size;
	size_t						tiny_size;
	size_t						small_size;
	size_t						small_node_size;
	size_t						page_size;
}								t_all_infos;


extern pthread_mutex_t g_mutex;
extern t_all_infos g_all_infos;


/*
** show_alloc_mem
*/

// size_t		print_mem(t_arena_container *zones, char *type);
void		show_alloc_mem();
void		show_freed_mem();
void		show_mapping();

/*
** malloc
*/

void 		*malloc(size_t size);
void		ordered_put_node(t_addr_list **to, t_addr_list *node);

void		ft_putstr_log(char *str);

/*
** free
*/

void		free(void *ptr);

/*
** mylib
*/

void    ft_putptr_fd(void *ptr, int fd);
void	ft_putnbr_fd(size_t n, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
**  realloc
*/
void	*realloc(void *ptr, size_t size);
#endif