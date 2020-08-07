/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:08:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/07 20:31:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t g_iamerror;

void	printnotifications(void)
{
	if (!g_iamerror.cubfilenotfound && !g_iamerror.weirdfd)
	{
		if (!g_iamerror.fcolorinvalid)
		{
			ft_printf(rgbF, g_config.frgb[0], g_config.frgb[1], g_config.frgb[2]);
			ft_printf(hexF,	g_frameData.ofloorColor);
		}
		else
			ft_printf(defaultF);
		if (!g_iamerror.ccolorinvalid)
		{
			ft_printf(rgbC, g_config.crgb[0], g_config.crgb[1], g_config.crgb[2]);
			ft_printf(hexC,	g_frameData.oceilingColor);
		}
		else
			ft_printf(defaultC);
	}
	if (g_iamerror.mapchecked)
		ft_printf(mapHeight, g_config.mapH);
	if (!g_iamerror.texpathfail)
	{
		ft_printf(wallTexSize, g_config.texW, g_config.texH);
		if (g_normiImg.mlx_img)
			ft_printf(spriteTexSize, g_config.spriteW, g_config.spriteH);
	}
	return ;
}
