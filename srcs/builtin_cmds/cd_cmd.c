/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:10:02 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/22 17:51:43 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char **cmd_list)
{
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
