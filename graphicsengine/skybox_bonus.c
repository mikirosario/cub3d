/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:23:56 by miki              #+#    #+#             */
/*   Updated: 2020/09/24 06:04:10 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	findtexx(void)
{
	double texx;
	int		sidewidth = 128;

	if (g_raydata.raydiry <= 0 && g_raydata.raydirx > 0.5) //east-northeast
	{
		texx = (g_raydata.raydirx - 0.5) * sidewidth;
		//texx = sidewidth - texx - 1;
	}
	else if (g_raydata.raydiry > 0 && g_raydata.raydirx > 0.5) //east-southeast
	{
		texx = 1 - (g_raydata.raydirx + 0.5) * sidewidth;
		//texx = sidewidth - texx - 1;
	}
	else
	{
			return (-1);
	}
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
	return ((int)texx);
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
	texx = findtexx();
	step = 1.0 * 128 / g_config.screenh;
	texpos = 0;
	while (pixel < (x + g_framedata.drawstart * g_config.screenw))
	{
		texy = (int)texpos & (128 - 1);
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
