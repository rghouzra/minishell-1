/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:51:36 by aklaikel          #+#    #+#             */
/*   Updated: 2021/12/01 22:27:28 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putnbr_u_fd(unsigned int n, int *len, int fd)
{
	unsigned int	i;

	i = n;
	if (i <= 9)
	{
		ft_putchar_fd(i + 48, fd);
		(*len)++;
	}
	else
	{
		ft_putnbr_fd(i / 10, len, fd);
		ft_putnbr_fd(i % 10, len, fd);
	}
}
