/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsmodes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:36:34 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/28 15:39:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	displaygraphicsmode(void)
{
	if (g_keydata.m == 0)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 0, 0x0000ff00, "Mode 0 Grafx");
	else if (g_keydata.m == 1)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 0, 0x0000ff00, "Mode 1 Grafx");
	else if (g_keydata.m == 2)
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		g_config.screenw / 2, 0, 0x0000ff00, "Mode 2 Grafx");
}