/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uhexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:39:16 by aklaikel          #+#    #+#             */
/*   Updated: 2021/12/01 22:22:15 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_uhexa(unsigned long num, int *len)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (num <= 15)
	{
		ft_putchar_fd(base[num], 1);
		(*len)++;
	}
	else
	{
		ft_print_uhexa(num / 16, len);
		ft_print_uhexa(num % 16, len);
	}
}
