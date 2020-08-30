/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:08:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/27 19:59:37 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;
extern t_imagedata *sprimg[10];

void	spritepathnotifications(void)
{
	int i;

	i = 2;
	if (g_config.sprtexnum)
	{
		ft_printf(GREEN"%s"RESET, SPRPATHS);
		while (i <= g_config.sprtexnum)
		{
			ft_printf(GREEN"\n%d ->"RESET" %s", i, (*sprimg[i]).texpath);
			i++;
		}
		write(1, "\n", 2);
	}
}

void	ceilingcolornotifications(void)
{
	ft_printf(GREEN"%s"RESET"%d, %d, %d", RGBC, g_config.crgb[0], \
	g_config.crgb[1], g_config.crgb[2]);
	ft_printf(GREEN"%s"RESET"%x\n", HEXC, g_framedata.xceilingcolor);
}

void	floorcolornotifications(void)
{
	ft_printf(GREEN"%s"RESET"%d, %d, %d", RGBF, g_config.frgb[0], \
	g_config.frgb[1], g_config.frgb[2]);
	ft_printf(GREEN"%s"RESET"%x\n", HEXF, g_framedata.xfloorcolor);
}

void	texturesizenotifications(void)
{
	int i;

	i = 2;
	if (g_config.texw && g_config.texh && !g_iamerror.orphansprites)
		ft_printf(GREEN"%s"RESET"\n%d x %d\n", WALLTEXSIZE, g_config.texw, \
		g_config.texh);
	if (g_config.sprtexnum && !g_iamerror.badsprsyn && \
	!g_iamerror.orphansprites)
	{
		ft_printf(GREEN"%s"RESET, SPRITETEXSIZES);
		while (i <= g_config.sprtexnum)
		{
			ft_printf(GREEN"\n%d ->"RESET" %d x %d", i, (*sprimg[i]).texw, \
			(*sprimg[i]).texh);
			i++;
		}
		write (1, "\n", 1);
	}
}

void	printnotifications(void)
{
	if (!g_iamerror.cubfilenotfound && !g_iamerror.weirdfd)
	{
		ft_printf(GREEN"%s"RESET"%d x %d\n", RES, g_config.screenw, \
		g_config.screenh);
		ft_printf(GREEN"%.14s"RESET"\n%s\n"GREEN"%.13s"RESET"\n%s\n" \
		GREEN"%.13s"RESET"\n%s\n"GREEN"%.13s"RESET"\n%s\n", WALLPATHS, \
		g_nowallimg.texpath, (WALLPATHS + 14), g_sowallimg.texpath, \
		(WALLPATHS + 27), g_wewallimg.texpath, (WALLPATHS + 40), \
		g_eawallimg.texpath);
        ft_printf(GREEN"%.11s"RESET"\n%s\n"GREEN"%.13s"RESET"\n%s\n", FCPATHS, \
        g_floorimg.texpath, (FCPATHS + 11), g_ceilingimg.texpath);
		if (g_config.spritenum)
			spritepathnotifications();
		if (!g_iamerror.texpathfail)
			texturesizenotifications();
	}
	return ;
}
