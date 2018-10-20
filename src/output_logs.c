/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_logs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:53:16 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 16:23:51 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void	output_f_log(void *ptr, char *str)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (MEMSTATUS)
		show_mapping(fd);
	ft_putstr_fd("ptr : ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" succesfully freed\n\n", fd);
	close(fd);
}

void	output_m_log(void *ptr, size_t size)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd("malloc return ptr ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd(" for ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits\n\n", fd);
	close(fd);
}

void	output_r_log(char *str, void *ptr, size_t size)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("realloc to ptr ", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd(" for ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" bits\n\n", fd);
	close(fd);
}

void	ft_print_head(char *str, void *ptr, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("0x", fd);
	ft_putptr_fd(ptr, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_print_line(void *ptr1, void *ptr2, size_t size, int fd)
{
	ft_putstr_fd("0x", fd);
	ft_putptr_fd(ptr1, fd);
	ft_putstr_fd(" - 0x", fd);
	ft_putptr_fd(ptr2, fd);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_fd(size, fd);
	ft_putstr_fd(" octets\n", fd);
}
