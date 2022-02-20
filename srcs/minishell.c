/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:15:43 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/20 14:50:38 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tools	g_tools = {0};

void	sigint_handler(int sig)
{
	(void) sig;
	g_tools.exit_status = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_gc	*garbage;

	handle_signals();
	garbage = NULL;
	shell(ac, av, env, &garbage);
	rl_clear_history();
	clear(&garbage);
}
