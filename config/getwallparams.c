/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getwallparams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:13:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 18:23:36 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

/*
** These functions evaluate the line passed as an argument. Any spaces at the
** beginning are skipped. The functions will then look for the specifiers NO,
** SO, WE or EA, depending on the function, each corresponding to the NORTH,
** SOUTH, WEST and EAST walls.
**
** If the specifier specific to each function (NO for getno, SO for getso,
** etc.) is not found, the function will return 0. If the specifier is found,
** the function will skip any spaces thereafter and look for the path
** information './'. If './' is not found, the function will return 0.
**
** If the specifier and path information are found, the function will count
** all printable characters starting with and including './'. It will then
** attempt to use ft_calloc to reserve memory for a string containing all
** printable characters found plus 1 and point the texpath variable of the
** associated struct to its address. If the memory reservation fails, the
** function will set the global g_iamerror.mallocfail flag to 1 to report it
** and then return 0.
**
** If all tasks have been successful to this point, the function will use
** ft_memcpy to copy line from './' to the reserved block of memory, passing
** the number of printable characters found as an argument to copy until the
** last printable character.
**
** Finally, the texpath will be printed out on screen for user reference.
** PROBABLY MOVE THIS TO A DEDICATED FUNCTION TO CONTROL WHERE IT IS PRINTED.
*/

int		getno(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'N' && *line != 'n') || \
	(*(line + 1) != 'O' && *(line + 1) != 'o'))
		return (0);
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badnosyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(nowallimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(nowallimg.texpath, line, i);
	return (1);
}

int		getso(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'S' && *line != 's') || \
	(*(line + 1) != 'O' && *(line + 1) != 'o'))
		return (0);
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badsosyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(sowallimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(sowallimg.texpath, line, i);
	return (1);
}

int		getwe(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'W' && *line != 'w') || \
	(*(line + 1) != 'E' && *(line + 1) != 'e'))
		return (0);
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badwesyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(wewallimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(wewallimg.texpath, line, i);
	return (1);
}

int		getea(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'E' && *line != 'e') || \
	(*(line + 1) != 'A' && *(line + 1) != 'a'))
		return (0);
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badeasyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(eawallimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(eawallimg.texpath, line, i);
	return (1);
}
