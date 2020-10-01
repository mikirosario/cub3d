/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getspriteparams.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:08:49 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/01 20:46:22 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

extern t_error g_iamerror;

/*
** Note: To distinguish this line from the SO/so line that passes the south
** wall texture path, after skipping any initial spaces, we will terminate
** this function if the character we find is NOT an 'S' and is NOT an 's',
** OR (that is, even if it IS) if the character following it IS an 'O' or IS
** an 'o'. It's OK if it's NULL, it will just trigger a bad syntax error because
** (*line != '.'). ^_^
*/

int		getsprite(const char *line, unsigned int linenum, int *checked)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'S' && *line != 's') || \
	(*(line + 1) == 'O' || *(line + 1) == 'o'))
		return (0);
	*checked = 1;
	line = ft_skipspaces(++line);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badsprsyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(g_sprt2img.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(g_sprt2img.texpath, line, i);
	return (1);
}
