/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:03:38 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/06 15:07:20 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*str_convert(char *s, int n, int l)
{
	while (n > 0)
	{
		s[l--] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		k;

	s = ft_calloc(num_len(n) + 1, sizeof(char));
	if (!s)
		return (s);
	if (n == 0)
	{
		ft_strlcpy(s, "0", 2);
		return (s);
	}
	if (n == -2147483648)
	{
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	k = 0;
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
		k = 1;
	}
	str_convert(s + k, n, num_len(n) - 1);
	return (s);
}
