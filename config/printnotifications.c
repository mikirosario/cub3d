/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:08:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:19:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error g_iamerror;

void	ceilingcolornotifications(void)
{
	ft_printf(rgbC, g_config.crgb[0], g_config.crgb[1], g_config.crgb[2]);
	ft_printf(hexC, g_framedata.xceilingcolor);
}

void	floorcolornotifications(void)
{
	ft_printf(rgbF, g_config.frgb[0], g_config.frgb[1], g_config.frgb[2]);
	ft_printf(hexF, g_framedata.xfloorcolor);
}

void	texturesizenotifications(void)
{
	if (g_config.texw && g_config.texh)
		ft_printf(wallTexSize, g_config.texw, g_config.texh);
	if (g_config.spritew && g_config.spriteh && g_config.spritenum)
		ft_printf(spriteTexSize, g_config.spritew, g_config.spriteh);
}

void	printnotifications(void)
{
	if (!g_iamerror.cubfilenotfound && !g_iamerror.weirdfd)
	{
		ft_printf(Res, g_config.screenw, g_config.screenh);
		ft_printf(wallPaths, g_nowallimg.texpath, g_sowallimg.texpath, \
		g_wewallimg.texpath, g_eawallimg.texpath);
		if (g_config.spritenum)
			ft_printf(GREEN"Sprite Path: "RESET"\n%s\n", g_sprt2img.texpath);
		if (!g_iamerror.texpathfail)
			texturesizenotifications();
		if (!g_iamerror.fcolorinvalid)
			floorcolornotifications();
		else
			ft_printf(defaultF);
		if (!g_iamerror.ccolorinvalid)
			ceilingcolornotifications();
		else
			ft_printf(defaultC);
	}
	return ;
}
