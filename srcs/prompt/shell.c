/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/12 16:23:41 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check if a string contains more than one instance of a specific char
*/
static int	gt_one(char *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s++ == c)
			n++;
		if (n > 1)
			return (n);
	}
	return (n);
}

/*
	prompt with the file name of with ~ in home like oh_my_zsh (robbyrussell theme)
*/
char	*prompt(void)
{
	char	path[255];

	if (!getcwd(path, 255))
		return (ft_strdup("deleted"));
	if (!ft_strncmp(path, getenv("HOME"), 255))
		return (ft_strdup("~"));
	if (gt_one(path, '/') > 1)
		return (ft_strdup(ft_strrchr(path, '/') + 1));
	return (ft_strdup(path));
}

// test
char	*get_type(unsigned int type)
{
	if (type == PIPE)
		return ("pipe");
	if (type == REDIRECTION_IN)
		return ("input redirection");
	if (type == REDIRECTION_OUT)
		return ("output redirection");
	if (type == HEREDOC)
		return ("heredoc");
	if (type == APPEND)
		return ("append");
	if (type == WORD)
		return ("word");
	return ("none");
}

/*
	prompt in loop and execute shell commands 
*/
void	shell(int ac, char **av, char **env, t_gc **garbage)
{
	char	*line;
	char	*prom;

	(void) env;
	(void) ac;
	(void) av;
	printf("%s", GREEN);
	while (true)
	{
		g_tools.exit_status = 0;
		prom = collect(prompt(), garbage);
		line = collect(freadline(prom, CYAN), garbage);
		if (!line)
			return ;
		add_history(line);
		t_list *tok = tokenize(line, garbage);
		tok = replace_vars(tok, create_virtual_env(env, garbage), garbage);\
		t_token *toks = lexer(tok, garbage);
		for (t_token *tok = toks; tok; tok = tok->next)
			printf("%s: %s\n", get_type(tok->type), tok->content);
		//todo: execute the command
		//todo: save exit status of last command
	}
}
