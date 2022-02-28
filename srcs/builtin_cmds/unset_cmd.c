/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:30:34 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/28 03:31:04 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove(char *name, t_var **env)
{
	t_var	*var;

	var = *env;
	if (var && !ft_strncmp(name, var->name, 255))
	{
		*env = var->next;
		return ;
	}
	while (var)
	{
		if (var->next && !ft_strncmp(name, var->next->name, 255))
			var->next = var->next->next;
		var = var->next;
	}
}

void	unset_cmd(char **cmd_list, t_var **env)
{
	int	i;

	if (!cmd_list || !*cmd_list || ft_strncmp(cmd_list[0], "unset", 255))
		return ;
	if (cmd_list[1] && cmd_list[1][0] == '-' \
		&& cmd_list[1][1] != '\0' && cmd_list[1][1] != '-')
	{
		g_tools.exit_status = 1;
		err_printf("%s: bad option: -%c\n", cmd_list[0], cmd_list[1][1]);
		return ;
	}
	i = 0;
	while (cmd_list[++i])
		ft_remove(cmd_list[i], env);
}
