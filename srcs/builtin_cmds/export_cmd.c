/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <akarafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:30:18 by akarafi           #+#    #+#             */
/*   Updated: 2022/02/22 02:06:12 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_var *env)
{
	while (env)
	{
		printf("declare -x %s\n", env->name);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		env = env->next;
	}
}

static bool	is_not_valid(char *line, int i)
{
	return ((line[i] == '+' && line[i + 1] != '=' && line[i]) \
		|| (line[0] != '_' && !ft_isalpha(line[0]))
		|| (line[i] != '=' && line[i] != '+' \
		&& !ft_isalnum(line[i]) && line[i]));
}

static void	append_to_env(char **tab, bool append, \
	t_var **v_env, t_gc **garbage)
{
	t_var	*var;
	t_var	*head;

	if (!v_env)
		return ;
	var = *v_env;
	while (var)
	{
		if (!ft_strncmp(var->name, tab[0], 255) && (var->value || tab[1]))
		{
			if (append && var->value)
				var->value = collect(ft_strjoin(var->value, tab[1]), garbage);
			else
				var->value = tab[1];
			return ;
		}
		var = var->next;
	}
	var = gc_malloc(sizeof(t_var), garbage);
	var->name = tab[0];
	var->value = tab[1];
	var->next = NULL;
	add_back(v_env, var);
}

static int	append_var(char *line, t_var **env, t_gc **garbage)
{
	char	*name;
	char	*value;
	char	*tab[2];
	int		i;

	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	if (is_not_valid(line, i))
	{
		g_tools.exit_status = 1;
		return (printf("minishell: export: `%s': not a valid identifier\n", \
		line), -1);
	}
	name = collect(ft_substr(line, 0, i), garbage);
	if (line[i] == 0)
		value = NULL;
	else if (line[i] == '+')
		value = collect(ft_strdup(&line[i + 2]), garbage);
	else
		value = collect(ft_strdup(&line[i + 1]), garbage);
	tab[0] = name;
	tab[1] = value;
	return (append_to_env(tab, (line[i] == '+'), env, garbage), 0);
}

void	export_cmd(char **cmd_list, t_var **env, t_gc **garbage)
{
	t_var	*var;
	int		i;

	if (!env || !cmd_list \
		|| !*cmd_list || ft_strncmp(cmd_list[0], "export", 255))
		return ;
	if (!cmd_list[1])
	{
		print_export(*env);
		return ;
	}
	if (cmd_list[1][0] == '-' \
		&& cmd_list[1][1] != '\0' && cmd_list[1][1] != '-')
	{
		g_tools.exit_status = 1;
		printf("%s: illegal option -- %c\n", cmd_list[0], cmd_list[1][1]);
		printf("usage: export [with no options]\n");
		return ;
	}
	i = 0;
	while (cmd_list[++i])
		if (append_var(cmd_list[i], env, garbage) == -1)
			return ;
}
