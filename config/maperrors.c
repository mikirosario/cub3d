/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maperrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:47:38 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 17:44:54 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error g_iamerror;

/*
** This function is a line-saver. It is used to retrieve error locations from
** error flag arrays that save the coordinates of map errors.
*/

void	geterrorlocation(unsigned int *errorarray, unsigned int *x, \
unsigned int *y)
{
	*x = errorarray[0];
	*y = errorarray[1];
}

/*
** This function is a line-saver. It is used to record error locations to
** error flag arrays that save the coordinates of map errors.
*/

int		recorderrorlocation(unsigned int *errorarray, unsigned int x, \
unsigned int y, int returnvalue)
{
	errorarray[0] = x;
	errorarray[1] = y;
	return (returnvalue);
}

/*
** This function is a line-saver. It is used to record error locations to
** the toomanyplayers flag array that because using recorderrorlocation to
** do this put me over norminette's line limit by ONE BEEPING LINE.
*/

char	toomanyplayers(unsigned int x, unsigned int y, char foundplayer)
{
	g_iamerror.toomanyplayers[0] = x;
	g_iamerror.toomanyplayers[1] = y;
	return (foundplayer);
}

/*
** This function will handle all generic map errors that don't report error
** location on the map. If no player was found, the no player found error
** will be printed. If a player was found, the character in the map will
** be changed to P to indicate where it was found when the map is printed
** or the line with the player is printed for the user.
**
** If the map was rejected because it had less than 3 lines, the associated
** error will be printed. If the map occupies more than the MAPMEMCAP, which
** is set in the cub3d.h, we'll print the mapTooBig error.
*/

void	generalmaperrors(void)
{
	if (g_iamerror.noplayer)
		ft_putstr(noPlayer, strlen(noPlayer));
	if (g_iamerror.badmap3line)
		ft_putstr(badMap3line, strlen(badMap3line));
	if (g_iamerror.maptoobig)
		ft_printf("%.63s""%u""%s\n", mapTooBig, MAPMEMCAP, (mapTooBig + 63));
}

/*
** This function will handle all map errors involving errors whose location in
** cub file is reported to the user through the error message.
**
** To achieve this, first we retrieve g_iamerror.premaplines, a variable that
** records how many lines were read from the file before the first map line
** was found. Then we run a special variant of the unflood function that will
** fill in all the characters analysed by the floodfill function before it
** found an out of bounds error with '.'.
**
** Then we retrieve the location of character in the map that caused floodfill
** to return an out of bounds error. Note that this location should never be a
** NULL terminator marking the end of a string, as the floodfill function is
** programmed to record only the position FROM WHICH the out of bounds was
** detected, not the out of bounds position itself (even if the out of bounds
** is addressable), so it should always be safe to print x + 1. ^_^
**
** Then we'll replace the error character with an X, to help the user see it
** better when we print it, unless it was a 'P' (standing for player starting
** location), in which case we will leave the 'P'.
**
** We'll then use ft_printf to print the line number where the error was found
** in the file. Since we start counting lines at 0 and the file starts at 1,
** that will be y + 1 + o (all the lines we counted before the map). Then we
** print the line up until the error by passing the error location in the
** line (x) as a precision flag. Then we print the error character. Then we
** print the rest of the line after the error character, which might just be
** NULL if the error character was the last one on the line. Finally, we print
** a new line with the associated error message.
**
** We do this for both the 'out of bounds' and 'too many players' errors, if
** they are detected.
**
** When we're done, we'll free both the sprite list, if it exists, and the
** map list, if it exists. ^_^
*/

void	localizedmaperrors(void)
{
	unsigned int	o;
	unsigned int	x;
	unsigned int	y;
	char			*c;

	o = g_iamerror.premaplines;
	if (g_iamerror.outofbounds[2])
	{
		geterrorlocation(g_iamerror.outofbounds, &x, &y);
		if (*(c = maplistdir(x, y)) != 'P')
			*c = 'X';
		ft_printf("Line: %u: %.*s"RED"%c"RESET"%s\n%s\n", y + 1 + o, x, \
		maplistdir(0, y), maplist(x, y), maplistdir(x + 1, y), outOfBounds);
	}
	if (g_iamerror.toomanyplayers[2])
	{
		geterrorlocation(g_iamerror.toomanyplayers, &x, &y);
		ft_printf("Line: %u: %.*s"RED"%c"RESET"%s\n%s\n", y + 1 + o, x, \
		maplistdir(0, y), maplist(x, y), maplistdir(x + 1, y), tooManyPlayers);
	}
}
