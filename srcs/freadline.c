/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freadline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:20:08 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/23 17:44:49 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*freadline(char *promt, char *color)
{
	char	*bold;

	bold = "\033[1m";
	printf("➜  %s%s%s$ ", color, bold, promt);
	return (readline(RESET));
}
