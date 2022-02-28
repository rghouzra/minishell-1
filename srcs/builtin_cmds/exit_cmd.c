/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 02:11:16 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/28 18:43:45 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbr(const char *str, t_gc **garbage)
{
	int		i;
	int		n;
	long	result;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			n = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (err_printf("exit: %s: numeric argument required\n", str), \
			clear(garbage), exit(255), 255);
	return (result * n);
}

void	exit_cmd(char **cmd_list, t_gc **garbage)
{
	int	status;

	if (!cmd_list || !*cmd_list || ft_strncmp(*cmd_list, "exit", 255))
		return ;
	if (!cmd_list[1])
	{
		clear(garbage);
		exit(0);
	}
	status = get_nbr(cmd_list[1], garbage);
	if (cmd_list[2])
	{
		g_tools.exit_status = 1;
		printf("minishell: exit: too many arguments\n");
	}
	else
	{
		clear(garbage);
		exit(status);
	}
}
