/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:10:33 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/07 15:04:54 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/cub3d_bonus.h"

extern t_error	g_iamerror;

void	makemaplistarray(t_list **maplistarray)
{
	unsigned int	i;

	i = 0;
	while (i <= g_config.maph + 1)
	{
		maplistarray[i] = maplistmem(i);
		i++;
	}
}

/*
** If the mapchar represents a sprite, returns true. Otherwise, returns false.
** In the bonus, for the purposes of floodfill, doors are treated as sprites.
** Sprites do not impede movement through the square they occupy, so doors to
** out of bounds locations are rejected. The playermovement function will still
** treat closed doors as collidable.
*/

int		isspr(char mapchr)
{
	return ((mapchr >= '2' && mapchr <= '9') || mapchr == '/' || \
	mapchr == 'v' ? 1 : 0);
}

/*
** Check map square transitability. If the squares above and below the passed
** square are either transitable, potentially transitable (pending their own
** check against their neighbours), or walls, the map square is transitable.
**
** If the map square neighbours a space ' ', a NULL (here considered as
** !mapchr) or the map edge (!x, !y or y > maph), or a line that is shorter
** than the map square's position, it is intransitable and the map is rejected.
*/

int		check_transitability(unsigned int x, unsigned int y, char mapchr, \
t_list **maplistarray)
{
	if ((y + 1 <= g_config.maph) && (maplistarray[y + 1])->len >= x \
	&& (mapchr = g_config.map[y + 1][x]) && (mapchr == '0' || isspr(mapchr)))
		g_config.map[y + 1][x] = 'A';
	else if (y + 1 > g_config.maph || (maplistarray[y + 1])->len < x || \
	mapchr == ' ' || !mapchr)
		return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
	if (y && (maplistarray[y - 1])->len >= x && \
	(mapchr = g_config.map[y - 1][x]) && (mapchr == '0' || isspr(mapchr)))
		g_config.map[y - 1][x] = 'A';
	else if (!y || (maplistarray[y - 1])->len < x || mapchr == ' ' || !mapchr)
		return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
	(g_config.map[y][x] = 'T');
	return (1);
}

/*
** This function (floodline) is auxiliary to the floodfill function. It
** essentially does a horizontal sweep of the line from the position it is
** passed, first from the right of the position and rightward (floodright),
** then from the left of (and including) the position and leftward (floodleft).
** This occurs in two consecutive whiles.
**
** Every traversable space found on the horizontal sweep that is contiguous to
** the space being checked is itself also checked against the spaces immediately
** above and below it on the vertical axis. For vertical axis checks the
** function will first verify that something exists in the map at the specified
** line, either because y + 1 is not greater than the map height or because y is
** greater than 0. Once certain that a line does exist above or below the
** character being checked, the function will then refer to the maplist to check
** that the length of that line is at least equal to x. These checks MUST be
** successful before any memory is addressed or dereferenced, otherwise there
** would be a segmentation fault!
**
** Here is a diagram (the starting position is A):
**
**					floodright
**					---->
**		0	0	1	0	0
**		^	^	^	^	^
**	<	0	0	A	0	0	>
**		v	v	v	v	v
**		1	0	0	0	1
**		<--------
**		floodleft
**
** If both of these vertically contiguous spaces are not out of bounds, the
** check passes and the space being checked is changed to a 'T' to mark it
** as valid, while if the contiguous spaces in the vertical axis (above and
** below it) are traversable, they are in turn marked 'A' signalling that they
** are reachable by the player and thus must themselves be checked on all axes.
** If a wall is found on the vertical axis, it is left alone and the function
** continues. If an out of bounds space is found on the vertical axis, the
** function terminates and the check fails and returns a 0 error signal.
**
**					floodright
**					---->
**		A	A	1	A	A
**		^	^	^	^	^
**	<	T	T	T	T	T	>
**		v	v	v	v	v
**		1	A	A	A	1
**		<--------
**		floodleft
**
** This algorithm will record the position on the map contiguous to the position
** that caused the error and FROM WHICH the error was detected.
**
** On the horizontal axis, if the out of bounds position is outside the map's
** addressable area (the traversable space being checked is at the boundary of
** the allocated memory), this will be the position being checked (mapchr),
** because mapchr is, of course, never addressed to unaddressable bits of
** memory. If the out of bounds position is inside the the map's addressable
** area (it is a ' ' or a NULL terminator), however, mapchr will be addressed
** to that position, and so it will be x - 1 in floodright and x + 1 in
** floodleft.
**
** On the vertical axis the positions above and below the character being
** checked aren't addressed by mapchr, so the position of mapchr is always
** recorded as the error position.
**
** NOTE that since the NULL terminator in floodright and the x == 0 position in
** floodleft are also invalid map conditions, they are respectively handled
** by ifs within their whiles that terminate the while by returning 0 for the
** whole function, rather than as a while condition merely terminating the
** while. The only while conditions are thus those that are not invalid map
** condition, such as encountering a wall or a 'T' (map square already checked
** and labelled traversable).
*/

