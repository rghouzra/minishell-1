/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:56:13 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/11 22:55:11 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_token(char *content, t_gc	**garbage)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), garbage);
	token->content = content;
	token->type = WORD;
	token->next = NULL;
	return (token);

}

static void	append_token(t_token **tokens, t_token *token)
{
	t_token	*last;

	if (!tokens)
		return ;
	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = token;
}

static t_token	*create_token(char *content, t_gc **garbage)
{
	t_token	*token;

	token = get_token(content, garbage);
	if (!ft_strncmp("|", content, 255))
		token->type = PIPE;
	else if (!ft_strncmp(">>", content, 255))
		token->type = APPEND;
	else if (!ft_strncmp(">", content, 255))
		token->type = REDIRECTION_OUT;
	else if (!ft_strncmp("<<", content, 255))
		token->type = HEREDOC;
	else if (!ft_strncmp("<", content, 255))
		token->type = REDIRECTION_IN;
	return (token);
}

t_token	*lexer(t_list	*toks, t_gc **garbage)
{
	t_token	*tokens;
	t_token	*token;

	tokens = NULL;
	while (toks)
	{
		token = create_token(toks->content, garbage);
		append_token(&tokens, token);
		toks = toks->next;
	}
	return (tokens);
}
