/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:39:48 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/10 22:54:55 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static int	is_exist(char c, char const *s)
{
	while (*s)
		if (*s++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start;
	int		end;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (is_exist(s1[start], set) && s1[start])
		start++;
	while (is_exist(s1[end], set) && end >= start)
		end--;
	s2 = (char *) malloc(end - start + 2);
	if (!s2)
		return (s2);
	ft_strlcpy(s2, (char *)s1 + start, end - start + 2);
	return (s2);
}
