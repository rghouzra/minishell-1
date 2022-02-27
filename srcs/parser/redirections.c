/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:40:37 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/27 03:09:29 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_red(t_red **reds, t_red *red)
{
	t_red	*last;

	if (!reds)
		return ;
	if (!*reds)
	{
		*reds = red;
		return ;
	}
	last = red;
	while (last->next)
		last = last->next;
	last->next = red;
}

int	heredoc(char *end, t_var *env, t_gc **garbage)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	while (true)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strncmp(line, end, 255))
			return (close(fd[1]), fd[0]);
		collect(line, garbage);
		line = shearch_and_replace(line, env, garbage);
		write(fd[1], line, ft_strlen(line));
	}
}

t_red	*get_redirections(t_token *tok, t_var *env, t_gc **garbage)
{
	t_red	*reds;
	t_red	*red;

	reds = NULL;
	while (tok && tok->next && tok->type != PIPE)
	{
		if (tok->type != PIPE && tok->type != WORD)
		{
			red = gc_malloc(sizeof(t_red), garbage);
			red->type = tok->type;
			red->fd = -1;
			red->next = NULL;
			red->file = tok->next->content;
			if (red->type == HEREDOC)
				red->fd = heredoc(red->file, env, garbage);
			append_red(&reds, red);
			tok = tok->next;
		}
		tok = tok->next;
	}
	return (reds);
}
