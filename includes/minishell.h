/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:13:40 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/10 16:17:40 by akarafi          ###   ########.fr       */
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

// global
typedef struct s_tools
{
	int	exit_status;
}	t_tools;

extern t_tools	g_tools;

// virtual env:
typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}		t_var;

t_var	*create_virtual_env(char **env, t_gc	**garbage);
char	*ft_getenv(char *name, t_var *env);

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