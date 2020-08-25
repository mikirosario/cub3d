/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsmodes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:36:34 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/25 19:39:25 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	displaygraphicsmode(void)
{
	if (g_keyData.m == 0)
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, \
		g_config.screenW / 2, 0, 0x0000ff00, "Mode 0 Grafx");
	else if (g_keyData.m == 1)
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, \
		g_config.screenW / 2, 0, 0x0000ff00, "Mode 1 Grafx");
	else if (g_keyData.m == 2)
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, \
		g_config.screenW / 2, 0, 0x0000ff00, "Mode 2 Grafx");
}
