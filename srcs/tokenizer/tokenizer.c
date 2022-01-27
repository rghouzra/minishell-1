/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:08:09 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/27 17:43:16 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static char	*append_char(char *str, char c)
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

static char	*handle_quotes(char *s, t_list **tokens)
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
	}
	return (s);
}

static t_list	*quote_error(void)
{
	printf("syntax error: missing to close quotes\n");
	return (NULL);
}

t_list	*tokenize(char *s, t_gc **garbage)
{
	t_list	*tokens;
	t_list	*token;
	char	*start;

	tokens = NULL;
	start = s;
	while (*s)
	{
		if ((s == start || is_space(*s)) && (*(s + 1) && !is_space(*(s + 1))))
			ft_lstadd_back(&tokens, collect(ft_lstnew(NULL), garbage));
		if (*s == '\'' || *s == '"')
		{
			s = handle_quotes(s, &tokens);
			if (*s != '\'' && *s != '"')
				return (quote_error());
		}
		else if (tokens && !is_space(*s))
		{
			token = ft_lstlast(tokens);
			token->content = collect(append_char(token->content, *s), garbage);
		}
		s++;
	}
	return (tokens);
}
