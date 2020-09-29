/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castoneray_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:13:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:57:28 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

void	calculatedistance(void)
{
	if (g_raydata.side == 0)
	{
		g_raydata.perpwalldist = (g_raydata.mapx - g_player.posx + \
		(1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
	}
	else
	{
		g_raydata.perpwalldist = (g_raydata.mapy - g_player.posy + \
		(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
	}
}

/*
** The hit variable will be initialized to 0 here, and will later be used to
** record a wall hit. Until a wall is hit, we'll keep moving the ray from
** side to side, where walls can be. Depending on the ray's orientation, it
** will move so many walls along one axis for every wall it hits on the other.
** When a wall is hit, we exit.
*/

void	hitdetector(void)
{
	char	mapchr;

	g_raydata.hit = 0;
	while (!g_raydata.hit)
	{
		if (g_raydata.sidedistx < g_raydata.sidedisty)
		{
			g_raydata.sidedistx += g_raydata.deltadistx;
			g_raydata.mapx += g_raydata.stepx;
			g_raydata.side = 0;
		}
		else
		{
			g_raydata.sidedisty += g_raydata.deltadisty;
			g_raydata.mapy += g_raydata.stepy;
			g_raydata.side = 1;
		}
		if ((mapchr = g_config.map[g_raydata.mapy][g_raydata.mapx]) == '/' || \
		mapchr == 'v' || mapchr == 'O' || mapchr == '1')
		{
			g_raydata.hit = 1;
			calculatedistance();
		}
	}
}

/*
** Here the steps and initial side distance of the ray will be calculated. Step
** will determine whether we're moving left or right and up or down, which will
** depend on the value of the rayDir variable (if rayDirX is positive we are
** moving right, which we signify with stepX = 1, if negative we are moving
** left, which we signify with stepX = -1, if rayDirY is positive we are moving
** up, which we signify with stepY = 1, if negative we are moving down which we
** signify with stepY = -1).
**
** The side distance for the initial ray position is special because we can be
** anywhere in relation to the wall. For subsequent calculations of side
** distance, however, we know we will always move from wall edge to wall edge.
*/

void	stepandinitialside2(void)
{
	if (g_raydata.raydirx < 0)
	{
		g_raydata.stepx = -1;
		g_raydata.sidedistx = (g_player.posx - g_raydata.mapx) * \
		g_raydata.deltadistx;
	}
	else
	{
		g_raydata.stepx = 1;
		g_raydata.sidedistx = (g_raydata.mapx + 1.0 - g_player.posx) * \
		g_raydata.deltadistx;
	}
	if (g_raydata.raydiry < 0)
	{
		g_raydata.stepy = -1;
		g_raydata.sidedisty = (g_player.posy - g_raydata.mapy) * \
		g_raydata.deltadisty;
	}
	else
	{
		g_raydata.stepy = 1;
		g_raydata.sidedisty = (g_raydata.mapy + 1.0 - g_player.posy) * \
		g_raydata.deltadisty;
	}
}

/*
** Similar to the normal raycaster, except castoneray will only be called for
** camerax == 0, that is, the ray that comes from the centre of the player,
** crosses the camera plane in the middle and goes through the center of the
** screen.
**
** We are basically only interested in whether it hits a door or not and, if
** so, how far away that door is. We store that distance immediately in
** g_raydata.perpwalldist and can the use it to decide what to do with the door
** depending on any other flags (spacebar pressed, for example).
*/

void	castoneray(void)
{
	g_raydata.raydirx = g_player.dirx;
	g_raydata.raydiry = g_player.diry;
	g_raydata.mapx = (int)g_player.posx;
	g_raydata.mapy = (int)g_player.posy;
	if (g_raydata.raydiry == 0)
		g_raydata.deltadistx = 0;
	else if (g_raydata.raydirx == 0)
		g_raydata.deltadistx = 1;
	else
		g_raydata.deltadistx = fabs(1 / g_raydata.raydirx);
	if (g_raydata.raydirx == 0)
		g_raydata.deltadisty = 0;
	else if (g_raydata.raydiry == 0)
		g_raydata.deltadisty = 1;
	else
		g_raydata.deltadisty = fabs(1 / g_raydata.raydiry);
	stepandinitialside2();
	hitdetector();
}
