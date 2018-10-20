/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 17:26:53 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>

# define HEXCHARS "0123456789ABCDEF"

# define DEBUG 0
# define GVAR 0
# define MEMSTATUS 0

typedef struct			s_addr_list
{
	void				*content;
	size_t				content_size;
	struct s_addr_list	*next;
	void				*arena;
}						t_addr_list;

typedef struct			s_all_infos
{
	t_addr_list			*tiny_mapping;
	t_addr_list			*e_tiny_mapping;
	t_addr_list			*small_mapping;
	t_addr_list			*e_small_mapping;
	t_addr_list			*other_mapping;
	size_t				tiny_node_size;
	size_t				tiny_size;
	size_t				small_size;
	size_t				small_node_size;
	size_t				page_size;
}						t_all_infos;

extern pthread_mutex_t	g_mutex;
extern t_all_infos		g_all_infos;

/*
** malloc
*/

void					*malloc(size_t size);
void					ordered_put_node(t_addr_list **to, t_addr_list *node);
void					*calloc(size_t count, size_t size);\

/*
** free
*/

void					free(void *ptr);

/*
**  realloc
*/
void					*realloc(void *ptr, size_t size);

/*
** show_alloc_mem
*/

void					show_alloc_mem();
void					show_freed_mem();
void					show_mapping(int fd);

/*
** mylib_print
*/

void					ft_putstr_log(char *str);
void					ft_putptr_fd(void *ptr, int fd);
void					ft_putnbr_fd(size_t n, int fd);
void					ft_putstr_fd(char const *s, int fd);

/*
** mylib
*/

void					*ft_memset(void *b, int c, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
size_t					ft_strlen(const char *s);

/*
** output_logs
*/

void					output_f_log(void *ptr, char *str);
void					output_m_log(void *ptr, size_t size);
void					output_r_log(char *str, void *ptr, size_t size);
void					ft_print_head(char *str, void *ptr, int fd);
void					ft_print_line(void *ptr1, void *ptr2, \
							size_t size, int fd);

/*
** input_logs
*/
void					globals_var_log();
void					entry_m_log(size_t size);
void					entry_f_log(void *ptr);
void					entry_r_log(void *ptr, size_t size);
void					sizes_r_log(size_t s1, size_t s2);

/*
** list
*/

t_addr_list				*ft_find_node(void *ptr, t_addr_list *map);
t_addr_list				*get_last_node(t_addr_list *tmp, t_addr_list *arena);
void					ft_clear_list(t_addr_list **empty, t_addr_list *node);
void					put_node_after(t_addr_list *node, t_addr_list *ref);
void					ordered_put_node(t_addr_list **to, t_addr_list *node);

/*
** init
*/

t_addr_list				*ft_init_big(size_t size);
t_addr_list				*ft_init_one_map(size_t node_size);
void					ft_init_sizes();

#endif
