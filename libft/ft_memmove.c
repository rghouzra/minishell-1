/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:59:27 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/05 12:07:46 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
	{
		len--;
		while ((int) len >= 0)
		{
			*((char *)(dst + len)) = *((char const *)(src + len));
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
