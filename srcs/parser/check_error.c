/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:29:03 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/19 22:53:47 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(int type)
{
	return (type == REDIRECTION_IN || type == REDIRECTION_OUT
		|| type == APPEND || type == HEREDOC);
}

bool	check_errors(t_token *tok)
{
	if (tok && tok->type == PIPE)
		return (printf("%s `|'\n", SYNTAX_ERR), true);
	while (tok)
	{
		if ((is_redirection(tok->type)) \
			&& (!tok->next || tok->next->type != WORD))
		{
			if (tok->next)
				return (printf("%s `%s'\n", \
					SYNTAX_ERR, tok->next->content), true);
			return (printf("%s `newline'\n", SYNTAX_ERR), true);
		}
		if (tok->type == PIPE && (!tok->next \
			|| (tok->next->type != WORD && !is_redirection(tok->next->type))))
		{
			if (tok->next)
				return (printf("%s `%s'\n", \
					SYNTAX_ERR, tok->next->content), true);
			return (printf("%s `newline'\n", SYNTAX_ERR), true);
		}
		tok = tok->next;
	}
	return (false);
}
