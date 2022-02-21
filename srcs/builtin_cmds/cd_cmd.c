/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:10:02 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/21 02:37:39 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char **cmd_list)
{
	char	**cwd;
	int		ret;

	if (!cmd_list || !*cmd_list || ft_strncmp(cmd_list[0], "cd", 255))
		return ;
	if (cmd_list[1] && cmd_list[1][0] == '-' \
			&& cmd_list[1][1] != '\0' && cmd_list[1][1] != '-')
	{
		g_tools.exit_status = 1;
		printf("%s: illegal option -- %c\n", cmd_list[0], cmd_list[1][1]);
		printf("usage: cd [with no options]\n");
		return ;
	}
	if (!cmd_list[1])
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(cmd_list[1]);
	if (ret < 0)
	{
		perror("cd");
		g_tools.exit_status = 1;
	}
}
