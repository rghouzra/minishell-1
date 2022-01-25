/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freadline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:20:08 by ayoub             #+#    #+#             */
/*   Updated: 2022/01/23 21:24:16 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*freadline(char *prompt, char *color)
{
	char	*bold;

	bold = "\033[1m";
	printf("➜  %s%s%s ", color, bold, prompt);
	return (readline(RESET));
}
