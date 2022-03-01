/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/03/01 02:53:39 by akarafi          ###   ########.fr       */
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
char	*prompt(t_var *env)
{
	char	path[255];

	if (!getcwd(path, 255))
		return (ft_strdup("deleted"));
	if (!ft_strncmp(path, ft_getenv("HOME", env), 255))
		return (ft_strdup("~"));
	if (gt_one(path, '/') > 1)
		return (ft_strdup(ft_strrchr(path, '/') + 1));
	return (ft_strdup(path));
}

/*
	go execute cmds
*/
void	execute_line(char *line, t_var **env, t_gc **garbage)
{
	t_list	*tok;
	t_token	*toks;
	t_cmd	*cmds;
	bool	no_error;

	tok = tokenize(line, garbage);
	tok = replace_vars(tok, *env, garbage);
	toks = lexer(tok, garbage);
	no_error = !check_errors(toks);
	if (no_error)
	{
		cmds = parse(toks, *env, garbage);
		g_tools.exit_status = 0;
		exec_cmd(cmds, env, garbage);
	}
	else
		g_tools.exit_status = 258;
}

/*
	prompt in loop and execute shell commands 
*/
void	shell(char **env, t_gc **garbage)
{
	char	*line;
	char	*prom;
	t_var	*venv;

	venv = create_virtual_env(env, garbage);
	while (true)
	{
		prom = collect(prompt(venv), garbage);
		line = freadline(prom, CYAN, garbage);
		if (!line)
			return ;
		collect(line, garbage);
		if (*line && *line != ' ')
			add_history(line);
		execute_line(line, &venv, garbage);
	}
}
