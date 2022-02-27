/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 00:21:46 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/27 03:19:59 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd(t_gc **garbage)
{
	t_cmd	*cmd;

	cmd = gc_malloc(sizeof(t_cmd), garbage);
	cmd->cmd_list = NULL;
	cmd->red = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	append_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*last;

	if (!cmds)
		return ;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	last = *cmds;
	while (last->next)
		last = last->next;
	last->next = cmd;
}

static char	**get_cmd_list(t_token *tok, t_gc **garbage)
{
	char	**cmd_list;
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tok;
	while (tok && tok->type != PIPE)
	{
		if (tok->type != WORD)
			tok = tok->next;
		else
			i++;
		tok = tok->next;
	}
	cmd_list = gc_malloc(sizeof(char *) * (i + 1), garbage);
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != WORD)
			tmp = tmp->next;
		else
			cmd_list[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (cmd_list[i] = NULL, cmd_list);
}

t_cmd	*parse(t_token *tok, t_var *env, t_gc **garbage)
{
	t_cmd	*cmds;
	t_cmd	*cmd;

	if (!tok)
		return (NULL);
	cmds = NULL;
	while (tok)
	{
		if (!cmds || tok->type == PIPE)
		{
			if (tok->type == PIPE)
				tok = tok->next;
			cmd = get_cmd(garbage);
			append_cmd(&cmds, cmd);
			cmd->cmd_list = get_cmd_list(tok, garbage);
			cmd->red = get_redirections(tok, env, garbage);
		}
		tok = tok->next;
	}
	return (cmds);
}
