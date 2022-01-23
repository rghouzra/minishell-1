/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:50:26 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/23 20:00:51 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H
# include <stdlib.h>
# include <stddef.h>

typedef struct s_gc
{
	void		*rubbish;
	struct s_gc	*next;
}	t_gc;

void	collect(void *rubbish, t_gc **garbage);
void	*gc_malloc(size_t size, t_gc **garbage);
void	clear(t_gc **garbage);

#endif