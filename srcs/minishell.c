/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:15:43 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/24 18:10:17 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	char	*prom;
	char	*bold;

	(void) sig;
	bold = "\033[1m";
	prom = prompt(); //! collect in garbage and change exit status
	printf("\n%s➜  %s%s%s%s ", RED, CYAN, bold, prom, RESET);
	rl_replace_line("", 0);
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
