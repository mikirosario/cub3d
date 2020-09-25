/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:23:56 by miki              #+#    #+#             */
/*   Updated: 2020/09/25 16:05:37 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	findtexx(void)
{
	double x;
	double y;
	double perpwalldist;
	double wallx;
	double texx;
	int		sidewidth = g_skybox.texw / 4;

	x = g_raydata.raydirx;
	y = g_raydata.raydiry;
//perpwalldist = 1 / y;
//wallx = perpwalldist * x;

	if (y + x >= 0 && y - x < 0) //East
	{
		perpwalldist = 1 / x;
		wallx = perpwalldist * fabs(y);// < 0 ? y + 0.5 : y;
		//wallx = 1 - wallx;
		//wallx -= floor(wallx);
		texx = (int)(wallx * (double)sidewidth);
		//texx = 1 - texx;
		if (texx < 0.0)
			printf("\ntexx: %f > 0\n", texx);
		//if (y < 0)
		//	texx = sidewidth - texx + (sidewidth / 2);
		texx = sidewidth - (texx) - 1;
		texx /= 2;
		return (y >= 0 ? ((int)texx) + 64 : (int)texx);
	}
	/*
	else if (y + x > 0 && y - x >= 0) //South
	{
		perpwalldist = (1 - 1 / 2) / y;
		wallx = perpwalldist * x;
		texx = (int)(wallx * (double)sidewidth);
		//texx = ((sidewidth) - (texx) - 1);
		return (256 - (int)texx - 1);
	}
	else if (y + x < 0 && y - x > 0) //West
	{
		perpwalldist = 1 / x;
		wallx = perpwalldist * y;
		texx = (int)(wallx * (double)sidewidth);
		texx = ((sidewidth) - (texx) - 1);
		return ((int)texx + 256);
	}
	else if (y + x < 0 && y - x < 0) //North
	{
		perpwalldist = 1 / y;
		wallx = perpwalldist * x;
		texx = (int)(wallx * (double)sidewidth);
		texx = ((sidewidth) - (texx) - 1);
		return ((int)texx + 384);
	}*/

/*	if (g_raydata.raydiry <= 0 && g_raydata.raydirx > 0.5) //east-northeast	{
		texx = (double)((g_raydata.raydirx - 0.5) * sidewidth);
		//texx = sidewidth - texx - 1;
.
	}
	if (g_raydata.raydiry > 0 && g_raydata.raydirx > 0.5) //east-southeast
	{
		texx = 128 - texx - 1;
		//texx = (1 - g_raydata.raydirx + 0.5) * sidewidth;
		//	texx = (g_raydata.raydirx - 0.5) * sidewidth;
		//texx = sidewidth - texx - 1;
	}*/
	/*
	else if (g_raydata.raydiry >= 0 && g_raydata.raydirx < -0.5) //west-southwest
		texx = fabs((g_raydata.raydirx + 0.5)) * sidewidth + 256;
	else if (g_raydata.raydiry < 0 && g_raydata.raydirx < -0.5) //west-northwest
		texx = (1 - fabs(g_raydata.raydirx) + 0.5) * sidewidth + 256;
	else if (g_raydata.raydirx >= 0 && g_raydata.raydiry > 0.5) //south-southeast
		texx = (g_raydata.raydiry - 0.5) * sidewidth + 128;
	else if (g_raydata.raydirx < 0 && g_raydata.raydiry > 0.5) //south-southwest
		texx = 1 - (g_raydata.raydiry + 0.5) * sidewidth + 128;
	else if (g_raydata.raydirx <= 0 && g_raydata.raydiry < -0.5) //north-northwest
	{
		texx = fabs((g_raydata.raydiry + 0.5)) * sidewidth + 384;
		//texx = sidewidth - texx - 1;
	}
	else if (g_raydata.raydirx > 0 && g_raydata.raydiry < -0.5) //north-northeast
	{
		texx = (1 - fabs(g_raydata.raydiry) + 0.5) * sidewidth + 384;
		//texx = sidewidth - texx - 1;
	}*/
	else
	{
			return (-1);
	}
}

int	drawskybox(int x, int pixel, t_raycasterdata *rdata)
{
	double			step;
	int				texx;
	int				texy;
	double			texpos;
	unsigned int 	xcolor;
	//static int		facesize;
	//facesize = g_skybox.texw / 4;
	//texx = g_skybox.texw;
	//step = 1.0 * g_skybox.texw / (double)(g_config.screenh / 2);
	//texpos = g_skybox.texw;
	//texy = (int)(g_framedata.skyx * (double)(g_skybox.texh - 1));
	texx = findtexx();
	step = 1.0 * g_skybox.texh / g_config.screenh / 1.0;
	texpos = 0;
	//if (texy < 1)
	//	texy = 1;
	while (pixel < (x + g_framedata.drawstart * g_config.screenw))
	{
		//texx = (int)texpos;
		//texpos = texpos - step;
		texy = (int)(texpos) & (g_skybox.texh - 1);
		if (texx >= 0)
			xcolor = g_skybox.tex_ptr[texx + texy * g_skybox.texw];
		else
			xcolor = 0x00FF0000;
		//xcolor = g_skybox.tex_ptr[texx + texy * g_skybox.texw];
		drawtobuffer_bonus(rdata->buf, pixel, xcolor);
		texpos += step;
		pixel += g_config.screenw;
	}
	return (pixel);
}
