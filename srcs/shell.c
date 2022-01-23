/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/23 21:34:15 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(char *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s++ == c)
			n++;
		if (n > 1)
			return (n);
	}
	return (n);
}

static char	*prompt(void)
{
	char	path[255];

	if (!getcwd(path, 255))
		return (freadline("minishell", CYAN));
	if (!ft_strncmp(path, "/", 255))
		return (freadline("/", CYAN));
	if (!ft_strncmp(path, getenv("HOME"), 255))
		return (freadline("~", CYAN));
	if (count(path, '/') > 1)
		return (freadline(ft_strrchr(path, '/') + 1, CYAN));
	return (freadline(path, CYAN));
}

void	shell(char **env)
{
	char	*line;

	(void) env;
	while (true)
	{
		line = prompt();
		if (!line)
		{
			rl_clear_history();
			free(line);
			return ;
		}
		add_history(line);
		free(line);
	}
}
