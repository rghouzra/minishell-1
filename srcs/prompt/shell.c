/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/28 21:14:32 by akarafi          ###   ########.fr       */
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

void	printf_cmds(t_cmd *cmd)
{
	char **cmd_list;
	while (cmd)
	{
		cmd_list = cmd->cmd_list;
		if (!cmd_list || !cmd_list[0])
			printf("no command found\n");
		else
		{
			for (int i = 0; cmd_list[i]; i++)
				printf("%s ", cmd_list[i]);
			printf("\n");
		}
		for (t_red *red = cmd->red; red; red = red->next)
		{
			printf("red type: %s\n", get_type(red->type));
			printf("red file: %s\n", red->file);
			printf("red fd: %d\n", red->fd);
		}
		printf("\n");
		cmd = cmd->next;
	}
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
			exec_cmd(cmds, &venv, garbage);
			//printf_cmds(cmds);
		}
		g_tools.exit_status = 0;
		if (!no_error)
			g_tools.exit_status = 258;
		//todo: execute the command
		//todo: save exit status of last command
	}
}
