/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_bonus_original.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:23:56 by miki              #+#    #+#             */
/*   Updated: 2020/09/25 20:03:14 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** The easier-to-understand, pre-norminette version.
*/

int	get_texx(void)
{
	double x;
	double y;
	double perpwalldist;
	double wallx;
	double texx;
	int		sidewidth = g_skybox.texw / 4;

	x = g_raydata.raydirx;
	y = g_raydata.raydiry;

	if (y + x >= 0 && y - x < 0) //East
	{
		perpwalldist = 1 / x;
		wallx = perpwalldist * fabs(y);
		texx = (int)(wallx * (double)sidewidth);
		texx = sidewidth - (texx) - 1;
		texx /= 2;
		return (y >= 0 ? (sidewidth - (int)texx) : (int)texx);
	}
	else if (y + x > 0 && y - x >= 0) //South
	{
		perpwalldist = 1 / y;
		wallx = perpwalldist * fabs(x);
		texx = (int)(wallx * (double)sidewidth);
		texx = sidewidth - (texx) - 1;
		texx /= 2;
		return ((x <= 0 ? (sidewidth - (int)texx) : (int)texx) + sidewidth);
	}
	else if (y + x <= 0 && y - x > 0) //West
	{
		perpwalldist = 1 / x;
		wallx = perpwalldist * fabs(y);
		texx = (int)(wallx * (double)sidewidth);
		texx = sidewidth - (texx) - 1;
		texx /= 2;
		return ((y >= 0 ? (sidewidth - (int)texx) : (int)texx) + sidewidth * 2);
	}
	else if (y + x < 0 && y - x <= 0) //North
	{
		perpwalldist = 1 / y;
		wallx = perpwalldist * fabs(x);
		texx = (int)(wallx * (double)sidewidth);
		texx = sidewidth - (texx) - 1;
		texx /= 2;
		return ((x <= 0 ? (sidewidth - (int)texx) : (int)texx) + sidewidth * 3);
	}
	else
		return (-1);
}

int	drawskybox(int x, int pixel, t_raycasterdata *rdata)
{
	double			step;
	int				texx;
	int				texy;
	double			texpos;
	unsigned int 	xcolor;

	texx = get_texx();
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