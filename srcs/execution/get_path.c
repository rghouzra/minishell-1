/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:48:58 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/27 15:43:36 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *word, t_var *env, t_gc **garbage)
{
	char	**str;
	char	*path;
	int		i;

	i = 0;
	if (!word || !env)
		return (NULL);
	if (access(word, F_OK) == 0)
		return (word);
	path = ft_getenv("PATH", env);
	str = ft_split(path, ':');
	if (!str)
		return (NULL);
	while (str[i])
	{
		collect(str[i], garbage);
		str[i] = collect(append_char(str[i], '/'), garbage);
		str[i] = collect(ft_strjoin(str[i], word), garbage);
		if (access(str[i], F_OK) == 0)
			return (free(str), str[i]);
		i++;
	}
	return (free(str), NULL);
}

