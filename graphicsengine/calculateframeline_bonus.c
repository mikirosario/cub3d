/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculateframeline_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:42:02 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/21 01:19:55 by mikiencolor      ###   ########.fr       */
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
	if (g_raydata.side == 0)
		g_framedata.wallx = g_player.posy + \
		g_raydata.perpwalldist * g_raydata.raydiry;
	else
		g_framedata.wallx = g_player.posx + \
		g_raydata.perpwalldist * g_raydata.raydirx;
	g_framedata.wallx -= floor((g_framedata.wallx));
	if (g_raydata.hit > 1)
		g_framedata.wallx -= (g_framedata.dooroffset);
	g_framedata.texx = (int)(g_framedata.wallx * (double)g_config.texw);
	if (g_raydata.side == 0 && g_raydata.raydirx > 0)
		g_framedata.texx = (g_config.texw) - (g_framedata.texx) - 1;
	if (g_raydata.side == 1 && g_raydata.raydiry < 0)
		g_framedata.texx = (g_config.texw) - (g_framedata.texx) - 1;
	g_framedata.step = 1.0 * g_config.texh / g_framedata.lineheight;
	g_framedata.texpos = (g_framedata.drawstart - g_config.screenh \
	/ 2 + g_framedata.lineheight / 2) * g_framedata.step;
}

/*
** 49 - 54: Calculate distance projected on camera direction.
** 55 - 56: Calculate height of line to draw on screen.
** 57 - 63: Calculate lowest and highest pixel to fill in current line.
**
** Note: If the ray hit a door instead of a wall (g_raydata == 1 or 2) then
** the special perpwalldist to the door is precalculated in doorcaster_bonus.c
** within the hordoorslide or verdoorslide functions, so does not need to be
** calculated here, which is why these cases aren't referenced.
*/

void	walldrawparams(void)
{
	if (g_raydata.hit == 1)
	{
		if (g_raydata.side == 0)
		{
			//if (g_raydata.hit > 1)
			//	g_raydata.perpwalldist = ((double)(g_raydata.mapx + (0.5 * g_raydata.stepx)) - g_player.posx + 
			//	(1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
			//else
				g_raydata.perpwalldist = (g_raydata.mapx - g_player.posx + \
				(1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
		}		
		else
		{
			//if (g_raydata.hit > 1)
			//	g_raydata.perpwalldist = ((double)(g_raydata.mapy + (0.5 * g_raydata.stepy)) - g_player.posy + 
			//	(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
			//else
				g_raydata.perpwalldist = (g_raydata.mapy - g_player.posy + \
				(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
		}
		if (g_config.map[g_raydata.mapy][g_raydata.mapx] == 'v')
			g_framedata.secretwallcompass++;
	}
	g_framedata.lineheight = (int)(g_config.screenh * \
	g_config.wallmultiplier / g_raydata.perpwalldist);
	g_framedata.drawstart = -(g_framedata.lineheight) \
	/ 2 + g_config.screenh / 2;
	if (g_framedata.drawstart < 0)
		g_framedata.drawstart = 0;
	g_framedata.drawend = g_framedata.lineheight / 2 + g_config.screenh / 2;
	if (g_framedata.drawend >= g_config.screenh)
		g_framedata.drawend = g_config.screenh - 1;
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
	if (g_keydata.m != 2)
		walltexparams();
}
