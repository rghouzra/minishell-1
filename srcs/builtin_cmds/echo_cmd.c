/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:10:02 by aklaikel          #+#    #+#             */
/*   Updated: 2022/02/22 02:46:35 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_newline(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (1);
	return (0);
}

static void	print_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		printf("%s", words[i++]);
		if (words[i])
			printf(" ");
	}
}

void	echo_cmd(char **cmd_list)
{
	int		i;
	int		j;
	bool	is_set;

	if (!cmd_list || !*cmd_list || ft_strncmp(cmd_list[0], "echo", 255))
		return ;
	i = 1;
	is_set = true;
	while (cmd_list[i] && cmd_list[i][0] == '-')
	{
		if (!valid_newline(cmd_list[i]))
			is_set = false;
		else
			break ;
		i++;
	}
	print_words(&cmd_list[i]);
	if (is_set)
		printf("\n");
}
