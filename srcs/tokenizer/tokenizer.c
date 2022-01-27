/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:08:09 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/27 23:04:42 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static bool	is_redirection(char *s)
{
	return ((*s == '<' && *(s + 1) == '<' && *(s + 2) != '<') \
			|| (*s == '>' && *(s + 1) == '>' && *(s + 2) != '>') \
			|| (*s == '<' && *(s + 1) != '<') \
			|| (*s == '>' && *(s + 1) != '>')
	);
}

static t_list	*quote_error(void)
{
	printf("syntax error: missing to close quotes\n");
	return (NULL);
}

static char	*special(char *s, t_list **tokens, t_gc **garbage)
{
	t_list	*last_token;
	int		n;

	last_token = ft_lstlast(*tokens);
	n = 1;
	if ((*s == '>' && *(s + 1) == '>' && *(s + 2) != '>') \
		|| (*s == '<' && *(s + 1) == '<' && *(s + 2) != '<'))
		n = 2;
	if (last_token->content)
		ft_lstadd_back(tokens, \
			collect(ft_lstnew(collect(ft_substr(s, 0, n), garbage)), garbage));
	else
		last_token->content = \
			collect(append_char(last_token->content, *s), garbage);
	ft_lstadd_back(tokens, collect(ft_lstnew(NULL), garbage));
	s += n;
	return (s);
}

t_list	*tokenize(char *s, t_gc **garbage)
{
	t_list	*tokens;
	t_list	*token;

	tokens = NULL;
	while (*s)
	{
		if ((!tokens || is_space(*s)) && (*(s + 1) && !is_space(*(s + 1))))
			ft_lstadd_back(&tokens, collect(ft_lstnew(NULL), garbage));
		else if (*s == ';' || *s == '|' || is_redirection(s))
			s = special(s, &tokens, garbage);
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
