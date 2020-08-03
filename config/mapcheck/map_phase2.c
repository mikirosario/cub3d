/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:10:33 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/03 20:43:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

extern error_t	g_iamerror;

int		initialvaliditytest(unsigned int x, unsigned int y)
{
	char mapchar;

	if (!((mapListMem(y)->next)))
	{
		recorderrorlocation(g_iamerror.outofbounds, x, y);
		return (0);
	}
	if ((mapchar = mapList(x, y)) && mapchar != '1' && mapchar != 'T') //transitables contiguas
	{
		if (((mapListMem(y + 1))->len) >= (size_t)x && (mapchar = mapList(x, y + 1)) && (mapchar == '0' || mapchar == '2')) //primero strlen para asegurarnos de que la fila de arriba abarca lo suficiente para evitar segfault...
			(*(mapListDir(x, y + 1)) = 'A'); //marca como transitable provisional, pdte de comprobar verticales
		else if (mapchar == ' ' || !mapchar)
		{
			recorderrorlocation(g_iamerror.outofbounds, x, y);
			return (0);
		}
		if (((mapListMem(y - 1))->len) >= (size_t)x && (mapchar = mapList(x, y -1)) && (mapchar == '0' || mapchar == '2'))
			(*(mapListDir(x, y - 1)) = 'A'); //marca como transitable, pdte de comprobar verticales
		else if (mapchar == ' ' || !mapchar)
		{
			recorderrorlocation(g_iamerror.outofbounds, x, y);
			return (0);
		}
	}
	return (1);
}

/*
** The floodfill algorithm analyses each line in the map, first horizontally,
** then vertically, looking for traversable or out of bounds squares, starting
** from the player's position.
** 
** First the player's position is taken and an analysis is done on all
** contiguous squares via the initialvaliditytest function. This tests whether
** the player's starting position leads to any continguous out of bounds area.
** If it passes, the floodfill proper starts.
**
** For the floodfill, traversable spaces starting from the player location are
** checked against all continguous spaces to the right and left until running
** into a wall or an out of bounds space. If an out of bounds spaces is
** reached the function terminates and the check fails and returns a -1
** error signal.
**
** Every traversable space found on a horizontal sweep that is contiguous to
** the space being checked is also checked against the spaces immediately
** above and below it in the vertical axis. If the vertical spaces are not
** out of bounds, the check passes. Any map character within a contiguously
** secure horizontal line and with one secure character above and below it
** is changed to a 'T' to mark it as 'traversable'. Any valid spaces found
** above and below the spaces marked as 'T' are marked as 'A' to mark
** them as potentially valid.
**
** The function will sweep through every line in the map looking for characters
** marked as 'A'. Upon finding such such characters it will either successfully
** check them against their neighbours and mark them 'T' for 'traversable', or
** it will run into an out of bounds character and return a -1 and terminate.
**
** If the program terminates because no more 'A' characters could be found, the
** test is successful and the player must be within a bounded area, otherwise
** the player must be able to reach an out of bounds area and the map is
** therefore invalid.
**
** The algorithm will record the position on the map that caused the error.
** Note that this position may be a string's NULL terminator, in which case
** any function handling these positions, for example, to print out their
** location for the user as part of error handling, must keep that in mind
** and avoid any attempt to access the memory beyond the NULL.
**
** When successful, the algorithm returns 1. When it fails, it returns -1,
** which signals the 'out of bounds' error.
*/
int     floodfill(void)
{
	char			mapchar;
	char			founda;
	unsigned int	x;
	unsigned int	y;

	founda = '1';
	if (!(initialvaliditytest((unsigned int)floor(g_player.posX), (unsigned int)floor(g_player.posY))))
		return (0);
	while (founda)
	{    
		y = 0;
		founda = 0;
		while (y <= g_config.mapH)
		{
			g_iamerror.mapsweeps++,
			x = 0;
			while ((mapchar = mapList(x, y)))
			{
				if (mapchar == 'A')
				{
					if (!founda)
						founda = '1';
					if (!(floodRight(x, y)) || !(floodLeft(x, y)))
						return (0);
				}
				x++;
			}
			y++;
		}
	}
printmap();
unfloodMap("play");
	return (1);
}
