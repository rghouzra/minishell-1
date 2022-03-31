/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 04:01:58 by ahimmi            #+#    #+#             */
/*   Updated: 2022/03/31 04:04:12 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fix(char *s, t_gc **garbage);

t_token	*__norm(t_token **toks, t_gc **garbage)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*current;
	t_token	*previous;

	tmp = *toks;
	while (tmp)
	{
		current = tmp->next;
		previous = tmp;
		if (current && ft_strchr(current->content, '*'))
		{
			tmp2 = current->next;
			previous->next = expand_wildcard(current->content, garbage);
			if (!previous->next)
			{
				previous->next = current;
				current->content = fix(current->content, garbage);
			}
			last_tok(previous)->next = tmp2;
		}
		tmp = tmp->next;
	}
	return (*toks);
}
