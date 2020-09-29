/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:23:56 by miki              #+#    #+#             */
/*   Updated: 2020/09/27 11:57:28 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

/*
** To make this function do its magic we must pass as walldir the raydir for
** the wall that the ray will hit. For example, if the ray will hit the eastern
** or western walls of the skybox, you pass raydirx as walldir, because these
** walls are on the x axis. If the ray will hit the northern or southern walls
** of the skybox, you pass raydiry as walldir, because these walls are on the y
** axis. We use this to determine the perpendicular wall distance to the wall
** from the player camera, per Lode.
**
** You pass the other raydir as angledir, which will be used to determine
** at what distance from the centre of the wall that ray will hit the wall.
**
** We'll then use this information to get a texture coordinate to which we can
** add multiples of sidewidth to move across the texture map. We can use this
** directly to get the first half of a wall texture, and subtract it from the
** width of a wall to get the second half of the wall texture.
**
** Bit convoluted, but it works.
*/

int	find_texx(double walldir, double angledir, t_raycasterdata *rdata)
{
	double	perpwalldist;
	double	wallx;
	double	texx;

	perpwalldist = 1 / walldir;
	wallx = perpwalldist * fabs(angledir);
	texx = (int)(wallx * (double)rdata->skyboxsidewidth);
	texx = rdata->skyboxsidewidth - (texx) - 1;
	texx /= 2;
	return (texx);
}

/*
** This function uses quantum ray information to determine whether your ray will
** hit the east, south, west or north walls (in that order). Depending on which
** wall you hit, it will send appropriate data to find_texx for that axis. For
** x axis hits (east or west) the x direction is sent as the wall direction and
** the y direction gives the location on the wall. For y axis hits (north or
** south) it's the opposite, the y direction is sent as the wall direction and
** the x direction gives the location on the wall.
**
** if (east)
** else if (south)
** else if (west)
** else if (north)
**
** We get back texx for the first half of the wall, which we return directly if
** the ray hit the first half of the wall, while if the ray hit the second half
** of the wall we return the width of the wall minus texx. For example, when
** facing east-northeast y will be negative (north is the negative y direction)
** so we don't do the subtraction, since that's the beginning of the east wall.
** If the ray is facing east-southeast, y will be positive and then we know we
** hit the second half of the wall, so we subtract texx from the wall width to
** get the right texture. We then multiply by a multiple of the width as
** appropriate to move across the east, south, west and north faces of the
** skybox, in that order (1 * width, 2 * width or 3 * width).
**
** Finally, if for whatever bizarre, inexplicable reason we don't fulfil any of
** these theoretically infallible conditions, we return -1 and the calling
** function will fill in any blank spots with red. I used this to debug when
** developing this, but left it in. ;)
*/

int	get_texx(t_raycasterdata *rdata)
{
	double	x;
	double	y;
	int		sw;

	sw = rdata->skyboxsidewidth;
	x = g_raydata.raydirx;
	y = g_raydata.raydiry;
	if (y + x >= 0 && y - x < 0)
		return (y >= 0 ? (sw - find_texx(g_raydata.raydirx, g_raydata.raydiry,
		rdata)) : find_texx(g_raydata.raydirx, g_raydata.raydiry, rdata));
	else if (y + x > 0 && y - x >= 0)
		return ((x <= 0 ? (sw - find_texx(g_raydata.raydiry, g_raydata.raydirx,
		rdata)) : find_texx(g_raydata.raydiry, g_raydata.raydirx, rdata)) + sw);
	else if (y + x <= 0 && y - x > 0)
		return ((y >= 0 ? (sw - find_texx(g_raydata.raydirx, g_raydata.raydiry,
		rdata)) : find_texx(g_raydata.raydirx, g_raydata.raydiry, rdata)) + sw
		* 2);
	else if (y + x < 0 && y - x <= 0)
		return ((x <= 0 ? (sw - find_texx(g_raydata.raydiry, g_raydata.raydirx,
		rdata)) : find_texx(g_raydata.raydiry, g_raydata.raydirx, rdata)) + sw
		* 3);
	else
		return (-1);
}

int	drawskybox(int x, int pixel, t_raycasterdata *rdata)
{
	double			step;
	int				texx;
	int				texy;
	double			texpos;
	unsigned int	xcolor;

	texx = get_texx(rdata);
	step = 1.0 * g_skybox.texh / g_config.screenh / 1.0;
	texpos = 0;
	while (pixel < (x + g_framedata.drawstart * g_config.screenw))
	{
		texy = (int)(texpos) & (g_skybox.texh - 1);
		if (texx >= 0)
			xcolor = g_skybox.tex_ptr[texx + texy * g_skybox.texw];
		else
			xcolor = 0x00FF0000;
		drawtobuffer_bonus(rdata->buf, pixel, xcolor);
		texpos += step;
		pixel += g_config.screenw;
	}
	return (pixel);
}
