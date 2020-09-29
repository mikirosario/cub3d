/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playercounter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:15:39 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:22:00 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d_bonus.h"

/*
** This function assigns the player's starting position and configures the
** associated initial data set - player position (posx, posy), relative camera
** plane position and orientation (planeX, planeY), player orientation (dirX,
** dirY).
**
** Initial player position is simply the location where the player was found
** in map, offset by 0.5 in both axes to bring the player to the centre of the
** square. The rest of the data will depend on initial player orientation,
** which is encoded in the letter representing the player character, where N
** is for north facing, S is for south facing, E is for east facing, and W is
** for west facing. Each orientation has its own set of starting data.
**
** Finally, after the starting position data is set, the character in the map
** is changed to A. This will tell the floodfill function, which will be used
** subsequently to check whether the player is within an area bounded by walls
** or not, that this spot needs to be checked.
**
** As for why this function looks like an it was run over by a car, there is
** is a simple answer for that. Norminette made me do it. This is a 42 school
** project, and we are limited to functions of no more than 25 lines. I had to
** mutilate this function to the form you see here to get it to fit. The 'real'
** clean function it is based off of is very straightforward and looks like
** this (^_^):
**
** void		configureplayer(unsigned int x, unsigned int y, char *playerchar)
** {
**	g_player.posx = (double)x + 0.5;
**	g_player.posy = (double)y + 0.5;
**	if (*playerchar == 'N' || *playerchar == 'n')
**	{
**		g_player.dirx = (double)0;
**		g_player.diry = (double)-1;
**		g_player.planex = (double)0.66;
**		g_player.planey = (double)0;
**	}
**	else if (*playerchar == 'S' || *playerchar == 's')
**	{
**		g_player.dirx = (double)0;
**		g_player.diry = (double)1;
**		g_player.planex = (double)-0.66;
**		g_player.planey = (double)0;
**	}
**	else if (*playerchar == 'E' || *playerchar == 'e')
**	{
**		g_player.dirx = (double)1;
**		g_player.diry = (double)0;
**		g_player.planex = (double)0;
**		g_player.planey = (double)0.66;
**	}
**	else if (*playerchar == 'W' || *playerchar == 'w')
**	{
**		g_player.dirx = (double)-1;
**		g_player.diry = (double)0;
**		g_player.planex = (double)0;
**		g_player.planey = (double)-0.66;
**	}
**	*playerchar = 'A';
** }
*/

void	orientplayer(double dirx, double diry, double planex, double planey)
{
	g_player.dirx = dirx;
	g_player.diry = diry;
	g_player.planex = planex;
	g_player.planey = planey;
}

void	configureplayer(unsigned int x, unsigned int y, char *playerchar)
{
	g_player.posx = (double)x + 0.5;
	g_player.posy = (double)y + 0.5;
	if (*playerchar == 'N' || *playerchar == 'n')
		orientplayer(0, -1, 0.66, 0);
	else if (*playerchar == 'S' || *playerchar == 's')
		orientplayer(0, 1, -0.66, 0);
	else if (*playerchar == 'E' || *playerchar == 'e')
		orientplayer(1, 0, 0, 0.66);
	else if (*playerchar == 'W' || *playerchar == 'w')
		orientplayer(-1, 0, 0, -0.66);
	*playerchar = 'A';
}

char	playercounter(int x, int y, char foundplayer)
{
	if (foundplayer > 1)
		return (toomanyplayers(x, y));
	else
		configureplayer(x, y, maplistdir(x, y));
	return (1);
}
