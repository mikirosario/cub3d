/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getscreenres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:26:34 by mrosario          #+#    #+#             */
/*   Updated: 2020/07/24 17:23:50 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

/*
** This function will attempt to set game screen resolution with the number
** at the address it is sent. If the int variable 'res' sent by the calling
** function is 0, setres will try to set the screen width. If it is non-zero,
** setres will try to set the screen height.
**
** If it succeeds at setting the screen width, it will return 1. If it
** succeeds at setting the screen height, it will return 2, signalling to
** the calling function that no further searching is required.
**
** Setres will only accept resolutions of at least 240 pixels and no greater
** than the default display resolution. If a user-provided resolution is
** considered invalid, it will throw a bad size error and return 0.
**
** To check the default display resolution on MacOS, part of the CoreGraphics
** library will be used. To check the number values, ft_atoi will be used.
*/

int		setres(const char *line, int res, unsigned int linenum)
{
	CGDirectDisplayID	displayid;

	displayid = CGMainDisplayID();
	ft_printf(RED"\nRES: %d\n"RESET, res);
	if (!res && (res = ft_atoi(line)) > 239 && \
	(size_t)res <= CGDisplayPixelsWide(displayid))
	{
		g_config.screenW = res;
		return (1);
	}
	else if (res && (res = ft_atoi(line)) > 239 && \
	(size_t)res <= CGDisplayPixelsHigh(displayid))
	{
		g_config.screenH = res;
		return (2);
	}
	g_iamerror.badresSize = linenum;
	return (0);
}

/*
** This function will attempt to determine if a line is meant to specify a
** Resolution by skipping any spaces and searching for the 'R' or 'r' specifier.
** If the specifier 'R' or 'r' is not found, the function will return 0. If the
** specifier is found, it will continue searching the line from the next address
** in the line.
**
** If it then finds a number, it will attempt to take it as a resolution
** value by sending it to the setres function. Setres will signal completion
** by returning 2 upon setting the resolution height to a user-defined values.
** It will return 1 if the width has been set to a user-defined value. It will
** return 0 if either the user-provided width or height was invalid.
**
** NOTE: If EITHER resolution width or height are invalid, NEITHER will be
** accepted!
**
** The 'res' variable will begin at 0. If 'res' 0 is sent to setres, it will
** attempt to set screen width with the provided number. If a non-zero value
** is sent to setres, it will attempt to set height with the provided number.
**
** If width has already been set (res is non-zero), the function will tolerate
** the characters 'x', 'X' and/or ',' between the width and height. Otherwise
** ONLY spaces and digits will be tolerated, and any other characters will be
** considered bad characters.
**
** If the function detects bad characters it will throw a syntax error and
** return zero. If setres fails to set a resolution at any point (returns zero),
** the getres function will also return zero. If setres successfully sets both
** screen width and screen height with numbers provided in the string line, the
** getres function will return 1.
*/

int		getres(const char *line, unsigned int linenum)
{
	int	res;

	if (!line)
		return (0);
	res = 0;
	line = ft_skipspaces(line);
	if (*line != 'R' && *line != 'r')
		return (0);
	line++;
	while (*line && ((ft_isspace(*line)) || ft_isdigit(*line) || \
	(res && (*line == 'x' || *line == 'X' || *line == ','))))
	{
		if (ft_isdigit(*line))
		{
			if ((res = setres(line, res, linenum)) != 1)
				return (res == 2 ? 1 : 0);
			line = ft_skipdigits(line);
		}
		else
			line++;
	}
	if (*line)
		g_iamerror.badresSyn = linenum;
	return (0);
}
