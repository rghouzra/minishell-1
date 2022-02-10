/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:57:17 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/10 16:48:13 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	get the value of a var in the original env
*/
char	*get_value(char *line)
{
	int	start;
	int	len;

	start = 0;
	while (start[line] != '=' && start[line])
		start++;
	start++;
	len = 0;
	while (line[len + start])
		len++;
	return (ft_substr(line, start, len));
}

/*
	get the name of a var in the original env
*/
char	*get_name(char *line)
{
	int		len;

	len = 0;
	while (len[line] != '=' && len[line])
		len++;
	return (ft_substr(line, 0, len));
}

/*
	get line from the original env and add it to the virtual env
*/
void	add_variable(t_var	**v_env, char	*line, t_gc	**garbage)
{
	t_var	*var;
	t_var	*head;

	if (!v_env)
		return ;
	var = gc_malloc(sizeof(t_var), garbage);
	var->name = collect(get_name(line), garbage);
	var->value = collect(get_value(line), garbage);
	var->next = NULL;
	if (!*v_env)
	{
		*v_env = var;
		return ;
	}
	head = *v_env;
	while (head->next)
		head = head->next;
	head->next = var;
}

/*
	create a virtual env where we can add new variables or re assign them
*/
t_var	*create_virtual_env(char **env, t_gc	**garbage)
{
	t_var	*v_env;
	int		i;

	v_env = NULL;
	i = 0;
	while (env[i])
		add_variable(&v_env, env[i++], garbage);
	return (v_env);
}

char	*ft_getenv(char *name, t_var *env)
{
	t_var	*var;
	int		max;

	var = env;
	while (var)
	{
		max = ft_strlen(var->name);
		if ((int) ft_strlen(name) > max)
			max = ft_strlen(name);
		if (!ft_strncmp(var->name, name, max))
			return (var->value);
		var = var->next;
	}
	return ("");
}
