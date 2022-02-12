/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:19:49 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/12 16:29:26 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	char	*tmp;
	int		len;

	if (!str)
	{
		tmp = malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
		return (tmp);
	}
	len = ft_strlen(str);
	tmp = malloc(len + 2);
	ft_strlcpy(tmp, str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = 0;
	return (tmp);
}

static void	sub_handle_quotes(t_list *token, char *s, char c)
{
	if (*(s + 1) == '\\')
		token->content = append_char(token->content, '\\');
	else if (*(s + 1) == c)
		token->content = append_char(token->content, c);
	else
	{
		token->content = append_char(token->content, *s);
		token->content = append_char(token->content, *(s + 1));
	}
}

char	*handle_quotes(char *s, t_list **tokens, t_gc **garbage)
{
	t_list	*token;
	char	c;

	c = *(s++);
	token = ft_lstlast(*tokens);
	if (*s == c && !token->content)
		token->content = "";
	while (*s && *s != c)
	{
		if (*s == '\\' && c == '"' && *(s + 1))
		{
			sub_handle_quotes(token, s, c);
			s += 2;
		}
		else if (*s != c)
		{
			token->content = append_char(token->content, *(s++));
			if (c == '\'' && *(s - 1) == '$')
				token->content = append_char(token->content, -1);
		}
		collect(token->content, garbage);
	}
	return (s);
}
