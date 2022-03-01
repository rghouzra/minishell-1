/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:11:36 by aklaikel          #+#    #+#             */
/*   Updated: 2022/03/01 20:03:52 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * the builtin command:
 * echo   -> write arguments to the standard output.
 * cd     -> Change the current directory to DIR.
 * pwd    -> Print the current working directory.
 * export -> NAMEs are marked for automatic export to the environment of
    subsequently executed commands.
 * unset  -> For each NAME, remove the corresponding variable.
 * env    -> Set environment and execute command, or print environment.
 * exit   ->  Exit the shell with a status of N.
 */

static int	__handle_redirections(t_red *red, int fd)
{
	if (red->type == HEREDOC)
	{
		dup2(red->fd, 0);
		close(red->fd);
	}
	else if (red->type == REDIRECTION_IN)
	{
		fd = open(red->file, O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, 0);
		close(fd);
	}
	else
	{
		if (red->type == APPEND)
			fd = open(red->file, O_APPEND | O_CREAT | O_WRONLY, 0666);
		else
			fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (0);
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}

int	handle_redirections(t_red *red)
{
	int	fd;

	fd = 0;
	while (red)
	{
		if (__handle_redirections(red, fd) == 0)
		{
			g_tools.exit_status = 1;
			err_printf("minisehll: ");
			perror(red->file);
			return (0);
		}
		red = red->next;
	}
	return (1);
}

static bool	is_builtin(char *s)
{
	return (!ft_strncmp(s, "echo", 255) \
			|| !ft_strncmp(s, "cd", 255) \
			|| !ft_strncmp(s, "pwd", 255) \
			|| !ft_strncmp(s, "export", 255) \
			|| !ft_strncmp(s, "unset", 255) \
			|| !ft_strncmp(s, "env", 255) \
			|| !ft_strncmp(s, "exit", 255));
}

bool	is_builtin_cmd(char **cmd_list, \
	t_red *red, t_var **env, t_gc **garbage)
{
	int	fd[2];

	if (!cmd_list || !cmd_list[0] || !is_builtin(cmd_list[0]))
		return (false);
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (handle_redirections(red) == 0)
		;
	else if (!ft_strncmp(*cmd_list, "echo", 255))
		echo_cmd(cmd_list);
	else if (!ft_strncmp(*cmd_list, "cd", 255))
		cd_cmd(cmd_list, *env);
	else if (!ft_strncmp(*cmd_list, "pwd", 255))
		pwd_cmd(cmd_list);
	else if (!ft_strncmp(*cmd_list, "export", 255))
		export_cmd(cmd_list, env, garbage);
	else if (!ft_strncmp(*cmd_list, "unset", 255))
		unset_cmd(cmd_list, env);
	else if (!ft_strncmp(*cmd_list, "env", 255))
		env_cmd(cmd_list, *env);
	else if (!ft_strncmp(*cmd_list, "exit", 255))
		exit_cmd(cmd_list, garbage);
	return (dup2(fd[0], 0), dup2(fd[1], 1), close(fd[0]), close(fd[1]), true);
}

void	exec_cmd(t_cmd *cmd, t_var **env, t_gc **garbage)
{
	int	tmp_in;
	int	status;

	tmp_in = dup(0);
	if (cmd && !cmd->next \
		&& is_builtin_cmd(cmd->cmd_list, cmd->red, env, garbage))
		return ;
	exec_multiple_cmds(cmd, env, garbage);
	while (cmd)
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			g_tools.exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				printf(" Quit\n");
		}
		else
			g_tools.exit_status = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	g_tools.is_runing = 0;
	dup2(tmp_in, 0);
}
