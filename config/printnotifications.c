/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:08:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 18:16:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t g_iamerror;

void	ceilingcolornotifications(void)
{
	ft_printf(rgbC, g_config.crgb[0], g_config.crgb[1], g_config.crgb[2]);
	ft_printf(hexC, g_frameData.oceilingColor);
}

void	floorcolornotifications(void)
{
	ft_printf(rgbF, g_config.frgb[0], g_config.frgb[1], g_config.frgb[2]);
	ft_printf(hexF, g_frameData.ofloorColor);
}

void	texturesizenotifications(void)
{
	if (g_config.texW && g_config.texH)
		ft_printf(wallTexSize, g_config.texW, g_config.texH);
	if (g_config.spriteW && g_config.spriteH && g_config.spriteNum)
		ft_printf(spriteTexSize, g_config.spriteW, g_config.spriteH);
}

void	printnotifications(void)
{
	if (!g_iamerror.cubfilenotfound && !g_iamerror.weirdfd)
	{
		ft_printf(Res, g_config.screenW, g_config.screenH);
		ft_printf(wallPaths, nowallimg.texpath, sowallimg.texpath, \
		wewallimg.texpath, eawallimg.texpath);
		if (g_config.spriteNum)
			ft_printf(GREEN"Sprite Path: "RESET"\n%s\n", g_normiImg.texpath);
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
