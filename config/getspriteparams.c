/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getspriteparams.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:08:49 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 18:24:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t g_iamerror;

/*
** Note: To distinguish this line from the SO/so line that passes the south
** wall texture path, after skipping any initial spaces, we will terminate
** this function if the character we find is NOT an 'S' and is NOT an 's',
** OR (that is, even if it IS) if the character following it IS an 'O' or IS
** an 'o'. I don't like segfaults, so I also tell it to terminate the function
** if it finds a NULL there. ;p
*/

int		getsprite(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'S' && *line != 's') || (!(*(line + 1)) || \
	*(line + 1) == 'O' || *(line + 1) == 'o'))
		return (0);
	line = ft_skipspaces(++line);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badsprsyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(g_normiImg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(g_normiImg.texpath, line, i);
	return (1);
}
