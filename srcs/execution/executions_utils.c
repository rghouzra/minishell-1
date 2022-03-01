/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:16:49 by akarafi           #+#    #+#             */
/*   Updated: 2022/03/01 22:40:15 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_as_array(t_var *env, t_gc	**garbage)
{
	t_var	*var;
	char	**envp;
	int		i;

	i = 0;
	var = env;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	envp = gc_malloc((i + 1) * sizeof(char *), garbage);
	i = -1;
	while (var)
	{
		if (var->value)
		{
			envp[++i] = var->name;
			envp[i] = collect(append_char(envp[i], '='), garbage);
			envp[i] = collect(ft_strjoin(envp[i], var->value), garbage);
		}
		var = var->next;
	}
	return (envp[++i] = NULL, envp);
}

static void	execute(t_cmd *cmd, int fd[], t_var **env, t_gc **garbage)
{
	char	**cmd_lst;
	char	*word;
	char	**envp;

	cmd_lst = cmd->cmd_list;
	envp = get_env_as_array(*env, garbage);
	if (cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
	if (is_builtin_cmd(cmd_lst, cmd->red, env, garbage) \
		|| !handle_redirections(cmd->red))
		exit(g_tools.exit_status);
	if (!cmd_lst || !cmd_lst[0])
		exit(0);
	word = cmd_lst[0];
	cmd_lst[0] = get_path(word, *env, garbage);
	if (!cmd_lst[0])
	{
		err_printf("minishell: %s: command not found\n", word);
		exit(1);
	}
	execve(cmd_lst[0], cmd_lst, envp);
}

static void	run_cmd(t_cmd *cmd, t_var **env, int fd[], t_gc **garbage)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute(cmd, fd, env, garbage);
	perror(cmd->cmd_list[0]);
	exit(1);
}

void	exec_multiple_cmds(t_cmd *cmd, t_var **env, t_gc **garbage)
{
	int	fd[2];
	int	id;

	while (cmd)
	{
		if (cmd->next)
			pipe(fd);
		g_tools.is_runing = 1;
		id = fork();
		if (id < 0)
			return (perror("fork"));
		if (id == 0)
			run_cmd(cmd, env, fd, garbage);
		if (cmd->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		else
			close(0);
		cmd = cmd->next;
	}
}
