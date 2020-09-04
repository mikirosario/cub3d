/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawceilingfloor_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 16:41:58 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/04 20:29:42 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_floor(unsigned int *buf, int x, int y)
{
	unsigned int	*texptr;

	texptr = g_floorimg.tex_ptr;
	g_framedata.xcolor = texptr[(g_xraydata.texy * g_config.texw) \
	+ g_xraydata.texx];
	if (g_keydata.m == 1)
		g_framedata.xcolor = (g_framedata.xcolor >> 1) & 8355711;
	if (g_framedata.invincibilityframes % 2)
		g_framedata.xcolor = g_framedata.xcolor >> 1 & 0x7F0000;
	buf[(y * g_config.screenw) + x] = g_framedata.xcolor;
}

void	draw_ceiling(unsigned int *buf, int x, int y)
{
	unsigned int	*texptr;

	texptr = g_ceilingimg.tex_ptr;
	g_framedata.xcolor = texptr[(g_xraydata.texy * g_config.texw) \
	+ g_xraydata.texx];
	if (g_keydata.m == 1)
		g_framedata.xcolor = (g_framedata.xcolor >> 1) & 8355711;
	if (g_framedata.invincibilityframes % 2)
		g_framedata.xcolor = g_framedata.xcolor >> 1 & 0x7F0000;
	buf[((g_config.screenh - y - 1) * g_config.screenw) + x] = \
	g_framedata.xcolor;
}

void	setpixelparams(void)
{
	g_xraydata.cellx = (int)g_xraydata.floorx;
	g_xraydata.celly = (int)g_xraydata.floory;
	g_xraydata.texx = (int)(g_config.texw * \
	(g_xraydata.floorx - g_xraydata.cellx)) & (g_config.texw - 1);
	g_xraydata.texy = (int)(g_config.texh * \
	(g_xraydata.floory - g_xraydata.celly)) & (g_config.texh - 1);
	g_xraydata.floorx += g_xraydata.floorstepx;
	g_xraydata.floory += g_xraydata.floorstepy;
}

void	setrowparams(int y)
{
	g_xraydata.raydirx0 = g_player.dirx - g_player.planex;
	g_xraydata.raydiry0 = g_player.diry - g_player.planey;
	g_xraydata.raydirx1 = g_player.dirx + g_player.planex;
	g_xraydata.raydiry1 = g_player.diry + g_player.planey;
	g_xraydata.p = y - g_config.screenh / 2;
	g_xraydata.posz = 0.5 * (double)g_config.screenh;
	g_xraydata.rowdistance = g_xraydata.posz / g_xraydata.p;
	g_xraydata.floorstepx = g_xraydata.rowdistance * \
	(g_xraydata.raydirx1 - g_xraydata.raydirx0) / g_config.screenw;
	g_xraydata.floorstepy = g_xraydata.rowdistance * \
	(g_xraydata.raydiry1 - g_xraydata.raydiry0) / g_config.screenw;
	g_xraydata.floorx = g_player.posx + g_xraydata.rowdistance * \
	g_xraydata.raydirx0;
	g_xraydata.floory = g_player.posy + g_xraydata.rowdistance * \
	g_xraydata.raydiry0;
}

void	cast_ceiling_floor(unsigned int *buf)
{
	int				y;
	int				x;

	y = 0;
	while (y < g_config.screenh)
	{
		setrowparams(y);
		x = 0;
		while (++x < g_config.screenw)
		{
			setpixelparams();
			draw_floor(buf, x, y);
			draw_ceiling(buf, x, y);
		}
		y++;
	}
}
