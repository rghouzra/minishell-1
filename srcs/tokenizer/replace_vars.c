/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:45:31 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/10 17:08:10 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char **value, char *line, t_var *env, t_gc **garbage)
{
	char	*name;

	name = NULL;
	if (*line == '?')
	{
		*value = collect(ft_itoa(g_tools.exit_status), garbage);
		return (line);
	}
	while (*line == '_' || ft_isalnum(*line))
	{
		name = collect(append_char(name, *line), garbage);
		line++;
	}
	*value = ft_getenv(name, env);
	return (line - 1);
}

char	*shearch_and_replace(char *line, t_var *env, t_gc **garbage)
{
	char	*ret;
	char	*value;

	(void) env;
	ret = "";
	while (*line)
	{
		if (*line == '$')
		{
			line = get_var_value(&value, line + 1, env, garbage);
			ret = collect(ft_strjoin(ret, value), garbage);
		}
		else
			ret = collect(append_char(ret, *line), garbage);
		line++;
	}
	return (ret);
}

t_list	*replace_vars(t_list *tokens, t_var *env, t_gc **garbage)
{
	t_list	*tok;

	tok = tokens;
	(void) garbage;
	(void) env;
	while (tok)
	{
		tok->content = shearch_and_replace(tok->content, env, garbage);
		tok = tok->next;
	}
	return (tokens);
}
