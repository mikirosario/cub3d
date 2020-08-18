/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:13:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/18 15:51:23 by mrosario         ###   ########.fr       */
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
	g_rayData.hit = 0;
	while (!g_rayData.hit)
	{
		if (g_rayData.sideDistX < g_rayData.sideDistY)
		{
			g_rayData.sideDistX += g_rayData.deltaDistX;
			g_rayData.mapX += g_rayData.stepX;
			g_rayData.side = 0;
		}
		else
		{
			g_rayData.sideDistY += g_rayData.deltaDistY;
			g_rayData.mapY += g_rayData.stepY;
			g_rayData.side = 1;
		}
		//if (maplist(g_rayData.mapX, g_rayData.mapY) == '1')
		if(g_config.map[g_rayData.mapY][g_rayData.mapX] == '1')
			g_rayData.hit = 1;
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
	if (g_rayData.rayDirX < 0)
	{
		g_rayData.stepX = -1;
		g_rayData.sideDistX = (g_player.posX - g_rayData.mapX) * \
		g_rayData.deltaDistX;
	}
	else
	{
		g_rayData.stepX = 1;
		g_rayData.sideDistX = (g_rayData.mapX + 1.0 - g_player.posX) * \
		g_rayData.deltaDistX;
	}
	if (g_rayData.rayDirY < 0)
	{
		g_rayData.stepY = -1;
		g_rayData.sideDistY = (g_player.posY - g_rayData.mapY) * \
		g_rayData.deltaDistY;
	}
	else
	{
		g_rayData.stepY = 1;
		g_rayData.sideDistY = (g_rayData.mapY + 1.0 - g_player.posY) * \
		g_rayData.deltaDistY;
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
	g_player.cameraX = 2 * x / (double)g_config.screenW - 1;
	g_rayData.rayDirX = g_player.dirX + g_player.planeX * g_player.cameraX;
	g_rayData.rayDirY = g_player.dirY + g_player.planeY * g_player.cameraX;
	g_rayData.mapX = (int)g_player.posX;
	g_rayData.mapY = (int)g_player.posY;
	if (g_rayData.rayDirY == 0)
		g_rayData.deltaDistX = 0;
	else if (g_rayData.rayDirX == 0)
		g_rayData.deltaDistX = 1;
	else
		g_rayData.deltaDistX = fabs(1 / g_rayData.rayDirX);
	if (g_rayData.rayDirX == 0)
		g_rayData.deltaDistY = 0;
	else if (g_rayData.rayDirY == 0)
		g_rayData.deltaDistY = 1;
	else
		g_rayData.deltaDistY = fabs(1 / g_rayData.rayDirY);
	stepandinitialside();
	sidetoside();
}
