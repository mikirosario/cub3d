/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getceilingfloorparams_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:50:30 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/05 15:18:23 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

extern t_error g_iamerror;

/*
** These functions will retrieve the floor and ceiling colors specified in the
** cub file, if any. Colors will be specified in RGB format and converted into
** hexadecimal format by the functions. The hexadecimal values will then be
** stored for use by the raycaster in the appropriate variable.
**
** These functions will skip any spaces and search for the specifier 'F' or 'f'
** for the floor and 'C' or 'c' for the ceiling function, respectively. Then
** they will skip any spaces after the specifier. If the character for a digit
** is found, its address will be passed to atoi to convert the number comprised
** by the found digit up to the first non-digit in the string into an integer.
** The color variable will be used to count how many colors have been retrieved
** and to move across the rgb color array, where it will store a color in each
** array position, red at 0, green at 1 and blue at 2.
**
** Colors may be separated by spaces and/or commas in the cub file. The
** specifiers may be separated from the colors by spaces only. If any character
** except for a space (or a comma between the colors) is found, the color
** retrieval will stop and the function will exit.
**
** When all three rgb colors have been successfully retrieved (color == 3),
** create_trgb will be called to convert the values into a single hexadecimal
** color value, and the result will be stored for use by the raycaster. The
** functions will then return 1.
**
** If the functions fail to retrieve all three colors for any reason, they will
** return 0.
*/

const char	*getnumber(int *rgb, const char *line, char callfuncid)
{
	if ((*rgb = ft_atoi(line)) > 255)
	{
		if (callfuncid == 'f')
			g_iamerror.fcoloroutofrange = 1;
		else
			g_iamerror.ccoloroutofrange = 1;
	}
	line = ft_skipdigits(line);
	return (line);
}

int			getftex(const char *line, unsigned int linenum, int *checked)
{
	int			i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if (*line != 'F' && *line != 'f')
		return (0);
	*checked = 1;
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badfloorsyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(g_floorimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(g_floorimg.texpath, line, i);
	return (!g_iamerror.badfloorsyn ? 1 : 0);
}

int			getctex(const char *line, unsigned int linenum, int *checked)
{
	int			i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if (*line != 'C' && *line != 'c')
		return (0);
	*checked = 1;
	line = ft_skipspaces(line += 2);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badceilsyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(g_ceilingimg.texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(g_ceilingimg.texpath, line, i);
	return (!g_iamerror.badceilsyn ? 1 : 0);
}
