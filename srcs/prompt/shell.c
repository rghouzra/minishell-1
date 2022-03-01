/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/03/01 02:01:39 by akarafi          ###   ########.fr       */
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
	prompt in loop and execute shell commands 
*/
void	shell(int ac, char **av, char **env, t_gc **garbage)
{
	char	*line;
	char	*prom;

	(void) env;
	(void) ac;
	(void) av;
	t_var *venv = create_virtual_env(env, garbage);
	while (true)
	{
		prom = collect(prompt(venv), garbage);
		line = freadline(prom, CYAN, garbage);
		if (!line)
			return ;
		collect(line, garbage);
		add_history(line);
		t_list *tok = tokenize(line, garbage);
		tok = replace_vars(tok, venv, garbage);
		t_token *toks = lexer(tok, garbage);
		bool no_error = !check_errors(toks);
		if (no_error)
		{
			t_cmd *cmds = parse(toks, venv, garbage);
			g_tools.exit_status = 0;
			exec_cmd(cmds, &venv, garbage);
			//printf_cmds(cmds);
		}
		else
			g_tools.exit_status = 258;
		//todo: execute the command
		//todo: save exit status of last command
	}
}
