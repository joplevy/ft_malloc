/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:59:35 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/17 17:59:55 by jplevy           ###   ########.fr       */
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

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}

void    ft_putptr(void *ptr)
{
    long   val;

    val = (size_t)ptr;
    if (val > 15)
    {
        ft_putptr((void  *)(val / 16));
        ft_putptr((void *)(val % 16));
    }
    else
        write(1, &(HEXCHARS[val]), 1);
}

void	ft_putnbr(size_t n)
{
    char c;

    if (n > 9)
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
    else
    {
        c = '0' + n;
        write(1, &c, 1);
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
