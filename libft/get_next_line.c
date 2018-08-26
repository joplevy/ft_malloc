/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:41:04 by jplevy            #+#    #+#             */
/*   Updated: 2016/04/29 01:06:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		ft_indexof(char *str)
{
	int		i;

	if (str)
	{
		i = 0;
		while (str[i] && str[i] != '\0')
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-2);
}

int		get_chars(char *buff, char **str)
{
	char	*tmp;

	if (*str)
	{
		if (!(tmp = ft_strdup(*str)))
			return (-1);
		free(*str);
		if (!(*str = ft_strjoin(tmp, buff)))
			return (-1);
		free(tmp);
	}
	else
		*str = ft_strdup(buff);
	return (ft_indexof(*str));
}

int		ft_result(char **line, char **str, int n)
{
	char	*tmp;

	if (n == -2)
		n = ft_strlen(*str);
	if (!(tmp = ft_strdup(*str)))
		return (-1);
	free(*str);
	*line = ft_strsub(tmp, 0, n);
	*str = ft_strsub(tmp, n + 1, ft_strlen(tmp) - n);
	free(tmp);
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	int			i;
	int			j;
	static char	*str = NULL;
	char		*buffer;

	if (fd < 0)
		return (-1);
	if ((j = ft_indexof(str)) != -2)
		return (ft_result(line, &str, j));
	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if (i == 0 && ft_strlen(str) == 0)
	{
		free(buffer);
		return (0);
	}
	if ((j = get_chars(buffer, &str)) == -1 || i == -1)
		return (-1);
	free(buffer);
	if (j == -2 && i != 0)
		return (get_next_line(fd, line));
	else
		return (ft_result(line, &str, j));
}
