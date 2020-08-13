/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculateframeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:42:02 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/12 18:38:33 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** 24 - 30: Calculate value of wallX (the x coordinate where wall was hit).
** 31 - 35: Calculate x coordinate on the texture.
** 36: How much to increase the texture coordinate per screen pixel.
** 37 - 38: Starting texture coordinate.
*/

void	walltexparams(void)
{
	if (g_rayData.side == 0)
		g_frameData.wallX = g_player.posY + \
		g_rayData.perpWallDist * g_rayData.rayDirY;
	else
		g_frameData.wallX = g_player.posX + \
		g_rayData.perpWallDist * g_rayData.rayDirX;
	g_frameData.wallX -= floor((g_frameData.wallX));
	g_frameData.texX = (int)(g_frameData.wallX * (double)g_config.texW);
	if (g_rayData.side == 0 && g_rayData.rayDirX > 0)
		g_frameData.texX = (g_config.texW) - (g_frameData.texX) - 1;
	if (g_rayData.side == 1 && g_rayData.rayDirY < 0)
		g_frameData.texX = (g_config.texW) - (g_frameData.texX) - 1;
	g_frameData.step = 1.0 * g_config.texH / g_frameData.lineHeight;
	g_frameData.texPos = (g_frameData.drawStart - g_config.screenH \
	/ 2 + g_frameData.lineHeight / 2) * g_frameData.step;
}

/*
** 49 - 54: Calculate distance projected on camera direction.
** 55 - 56: Calculate height of line to draw on screen.
** 57 - 63: Calculate lowest and highest pixel to fill in current line.
*/

void	walldrawparams(void)
{
	if (g_rayData.side == 0)
		g_rayData.perpWallDist = (g_rayData.mapX - g_player.posX + \
		(1 - g_rayData.stepX) / 2) / g_rayData.rayDirX;
	else
		g_rayData.perpWallDist = (g_rayData.mapY - g_player.posY + \
		(1 - g_rayData.stepY) / 2) / g_rayData.rayDirY;
	g_frameData.lineHeight = (int)(g_config.screenH * \
	g_config.wallMultiplier / g_rayData.perpWallDist);
	g_frameData.drawStart = -(g_frameData.lineHeight) \
	/ 2 + g_config.screenH / 2;
	if (g_frameData.drawStart < 0)
		g_frameData.drawStart = 0;
	g_frameData.drawEnd = g_frameData.lineHeight / 2 + g_config.screenH / 2;
	if (g_frameData.drawEnd >= g_config.screenH)
		g_frameData.drawEnd = g_config.screenH - 1;
}

/*
** This function will use mathemagics to calculate data needed so that we know
** which color to put into which pixel. Depending on how far away the wall is,
** and thus how small it appears from the player perspective, more or less of
** each vertical line will be taken up by wall. We calculate how much that is
** for a given line (value of x) in walldrawparams. If we get our color from a
** texture map, we furthermore calculate which pixel of the texture to start
** from and how many vertical texture pixels to jump for every screen pixel we
** paint.
**
** That is about as much as I know. xD I took this from the Lode tutorial and
** all I know is that the maths behind it all work, but maths have never been
** my forté so I honestly cannot explain them beyond saying... I trust Lode. xD
** In any case, we don't need the texparams if we aren't using textures to
** begin with (m != 2). We toggle between textured walls and untextured walls
** by pressing the m key.
*/

void	calculateframeline(void)
{
	walldrawparams();
	if (g_keyData.m != 2)
		walltexparams();
}
