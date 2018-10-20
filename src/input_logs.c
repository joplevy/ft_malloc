/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 16:03:16 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 16:18:27 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void	globals_var_log(void)
{
	int		fd;

	if (GVAR)
	{
		fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR);
		ft_putstr_fd("GLOBALS\nt_n_s : ", fd);
		ft_putnbr_fd(g_all_infos.tiny_node_size, fd);
		ft_putstr_fd("\nt_s : ", fd);
		ft_putnbr_fd(g_all_infos.tiny_size, fd);
		ft_putstr_fd("\ns_s : ", fd);
		ft_putnbr_fd(g_all_infos.small_size, fd);
		ft_putstr_fd("\ns_n_s : ", fd);
		ft_putnbr_fd(g_all_infos.small_node_size, fd);
		ft_putstr_fd("\n\n", fd);
		close(fd);
	}
}

void	entry_m_log(size_t size)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("malloc asked for size : ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits\n", fd);
	close(fd);
}

void	entry_f_log(void *ptr)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("ask to free pointer ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}

void	entry_r_log(void *ptr, size_t size)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("realloc asked for size : ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits at pointer : ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd("\n", fd);
	if (MEMSTATUS)
		show_mapping(fd);
	close(fd);
}

void	sizes_r_log(size_t s1, size_t s2)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("size : ", fd);
	ft_putnbr_fd(s1, fd);
	ft_putstr_fd(" node_size : ", fd);
	ft_putnbr_fd(s2, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}
