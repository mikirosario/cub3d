/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:13:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 04:27:08 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** The hit variable will be initialized to 0 here, and will later be used to
** record a wall hit. Until a wall is hit, we'll keep moving the ray from
** side to side, where walls can be. Depending on the ray's orientation, it
** will move so many walls along one axis for every wall it hits on the other.
** When a wall is hit, we exit.
*/

void	sidetoside(void)
{
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
		if (g_config.map[g_raydata.mapy][g_raydata.mapx] == '1')
			g_raydata.hit = 1;
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

void	stepandinitialside(void)
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
** The ray starts at the player's position. Here we determine in which
** direction or orientation it is travelling on the map.
**
** For a given orientation (depending on which way it's pointing), a ray will
** always have a set distance from the edge of one wall to the edge of the
** next. We call top and bottom walls y-facing walls and left or right walls
** x-facing walls. The distance from the edge of a wall to the edge of another
** x-facing or y-facing wall is a function of the ray's orientation, that is,
** how much far it travels along one axis versus how far it travels along the
** other. We just need to know whether the next wall it hits will be x-facing
** or y-facing so we know which to paint on screen, and its distance from the
** player so we know how many pixels tall to paint it.
**
** First we will determine these distances, taking the ray's orientation,
** which will, of course, depend on the player's orientation. They will be used
** later by the DDA algorithm to trace the ray's path wall by wall across the
** map to determine where it will first hit a wall.
**
** We calculate the ray's position and direction. Then we determine which box
** of the map we are in (mapX and mapY). Then we calculate the distance the ray
** must travel to go from one x-facing side to the next x-facing side, or one
** y-facing side to the next y-facing side as a function of its orientation.
** Unless facing perfectly west, east, north or south, this will be a
** fractional number.
**
** Then we will call stepandinitialside.
*/

void	castray(int x)
{
	g_player.camerax = 2 * x / (double)g_config.screenw - 1;
	g_raydata.raydirx = g_player.dirx + g_player.planex * g_player.camerax;
	g_raydata.raydiry = g_player.diry + g_player.planey * g_player.camerax;
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
	stepandinitialside();
	sidetoside();
}
