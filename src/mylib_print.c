/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:59:35 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/20 15:55:05 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putptr_fd(void *ptr, int fd)
{
	long	val;

	val = (size_t)ptr;
	if (val > 15)
	{
		ft_putptr_fd((void *)(val / 16), fd);
		ft_putptr_fd((void *)(val % 16), fd);
	}
	else
		write(fd, &(HEXCHARS[val]), 1);
}

void	ft_putnbr_fd(size_t n, int fd)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = '0' + n;
		write(fd, &c, 1);
	}
}

void	ft_putstr_log(char *str)
{
	int		fd;

	fd = open("malloc.logs", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_putstr_fd(str, fd);
	close(fd);
}
