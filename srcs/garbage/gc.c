/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:48:13 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/24 13:37:44 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	clear(t_gc **garbage)
{
	t_gc	*tmp;

	while (*garbage)
	{
		tmp = (*garbage)->next;
		free((*garbage)->rubbish);
		free(*garbage);
		*garbage = tmp;
	}
}

void	*collect(void *rubbish, t_gc **garbage)
{
	t_gc	*bin;

	if (!garbage)
		return (NULL);
	bin = malloc(sizeof(t_gc));
	bin->rubbish = rubbish;
	bin->next = (*garbage);
	(*garbage) = bin;
	return (rubbish);
}

void	*gc_malloc(size_t size, t_gc **garbage)
{
	void	*ptr;

	ptr = malloc(size);
	collect(ptr, garbage);
	return (ptr);
}
