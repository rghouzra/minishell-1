/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:45:31 by akarafi           #+#    #+#             */
/*   Updated: 2022/03/23 23:56:16 by ahimmi           ###   ########.fr       */
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
	if (!ft_isalnum(*line) && *line != '_')
	{
		*value = "$";
		if (*line != -1)
			return (line - 1);
		return (line);
	}
	while (*line == '_' || ft_isalnum(*line))
	{
		name = collect(append_char(name, *line), garbage);
		line++;
	}
	if (!name)
		name = "";
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
		if (tok->content)
		{
			tok->content = expand_wildcard(tok->content, garbage);
			tok->content = shearch_and_replace(tok->content, env, garbage);
		}
		tok = tok->next;
	}
	return (tokens);
}
