/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:18:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/20 21:39:47 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(char **cmd_list)
{
	char	cwd[1024];
	int		i;

	i = 0;
	if (!cmd_list || !*cmd_list || ft_strncmp(cmd_list[0], "pwd", 255))
		return ;
	if (cmd_list[1] && cmd_list[1][0] == '-' \
		&& cmd_list[1][1] != '\0' && cmd_list[1][1] != '-')
	{
		g_tools.exit_status = 1;
		printf("%s: illegal option -- %c\n", cmd_list[0], cmd_list[1][1]);
		printf("usage: env [with no options]\n");
		return ;
	}
	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
	else
		perror("pwd:");
}
