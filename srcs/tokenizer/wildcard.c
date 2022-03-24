/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:56:32 by ahimmi            #+#    #+#             */
/*   Updated: 2022/03/24 03:30:35 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match(char *wildcard, char *s)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	if (!*wildcard && *s)
		return (false);
	while (wildcard[i] && s[i] && wildcard[i] != '*')
	{
		if (s[i] != wildcard[i])
			return (false);
		i++;
	}
	i = ft_strlen(wildcard) + 1;
	j = ft_strlen(s) + 1;
	while (--i > 0 && --j > 0 && wildcard[i] != '*')
		if (s[j] != wildcard[i])
			return (false);
	words = ft_split(wildcard, '*');
	i = 0;
	while (words[i])
	{
		s = ft_strnstr(s, words[i], -1);
		if (!s)
			return (false);
		s += ft_strlen(words[i++]);
	}
	return (true);
}

char	*expand_wildcard(char *wildcard, t_gc **garbage)
{
	struct dirent	*dir_ent;
	DIR				*dir;
	char			*ret;

	if (!ft_strchr(wildcard, '*'))
		return (wildcard);
	ret = "";
	dir = opendir(".");
	while (true)
	{
		dir_ent = readdir(dir);
		if (!dir_ent)
			break ;
		if (dir_ent->d_name[0] != '.' && match(wildcard, dir_ent->d_name))
		{
			if (*ret)
				ret = collect(append_char(ret, ' '), garbage);
			ret = collect(ft_strjoin(ret, dir_ent->d_name), garbage);
		}
	}
	closedir(dir);
	if (!*ret)
		return (wildcard);
	return (ret);
}
