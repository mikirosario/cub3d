/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:10:33 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/09 16:20:49 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

extern t_error	g_iamerror;

/*
** If the mapchar represents a sprite, returns true. Otherwise, returns false.
*/

int		isspr(char mapchr)
{
	return ((mapchr >= '2' && mapchr <= '9') || mapchr == '-' || \
	mapchr == '|' ? 1 : 0);
}

/*
** This function will take the map left by the floodfill function, which fills
** all traversable spaces in the map with 'A' and/or 'T' characters until all
** spaces reachable by the player are filled or an out of bounds position is
** reached, and change all the 'A' and/or 'T' character to '0' so that the
** raycaster can read the map.
**
** The function has two modes, normal mode, which is launched by default, and
** 'error' mode. In normal mode filled characters are changed to '0'. In error
** mode, filled characters are changed to '.', to show the user where the
** floodfill checked before discovering the error in the map.
**
** To launch error mode, pass the function "error" as its only argument. To
** launch normal mode, pass it any other string (including an empty string).
*/

void	unfloodmap(char *flag)
{
	t_list	*mapptr;
	char	*mapchr;
	char	mode;
	int		i;
	int		d;

	mapptr = g_config.maplist;
	mode = 'p';
	if (!(ft_strncmp(flag, "error", 5)))
		mode = 'e';
	while (mapptr)
	{
		i = 0;
		while ((*(mapchr = (char *)(mapptr->content + i))))
		{
			if (*mapchr == 'T' || *mapchr == 'A')
			{
				if (mode == 'p')
				{
					d = 0;
					while (d < g_config.doornum && g_config.door[d]->dooraddr != mapchr)
						d++;
					if (d < g_config.doornum)
							*mapchr = g_config.door[d]->spritetype;
					else
						*mapchr = '0';
				}
				else
					*mapchr = '.';
			}
			i++;
		}
		mapptr = mapptr->next;
	}
}

/*
** These functions (floodright and floodleft) are auxiliary to the floodfill
** function. They are essentially identical and do a horizontal sweep of the
** line from the position they are passed, except floodright will check the line
** from the position to the right of the position it is passed and rightward,
** while floodleft will check the line from (and including) the position it is
** passed and leftward.
**
** Every traversable space found on the horizontal sweep that is contiguous to
** the space being checked is itself also checked against the spaces immediately
** above and below it on the vertical axis. For vertical axis checks the
** function will first verify that something exists in the map at the specified
** line, either because line->next exists for the line below or because y is
** greater than 0 for the line above. The function will then check to ensure
** that the length of the line below or above is at least equal to x. These
** checks MUST be successful before any memory is addressed or dereferenced,
** otherwise there would be a segmentation fault!
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
** If a wall is fond on the vertical axis, it is left alone and the function
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
** loodleft are also invalid map conditions, they are respectively handled
** within their function's while rather than as a while condition. The only
** while conditions are thus encountering a wall or a 'T' (already checked
** character).
*/

int		floodleft(unsigned int x, unsigned int y)
{
	t_list	*row;
	char	mapchr;

	while ((mapchr = maplist(x, y)) && mapchr != '1' && mapchr != 'T')
	{
		if (x > 0 && (mapchr == '0' || isspr(mapchr) || mapchr == 'A'))
		{
			if ((row = maplistmem(y))->next && ((maplistmem(y + 1))->len) >= x \
			&& (mapchr = maplist(x, y + 1)) && (mapchr == '0' || isspr(mapchr)))
				(*(maplistdir(x, y + 1)) = 'A');
			else if (!row->next || mapchr == ' ' || !mapchr)
				return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
			if (row != g_config.maplist && ((maplistmem(y - 1))->len) >= x && \
			(mapchr = maplist(x, y - 1)) && (mapchr == '0' || isspr(mapchr)))
				(*(maplistdir(x, y - 1)) = 'A');
			else if (row == g_config.maplist || mapchr == ' ' || !mapchr)
				return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
			(*(maplistdir(x, y)) = 'T');
		}
		else if (mapchr == ' ' || !x)
			return (recorderrorlocation(g_iamerror.outofbounds, \
			(mapchr == ' ' ? x + 1 : x), y, 0));
		x--;
	}
	return (1);
}

int		floodright(unsigned int x, unsigned int y)
{
	t_list	*row;
	char	mapchr;

	while ((mapchr = maplist(++x, y)) != '1' && mapchr != 'T')
	{
		if (mapchr == '0' || isspr(mapchr) || mapchr == 'A')
		{
			if ((row = maplistmem(y))->next && ((maplistmem(y + 1))->len) >= x \
			&& (mapchr = maplist(x, y + 1)) && (mapchr == '0' || isspr(mapchr)))
				(*(maplistdir(x, y + 1)) = 'A');
			else if (!row->next || mapchr == ' ' || !mapchr)
				return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
			if (row != g_config.maplist && ((maplistmem(y - 1))->len) >= x && \
			(mapchr = maplist(x, y - 1)) && (mapchr == '0' || isspr(mapchr)))
				(*(maplistdir(x, y - 1)) = 'A');
			else if (row == g_config.maplist || mapchr == ' ' || !mapchr)
				return (recorderrorlocation(g_iamerror.outofbounds, x, y, 0));
			(*(maplistdir(x, y)) = 'T');
		}
		else if (mapchr == ' ' || !mapchr)
			return (recorderrorlocation(g_iamerror.outofbounds, x - 1, y, 0));
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

	founda = '1';
	while (founda && (!(y = 0)))
	{
		founda = 0;
		while (y <= g_config.maph && (!(x = 0)))
		{
			g_iamerror.mapsweeps++;
			while ((mapchr = maplist(x, y)))
			{
				if (mapchr == 'A' && (founda = '1'))
					if (!(floodright(x, y)) || !(floodleft(x, y)))
						return (0);
				x++;
			}
			y++;
		}
	}
	unfloodmap("play");
	return (1);
}
