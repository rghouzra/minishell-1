/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 02:15:42 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/28 03:26:48 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

int		err_printf(const char *f, ...);
int		ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int *len, int fd);
void	ft_putnbr_u_fd(unsigned int n, int *len, int fd);
int		ft_printstr(char *s);
void	print_it(char c, va_list ptr, int *len);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_print_hexa(unsigned long num, int *len);
void	ft_print_uhexa(unsigned long num, int *len);

#endif