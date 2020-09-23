/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:23:56 by miki              #+#    #+#             */
/*   Updated: 2020/09/23 14:53:13 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	drawskybox(int x, int pixel, t_raycasterdata *rdata)
{
	double	step;
	int		texx;
	int		texy;
	double	texpos;
	unsigned int xcolor;
	int		invlineheight;

	invlineheight = g_config.screenh - g_framedata.lineheight - 1;

	texx = g_skybox.texw;
	//step = g_skybox.texw / (double)(g_skybox.texh / 2);
	step = g_skybox.texh / invlineheight;
	texpos = pixel - (g_config.screenh / 2 + invlineheight / 2) * step;
	texy = (int)(g_framedata.skyx * (double)(g_skybox.texh - 1));
	if (texy < 1)
		texy = 1;
	while (pixel < x + (g_framedata.drawstart * g_config.screenw))
	{
		texx = (int)texpos;
		texpos = texpos - step;
		xcolor = g_skybox.tex_ptr[(texy * g_skybox.texw) + texx];
		//xcolor = 0x00FF0000;
		drawtobuffer_bonus(rdata->buf, pixel, xcolor);
		pixel += g_config.screenw;
	}
	return (pixel);
}