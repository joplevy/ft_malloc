/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:22:20 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/18 19:00:22 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_addr_list	*ft_find_node(void *ptr, t_addr_list *map)
{
	t_addr_list			*tmp;

	tmp = map;
	while (tmp)
	{
		if (tmp->content == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
// #include <stdio.h>
void    *hard_realloc(void *ptr, size_t size, size_t n_size)
{
    void    *ret;
    size_t  final_size;

    ret = malloc(size);
    // ft_putstr("1\n");
    final_size = (size > n_size) ? n_size : size;
    // ft_putnbr(final_size);
    // ft_putstr("2\n");
    // printf("\nbefore free %p, %p, %s, %s, %zu wat\n", ret, ptr, ret, ptr, final_size);
    ft_memcpy(ret, ptr, final_size);
    // ft_putstr(ret);
    free(ptr);
    // printf("\nafter free %p, %p, %s, %zu\n", ret, ptr, ret, final_size);
    // ft_putstr("4\n");
    // ft_putstr(ret);
	// pthread_mutex_unlock(&(g_mutex));
    return (ret);
}

void    *realloc(void *ptr, size_t size)
{
    t_addr_list *node;

    node = ft_find_node(ptr, g_all_infos.tiny_mapping);
    if (node)
    {
        if (size > g_all_infos.tiny_node_size - sizeof(t_addr_list))
        {
            // ft_putstr("toto\n");
            return (hard_realloc(ptr, size, node->content_size));
        }
        if (size > node->content_size)
        {
	        pthread_mutex_lock(&(g_mutex));
            node->content_size = size;
	        pthread_mutex_unlock(&(g_mutex));
            return (node->content);
        }
        else
        {
	        pthread_mutex_lock(&(g_mutex));
            ft_memset((void*)((long)(node->content) + (long)size), 0, node->content_size - size);
            node->content_size = size;
	        pthread_mutex_unlock(&(g_mutex));
            return (node->content);
        }
    }
    else if ((node = ft_find_node(ptr, g_all_infos.small_mapping)))
    {
        if (size > g_all_infos.small_node_size - sizeof(t_addr_list))
            return (hard_realloc(ptr, size, node->content_size));
        if (size > node->content_size)
        {
	        pthread_mutex_lock(&(g_mutex));
            node->content_size = size;
	        pthread_mutex_unlock(&(g_mutex));
            return (node->content);
        }
        else
        {
	        pthread_mutex_lock(&(g_mutex));
            node->content_size = size;
            ft_memset(node->content + size, 0, size - node->content_size);
	        pthread_mutex_unlock(&(g_mutex));
            return (node->content);
        }
    }
    return (hard_realloc(ptr, size, 0));
}