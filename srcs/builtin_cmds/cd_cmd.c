/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:10:02 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/28 03:37:26 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_getenv(char *name, t_var *env)
{
	t_var	*var;
	int		max;

	var = env;
	while (var)
	{
		max = ft_strlen(var->name);
		if ((int) ft_strlen(name) > max)
			max = ft_strlen(name);
		if (!ft_strncmp(var->name, name, max))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

static void	ft_error(char **cmd_list)
{
	g_tools.exit_status = 1;
	err_printf("%s: illegal option -- %c\n", cmd_list[0], cmd_list[1][1]);
	err_printf("usage: cd [with no options]\n");
	return ;
}

static void	ft_error_home(void)
{
	g_tools.exit_status = 1;
	err_printf("minishell: cd: HOME not set");
}

static int	change_dir(char *path)
{
	char	str[1024];

	if (!ft_strncmp(path, ".", 255) && !getcwd(str, 1024))
		perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
	return (chdir(path));
}

void	cd_cmd(char **cmd_list, t_var *env)
{
	int		ret;
	char	*path;

	if (!cmd_list || !*cmd_list || ft_strncmp(cmd_list[0], "cd", 255))
		return ;
	if (cmd_list[1] && cmd_list[1][0] == '-' \
			&& cmd_list[1][1] != '\0' && cmd_list[1][1] != '-')
		ft_error(cmd_list);
	if (!cmd_list[1])
	{
		path = cd_getenv("HOME", env);
		if (!path)
			ft_error_home();
		ret = chdir(path);
	}
	else
		ret = change_dir(cmd_list[1]);
	if (ret < 0)
	{
		perror("cd");
		g_tools.exit_status = 1;
	}
}
