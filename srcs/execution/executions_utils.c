/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:16:49 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/28 21:16:05 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute(t_cmd *cmd, int out, t_var **env, t_gc **garbage)
{
	char	**cmd_lst;
	t_red	*red;
	char	*word;
	// change later
	char *envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "TZ=UTC0",
        "USER=beelzebub",
        "LOGNAME=tarzan",
        0
    };

	cmd_lst = cmd->cmd_list;
	red = cmd->red;
	dup2(out, 1);
	close(out);
	if (is_builtin_cmd(cmd_lst, red, env, garbage) || !handle_redirections(red))
		exit(g_tools.exit_status);
	if (!cmd_lst || !cmd_lst[0])
		exit(0);
	word = cmd_lst[0];
	cmd_lst[0] = get_path(word, *env, garbage);
	if (!cmd_lst[0])
	{
		err_printf("minishell: ");
		perror(word);
		exit(1);
	}
	(void) envp;
	execve(cmd_lst[0], cmd_lst, NULL);
	perror(word);
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
		id = fork();
		if (id < 0)
			return (perror("fork"));
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute(cmd, fd[1], env, garbage);
		}
		if (cmd->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		cmd = cmd->next;
	}
}
