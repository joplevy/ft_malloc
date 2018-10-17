/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:22:20 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/17 18:57:40 by jplevy           ###   ########.fr       */
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

void    *hard_realloc(void *ptr, size_t size, size_t n_size)
{
    void    *ret;
    size_t  final_size;

    ret = ft_malloc(size);
    ft_putstr("1\n");
    final_size = (size > n_size) ? n_size : size;
    ft_putnbr(final_size);
    ft_putstr("2\n");
    ft_memcpy(ret, ptr, final_size);
    ft_putstr(ret);
    // ft_free(ptr);
    ft_putstr("4\n");
    ft_putstr(ret);
    return (ret);
}

void    *ft_realloc(void *ptr, size_t size)
{
    t_addr_list *node;

    node = ft_find_node(ptr, g_all_infos.tiny_mapping);
    if (node)
    {
        if (size > g_all_infos.tiny_node_size - sizeof(t_addr_list))
        {
            ft_putstr("toto\n");
            return (hard_realloc(ptr, size, node->content_size));
        }
        if (size > node->content_size)
        {
            node->content_size = size;
            return (node->content);
        }
        else
        {
            ft_memset((void*)((long)(node->content) + (long)size), 0, node->content_size - size);
            node->content_size = size;
            return (node->content);
        }
    }
    else if ((node = ft_find_node(ptr, g_all_infos.small_mapping)))
    {
        if (size > g_all_infos.small_node_size - sizeof(t_addr_list))
            return (hard_realloc(ptr, size, node->content_size));
        if (size > node->content_size)
        {
            node->content_size = size;
            return (node->content);
        }
        else
        {
            node->content_size = size;
            ft_memset(node->content + size, 0, size - node->content_size);
            return (node->content);
        }
    }
    return (hard_realloc(ptr, size, 0));
}