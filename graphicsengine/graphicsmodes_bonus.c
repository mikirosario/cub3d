/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsmodes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:36:34 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/21 23:35:13 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	displayspeech(t_raycasterdata *rdata)
{
	if (g_framedata.phrase)
	{
		if (!rdata->phrasetimer.tv_sec)
			gettimeofday(&rdata->phrasetimer, NULL);
		else if ((msec_diff(&rdata->phrasetimer, NULL)) > 5000)
		{
			g_framedata.phrase = 0;
			reset_timer(&rdata->phrasetimer);
		}
		yput_to_buffer(g_config.screenw / 2 - g_phrases.texw / 2, 
		g_config.screenh / 2 - g_phrases.texh / 2, rdata->buf, 
		g_phrases.animation[g_framedata.phrase - 1]);
	}	
}

void	displaygraphicsmode(t_raycasterdata *rdata)
{
	if (g_keydata.m == 0)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 10, 0x0000ff00, "Mode 0 Grafx");
	else if (g_keydata.m == 1)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 10, 0x0000ff00, "Mode 1 Grafx");
	else if (g_keydata.m == 2)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 10, 0x0000ff00, "Mode 2 Grafx");
	displayspeech(rdata);
}
