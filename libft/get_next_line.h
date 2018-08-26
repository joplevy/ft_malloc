/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 10:59:44 by jplevy            #+#    #+#             */
/*   Updated: 2016/03/06 10:40:04 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 64

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_indexof(char *str);
int		get_chars(char *buff, char **str);
int		ft_result(char **line, char **str, int n);
int		get_next_line(int const fd, char **line);
#endif
