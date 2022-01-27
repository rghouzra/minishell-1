/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:19:49 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/27 23:18:13 by ayoub            ###   ########.fr       */
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

char	*handle_quotes(char *s, t_list **tokens, t_gc **garbage)
{
	t_list	*token;
	char	c;

	c = *(s++);
	while (*s && *s != c)
	{
		token = ft_lstlast(*tokens);
		if (*s == '\\' && c == '"' && *(s + 1))
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
			s += 2;
		}
		else if (*s != c)
			token->content = append_char(token->content, *(s++));
		collect(token->content, garbage);
	}
	return (s);
}
