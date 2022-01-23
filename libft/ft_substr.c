/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:49 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/11 01:15:46 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static char	*get_memory(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i < len)
		i++;
	return (malloc(i + 1));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (0);
	if (start < ft_strlen(s))
	{
		sub = get_memory(s, start, len);
		if (!sub)
			return (sub);
		i = 0;
		while (s[start] && i < len)
			sub[i++] = s[start++];
		sub[i] = '\0';
		return (sub);
	}
	sub = malloc(1);
	if (!sub)
		return (sub);
	sub[0] = 0;
	return (sub);
}
