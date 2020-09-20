/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsmodes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:36:34 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/20 07:46:20 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
	if (g_framedata.phrase)
	{
		if (!rdata->phrasetimer.tv_sec)
			gettimeofday(&rdata->phrasetimer, NULL);
		else if ((msec_diff(&rdata->phrasetimer, NULL)) > 2000)
		{
			g_framedata.phrase = 0;
			reset_timer(&rdata->phrasetimer);
		}
		else if (g_framedata.phrase == 1)
		{
			mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
			g_config.screenw / 2, (g_config.screenh / 2) - 10, 0x0000ff00, "IT'S DANGEROUS TO GO ALONE");
			mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
			g_config.screenw / 2, (g_config.screenh / 2) + 10, 0x0000ff00, "TAKE THIS");
		}
		
	}
}
