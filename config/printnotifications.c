/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:08:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/27 19:59:37 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error g_iamerror;

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
	if (g_config.texw && g_config.texh)
		ft_printf(GREEN"%s"RESET"\n%d x %d\n", WALLTEXSIZE, g_config.texw, \
		g_config.texh);
	if (g_config.spritew && g_config.spriteh && g_config.spritenum)
		ft_printf(GREEN"%s"RESET"\n%d x %d\n", SPRITETEXSIZE, \
		g_config.spritew, g_config.spriteh);
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
		if (g_config.spritenum)
			ft_printf(GREEN"%s"RESET"\n%s\n", SPRPATH, g_sprt2img.texpath);
		if (!g_iamerror.texpathfail)
			texturesizenotifications();
		if (!g_iamerror.fcolorinvalid)
			floorcolornotifications();
		else
			ft_printf(YELLOW"%s"RESET, DEFAULTF);
		if (!g_iamerror.ccolorinvalid)
			ceilingcolornotifications();
		else
			ft_printf(YELLOW"%s"RESET, DEFAULTC);
	}
	return ;
}
