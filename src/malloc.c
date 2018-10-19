/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:38:42 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/19 16:25:01 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

t_all_infos g_all_infos = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0,
	0
};
pthread_mutex_t	g_mutex;

t_addr_list		*ft_init_big(size_t size)
{
	t_addr_list	*ret;

	if (!(ret = (t_addr_list *)(mmap(0, size + sizeof(t_addr_list), PROT_READ \
	| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ret->content = (void*)((long)ret + (long)sizeof(t_addr_list));
	ret->content_size = size;
	ret->arena = ret;
	// ret->arena_end = (void *)((long)ret + (long)(size + sizeof(t_addr_list)));
	ret->next = NULL;
	// ret->prev = NULL;
	return (ret);
}

t_addr_list		*ft_init_one_map(size_t node_size)
{
	t_addr_list	*ret;
	t_addr_list	*tmp;
	int			i;

	if (!(ret = (t_addr_list *)(mmap(0, node_size * 128, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))))
		return (NULL);
	ft_memset(ret, 0, node_size * 128);
	i = -1;
	tmp = ret;
	while (++i < 128)
	{
		tmp->content = (void*)((long)tmp + (long)sizeof(t_addr_list));
		tmp->content_size = 0;
		tmp->next = (i == 127) ? NULL : (void *)((long)tmp + (long)node_size);
		// tmp->prev = (i == 0) ? NULL : (void *)((long)tmp - (long)node_size);
		tmp->arena = (void *)ret;
		// tmp->arena_end =  (void*)((long)ret + node_size * 128);
		tmp = (void *)((long)tmp + (long)node_size);
	
	}
	return (ret);
}

void	ft_init_sizes()
{
	size_t		page_size;

	page_size = getpagesize();
	g_all_infos.page_size = page_size;
	g_all_infos.tiny_size = page_size * 3;
	g_all_infos.tiny_node_size = g_all_infos.tiny_size / 128;
	g_all_infos.small_size = page_size * 33;
	g_all_infos.small_node_size = g_all_infos.small_size / 128;
}

void	put_node_after(t_addr_list *node, t_addr_list *ref)
{
	if (ref->next)
	{
		// ref->next->prev = node;
		node->next = ref->next;
	}
	// node->prev = ref;
	ref->next = node;
}

// void	put_node_before(t_addr_list **to, t_addr_list *node, t_addr_list *ref)
// {
// 	if (ref == *to)
// 	{
// 		node->prev = NULL;
// 		*to = node;
// 	}
// 	if (ref->prev)
// 	{
// 		ref->prev->next = node;
// 		node->prev = ref->prev;
// 	}
// 	node->next = ref;
// 	ref->prev = node;
// }

void	ordered_put_node(t_addr_list **to, t_addr_list *node)
{
	t_addr_list	*tmp;

	node->next = ((*to) && (long)((*to)->content) > (long)(node->content)) ? (*to) : NULL;
	// node->prev = NULL;
	if (!(*to) ||  (long)((*to)->content) > (long)(node->content))
	{
		*to = node;
		return;
	}
	tmp = *to;
	while (tmp->next && (long)(tmp->next->content) < (long)(node->content))
		tmp = tmp->next;
	// if ((long)(tmp->content) < (long)(node->content))
	put_node_after(node, tmp);
	// else
		// put_node_before(to, node, tmp);
}

void	output_m_log(void *ptr, size_t size)
{
	int 	fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("malloc return ptr ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd(" for ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits\n\n", fd);
	close(fd);
}

void	entry_m_log(size_t size)
{
	int 	fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("malloc asked for size : ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits\n", fd);
	close(fd);
}

void	*ft_allocate(t_addr_list **from, t_addr_list **to, size_t size)
{
	t_addr_list	*node;

	node = *from;
	node->content_size = size;
	*from = node->next;
	ordered_put_node(to, node);
	if (DEBUG)
		output_m_log(node->content, node->content_size);
	pthread_mutex_unlock(&(g_mutex));
	return (node->content);
}


void	ft_putstr_log(char *str)
{
	int 	fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd(str, fd);
	close(fd);
}

void 	*malloc(size_t size)
{
	t_addr_list	*big;

	pthread_mutex_lock(&(g_mutex));
	if (g_all_infos.tiny_size == 0 || g_all_infos.tiny_node_size == 0 \
		|| g_all_infos.small_size == 0 || g_all_infos.small_node_size == 0)
		ft_init_sizes();
	if (DEBUG)
		entry_m_log(size);
	if (size <= g_all_infos.tiny_node_size - sizeof(t_addr_list))
	{
		if (!(g_all_infos.e_tiny_mapping))
			g_all_infos.e_tiny_mapping = ft_init_one_map(g_all_infos.tiny_node_size);
		return (ft_allocate(&(g_all_infos.e_tiny_mapping), &(g_all_infos.tiny_mapping), size));
	}
	else if (size <= g_all_infos.small_node_size - sizeof(t_addr_list))
	{
		if (!(g_all_infos.e_small_mapping))
			g_all_infos.e_small_mapping = ft_init_one_map(g_all_infos.small_node_size);
		return (ft_allocate(&(g_all_infos.e_small_mapping), &(g_all_infos.small_mapping), size));
	}
	else
	{
		if (!(big = ft_init_big(size)))
		{
			if (DEBUG)
				ft_putstr_log("\nCould not init big\n\n");
			pthread_mutex_unlock(&(g_mutex));		
			return (NULL);
		}
		ordered_put_node(&(g_all_infos.other_mapping), big);
		if (DEBUG)
			output_m_log(big->content, big->content_size);
		pthread_mutex_unlock(&(g_mutex));		
		return (big->content);
	}
}