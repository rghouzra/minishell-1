/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:13:40 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/27 23:18:36 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "colors.h"
# include "gc.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

// custom readline:
char	*freadline(char *prompt, char *color);
char	*prompt(void);

// shell:
void	shell(int ac, char **av, char **env, t_gc **garbage);

// tokinizer
t_list	*tokenize(char *s, t_gc **garbage);
char	*handle_quotes(char *s, t_list **tokens, t_gc **garbage);
char	*append_char(char *str, char c);
#endif