/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:10:02 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/20 21:15:23 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **cmd_list, t_var *env)
{
	t_var	*var;

	var = env;
	if (!cmd_list || !*cmd_list || ft_strncmp(*cmd_list, "env", 255))
		return ;
	if (cmd_list[1])
	{
		g_tools.exit_status = 1;
		if (cmd_list[1][0] == '-' && cmd_list[1][1] != '\0')
			printf("%s: illegal option -- %c\n", cmd_list[0], cmd_list[1][1]);
		printf("usage: env [with no options] [with no arguments]\n");
		return ;
	}
	while (var)
	{
		printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
}
