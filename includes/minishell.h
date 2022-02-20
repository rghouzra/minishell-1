/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:13:40 by ayoub             #+#    #+#             */
/*   Updated: 2022/02/20 21:27:28 by akarafi          ###   ########.fr       */
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
char	*freadline(char *prompt, char *color, t_gc **garbage);
char	*prompt(void);

// shell:
void	shell(int ac, char **av, char **env, t_gc **garbage);

// tokinizer
t_list	*tokenize(char *s, t_gc **garbage);
char	*handle_quotes(char *s, t_list **tokens, t_gc **garbage);
char	*append_char(char *str, char c);
t_list	*replace_vars(t_list *tokens, t_var *env, t_gc **garbage);

// lexer

# define WORD 1U
# define PIPE 2U
# define REDIRECTION_IN 4U
# define REDIRECTION_OUT 8U
# define APPEND 16U
# define HEREDOC 32U

typedef struct s_token
{
	char			*content;
	unsigned int	type;
	struct s_token	*next;
}		t_token;

t_token	*lexer(t_list	*toks, t_gc **garbage);

// parser:
# define SYNTAX_ERR "minishell: syntax error near unexpected token"

bool	check_errors(t_token *tok);

// builtin commands:
void	env_cmd(char **cmd_list, t_var *env);

#endif