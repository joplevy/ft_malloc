/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:21:10 by jplevy            #+#    #+#             */
/*   Updated: 2016/09/08 07:01:57 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "../libft.h"
# include <stdio.h>

typedef struct			s_list1
{
	char				*data;
	int					c;
	struct s_list1		*next;
}						t_list1;

typedef union			u_types
{
	size_t				st;
	ssize_t				sst;
	intmax_t			im;
	uintmax_t			uim;
	char				c;
	unsigned char		uc;
	short int			s;
	unsigned short		us;
	int					i;
	unsigned int		ui;
	long int			l;
	unsigned long		ul;
	long long int		ll;
	unsigned long long	ull;
	void				*p;
}						t_types;

typedef struct			s_arg
{
	char				*flags;
	int					min;
	int					precision;
	char				*modifier;
	char				type;
}						t_arg;

t_list1					*ft_create_elem(void *data, int c);
unsigned long long		ft_get_mask(char *modifier);
t_types					ft_va_arg(t_arg argtype, va_list ap);
char					*ft_get_base(char type);
char					*ft_right_itoa(t_types val, char *modifier);
char					*ft_get_str(t_arg argtype, t_types val);
void					ft_list_push_back(t_list1 **begin_list, void *data, \
						int c);
int						ft_putlist(t_list1 *str);
int						ft_get_arg(t_arg *argtype, va_list ap, t_list1 **str);
int						ft_printf(const char *format, ...);
t_arg					ft_arginit(void);
t_arg					ft_get_argtype(const char *str, int *i);
char					*ft_itoa_base(long long int nb, char *base);
void					ft_check_argtype(t_arg *argtype);
char					*ft_unsigned_itoa_base(long long unsigned int nb,\
	char *base, unsigned long long mask);
char					*ft_get_wchar(unsigned int c);
char					*ft_get_wstr(wchar_t *s);
unsigned char			ft_get_oct(int c, int i, int j);
char					*ft_mal_char(char c);
char					*ft_att(char *str, t_arg at);
char					*ft_min(char *str, t_arg at, int c);
char					*ft_precision(char *str, t_arg at);
char					*ft_get_adress(void *p, t_arg at);
t_list1					*ft_get_list(const char *format, va_list ap);
t_types					ft_va_arg_2(t_arg argtype, va_list ap);
int						ft_lenght(int base, long long int nb);
int						ft_unsigned_lenght(int base, long long unsigned nb);
int						ft_before(t_arg at, char *str);
char					*ft_strjoin_no_leaks(char *s1, char *s2, char *tofree);
int						ft_min_sub(char **str);
void					free_flags(t_arg args);
char					*ft_strsub_no_leaks(char const *s, unsigned int start, \
	size_t len, char *tofree);
#endif
