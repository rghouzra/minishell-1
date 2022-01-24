/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:13:50 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/24 14:22:35 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check if a string contains more than one instance of a specific char
*/
static int	gt_one(char *s, char c)
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

/*
	prompt with the file name of with ~ in home like oh_my_zsh (robbyrussell theme)
*/
static char	*prompt(void)
{
	char	path[255];

	if (!getcwd(path, 255))
		return (freadline("minishell", CYAN));
	if (!ft_strncmp(path, getenv("HOME"), 255))
		return (freadline("~", CYAN));
	if (gt_one(path, '/') > 1)
		return (freadline(ft_strrchr(path, '/') + 1, CYAN));
	return (freadline(path, CYAN));
}

/*
	prompt in loop and execute shell commands 
*/
void	shell(int ac, char **av, char **env, t_gc **garbage)
{
	char	*line;

	(void) env;
	(void) ac;
	(void) av;
	printf("%s", GREEN);
	while (true)
	{
		line = collect(prompt(), garbage);
		if (!line)
			return ;
		add_history(line);
		//todo: execute the command
		//todo: save exit status of last command
	}
}