int		floodline(unsigned int x, unsigned int y, t_list **maplistarray)
{
	char	mapchr;
	int		orgx;

	orgx = x;
	while ((mapchr = g_config.map[y][++x]) != '1' && mapchr != 'T')
	{
		if ((mapchr == '0' || isspr(mapchr) || mapchr == 'A') && \
		!check_transitability(x, y, mapchr, maplistarray))
			return (0);
		else if (mapchr == ' ' || !mapchr)
			return (recorderrorlocation(g_iamerror.outofbounds, x - 1, y, 0));
	}
	x = orgx;
	while ((mapchr = g_config.map[y][x]) && mapchr != '1' && mapchr != 'T')
	{
		if ((x > 0 && (mapchr == '0' || isspr(mapchr) || mapchr == 'A')) && \
		!check_transitability(x, y, mapchr, maplistarray))
			return (0);
		else if (mapchr == ' ' || !x)
			return (recorderrorlocation(g_iamerror.outofbounds, \
			(mapchr == ' ' ? x + 1 : x), y, 0));
			x--;
	}
	return (1);
}

/*
** The floodfill algorithm analyses each line in the map, first horizontally,
** then vertically, looking for traversable or out of bounds squares. The
** map_phase1 checks will delineate and parse the map for invalid characters.
** If it finds a single player, it will mark the player's position with an
** 'A'. This 'A' position will be the starting seed for the floodfill
** algorithm.
**
** Traversable spaces are '0' (floor), '2' (sprite), or 'A'. Walls are '1'.
** Out of bounds spaces are either ' ', '\0' or non-existent (outside
** the map's addressable memory space).
**
** For the floodfill, traversable spaces starting from the player location (the
** first 'A') are checked against all continguous spaces to the right and left
** until running into a wall or an out of bounds space. If an out of bounds
** spaces is reached, the function terminates and the check fails and returns a
** 0 error signal.
**
** The function will sweep through every line in the map looking for characters
** marked as 'A'. Upon finding such characters it will either successfully check
** them against their neighbours and mark them 'T' to validate them, or it will
** will find that they are contiguous with an out of bounds character or
** location and terminate, returning 0.
**
** If the program terminates because no more 'A' characters could be found, the
** test is successful and the player is safely within a bounded area; otherwise,
** the player is be able to reach an out of bounds location and the map is
** therefore invalid.
**
** When successful, the algorithm returns 1. When it fails, it returns 0, which
** signals the 'out of bounds' error.
*/

int		floodfill(void)
{
	char			mapchr;
	char			founda;
	unsigned int	x;
	unsigned int	y;
	t_list			*maplistarray[g_config.maph + 1];

	makemaplistarray(maplistarray);
	founda = 1;
	while (founda && (!(y = 0)) && !(--founda))
	{
		while (y <= g_config.maph && (!(x = 0)) && ++g_iamerror.mapsweeps)
		{
			while ((mapchr = g_config.map[y][x]))
			{
				if (mapchr == 'A' && (founda = 1))
					if (!floodline(x, y, maplistarray))
						return (0);
				x++;
			}
			y++;
		}
	}
	unfloodmap("play");
	mapspecialdoors();
	return (1);
}
