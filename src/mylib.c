/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:59:35 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/19 15:42:12 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len > 0)
	{
		temp[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void    ft_putptr_fd(void *ptr, int fd)
{
    long   val;

    val = (size_t)ptr;
    if (val > 15)
    {
        ft_putptr_fd((void  *)(val / 16), fd);
        ft_putptr_fd((void *)(val % 16), fd);
    }
    else
        write(fd, &(HEXCHARS[val]), 1);
}

void	ft_putnbr_fd(size_t n, int fd)
{
    char c;

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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp1;
	char	*temp2;

	temp1 = (char *)src;
	temp2 = (char *)dst;
	while (n > 0)
	{
		temp2[n - 1] = temp1[n - 1];
		n--;
	}
	return (dst);
}
