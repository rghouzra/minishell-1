/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:56:32 by ahimmi            #+#    #+#             */
/*   Updated: 2022/03/31 04:04:22 by ahimmi           ###   ########.fr       */
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
	while (wildcard[i] && s[i] && wildcard[i] != '*' && !(s[i] != wildcard[i]))
		i++;
	if (s[i] == wildcard[i])
		return (false);
	i = ft_strlen(wildcard) + 1;
	j = ft_strlen(s) + 1;
	while (--i > 0 && --j > 0 && wildcard[i] != '*')
		if (s[j] != wildcard[i])
			return (false);
	words = ft_split(wildcard, '*');
	i = -1;
	while (words[++i])
	{
		s = ft_strnstr(s, words[i], -1) + ft_strlen(words[i]);
		if (!(s - ft_strlen(words[i])))
			return (false);
	}
	return (true);
}

t_token	*last_tok(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*fix(char *s, t_gc **garbage)
{
	char	*ret;

	ret = "";
	while (*s)
	{
		if (*s > 0)
			ret = collect(append_char(ret, *s), garbage);
		s++;
	}
	return (ret);
}

t_token	*expand_wildcard(char *wildcard, t_gc **garbage)
{
	t_token			*tokens;
	t_token			*last;
	struct dirent	*item;
	DIR				*dir;

	tokens = NULL;
	dir = opendir(".");
	item = readdir(dir);
	while (item)
	{
		if (item->d_name[0] != '.' && match(wildcard, item->d_name))
		{
			last = last_tok(tokens);
			if (!last)
				tokens = get_token(collect(ft_strdup(item->d_name), \
				garbage), garbage);
			else
				last->next = get_token(collect(ft_strdup(item->d_name), \
				garbage), garbage);
		}
		item = readdir(dir);
	}
	return (tokens);
}

t_token	*__norm(t_token **toks, t_gc **garbage);

t_token	*expand_all_wildcards(t_token **toks, t_gc **garbage)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!*toks)
		return (NULL);
	if (ft_strchr((*toks)->content, '*'))
	{
		tmp = (*toks)->next;
		tmp2 = (*toks);
		(*toks) = expand_wildcard((*toks)->content, garbage);
		if (!(*toks))
		{
			(*toks) = tmp2;
			tmp2->content = fix(tmp2->content, garbage);
		}
		last_tok(*toks)->next = tmp;
	}
	return (__norm(toks, garbage));
}
