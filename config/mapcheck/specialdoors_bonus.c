/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialdoors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 01:42:34 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/24 20:37:18 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

/*
** Find a doorlist door by its x and y coordinates on the map. Helpful. :)
*/

t_spritedata	*finddoor(int x, int y)
{
	int i;

	i = 0;
	while (i < g_config.doornum)
	{
		if (g_config.door[i]->posx == x && g_config.door[i]->posy == y)
			return (g_config.door[i]);
		i++;
	}
	return (NULL);
}

/*
** Link a door to a teleportation destination by sending x and y coordinates of
** the door of origin and x and y coordinates of the destination as arguments.
** The door of origin may be any kind of door ('/' or '*') and the destination
** door must have the special type '*' for this to work, otherwise the function
** will do nothing. All linked doors will be turned into teleportation type
** doors ('*'), even if they were normal before.
*/

t_spritedata	*linkdoors(int originx, int originy, int destx, int desty)
{
	t_spritedata *origin;
	t_spritedata *destination;

	if (!(origin = finddoor(originx, originy)))
		return (NULL);
	if ((destination = finddoor(destx, desty)) && \
	destination->spritetype == '*')
	{
		origin->spritetype = '*';
		*(origin->dooraddr) = '*';
		origin->destaddr = destination;
		*(destination->dooraddr) = '0';
		return (origin);
	}
	return (NULL);
}

/*
** This function exists to point certain special doors to otherwise inaccessible
** map tiles and function as teleportation devices. You can pair them with any
** tiles marked as '*' in the map. Such tiles are flagged in the floodfill
** to be checked for boundedness and are also added to the door list, where
** their type ('*') and address are recorded. If you want a door on the map to
** function as a teleportation device, just point its teleport pointer to the
** address of any * stored in the door list.
**
** The teleport function will go through the door list to find the associated
** teleport destination, and then retrieve its coordinates and make them the
** player's coordinates.
**
** Just input the x and y coordinates of a normal door as the first two
** arguments and the x and y coordinates of a special '*' door as the last two
** coordinates into the linkdoors function and voilà, done. It returns a link
** to the origin door so you can change its texture and stuff. You can link back
** by calling the same function again with the doors reversed.
*/

void			mapspecialdoors(void)
{
	t_spritedata	*origin;

	if ((origin = linkdoors(44, 11, 29, 21)))
		origin->texture = g_portal.tex_ptr;
	if ((origin = linkdoors(29, 17, 33, 17)))
		origin->texture = g_portal.tex_ptr;
}
