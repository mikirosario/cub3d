/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/14 20:30:08 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	readwasdkeys(void)
{
	
	if (g_keyData.w)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW/2, 24, 0xFF00000, "UP");
		if ((maplist((int)(g_player.posX + g_player.dirX * g_player.moveSpeed), (int)g_player.posY)) == '0')
			g_player.posX += g_player.dirX * g_player.moveSpeed;
		if ((maplist((int)g_player.posX, (int)(g_player.posY + g_player.dirY * g_player.moveSpeed))) == '0')
			g_player.posY += g_player.dirY * g_player.moveSpeed;
	}
	if (g_keyData.s)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW/2, g_config.screenH - 24, 0xFF00000, "DOWN");
		if ((maplist((int)(g_player.posX - g_player.dirX * g_player.moveSpeed), (int)(g_player.posY)) == '0'))
			g_player.posX -= g_player.dirX * g_player.moveSpeed;
		if ((maplist((int)g_player.posX, (int)(g_player.posY - g_player.dirY * g_player.moveSpeed))) == '0')
			g_player.posY -= g_player.dirY * g_player.moveSpeed;
	}
	if (g_keyData.a)
	{
		ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 10, g_config.screenH/2, 0xFF00000, "LEFT");
		if (maplist((int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
			g_player.posX += g_player.newDirXY[0] * g_player.moveSpeed;
		if (maplist((int)g_player.posX, (int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
			g_player.posY += g_player.newDirXY[1] * g_player.moveSpeed;
	}
	if (g_keyData.d)
	{
		ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW - 64, g_config.screenH/2, 0xFF00000, "RIGHT");
		if (maplist((int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
			g_player.posX -= g_player.newDirXY[0] * g_player.moveSpeed;
		if (maplist((int)g_player.posX, (int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
			g_player.posY -= g_player.newDirXY[1] * g_player.moveSpeed;
	}
}

void	readmovementkeys(void)
{
	readwasdkeys();
		//clockwise rotation
	if (g_keyData.r)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW - 100, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

		//mi método
		ft_rotate_2d(g_player.dirX, g_player.dirY, -3, 6, (double *)(&g_player.newDirXY));
		g_player.dirX = g_player.newDirXY[0];
		g_player.dirY = g_player.newDirXY[1];
		ft_rotate_2d(g_player.planeX, g_player.planeY, -3, 6, (double *)(&g_player.newDirXY));
		g_player.planeX = g_player.newDirXY[0];
		g_player.planeY = g_player.newDirXY[1];
		
		//método Lode
		/*g_player.oldDirX = g_player.dirX;
		g_player.dirX = g_player.dirX * cos(-g_player.rotSpeed) - g_player.dirY * sin(-g_player.rotSpeed);
		g_player.dirY = g_player.oldDirX * sin(-g_player.rotSpeed) + g_player.dirY * cos(-g_player.rotSpeed);
		g_player.oldPlaneX = g_player.planeX;
		g_player.planeX = g_player.planeX * cos(-g_player.rotSpeed) - g_player.planeY * sin(-g_player.rotSpeed);
		g_player.planeY = g_player.oldPlaneX * sin(-g_player.rotSpeed) + g_player.planeY * cos(-g_player.rotSpeed);*/
	}
	//anticlockwise rotation
	if (g_keyData.l)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "COUNTERCLOCKWISE"); //CHIVATO

		//mi método
		ft_rotate_2d(g_player.dirX, g_player.dirY, 3, 6, (double *)(&g_player.newDirXY));
		g_player.dirX = g_player.newDirXY[0];
		g_player.dirY = g_player.newDirXY[1];
		ft_rotate_2d(g_player.planeX, g_player.planeY, 3, 6, (double *)(&g_player.newDirXY));
		g_player.planeX = g_player.newDirXY[0];
		g_player.planeY = g_player.newDirXY[1];
		
		//método Lode
		/*g_player.oldDirX = g_player.dirX;
		g_player.dirX = g_player.dirX * cos(g_player.rotSpeed) - g_player.dirY * sin(g_player.rotSpeed);
		g_player.dirY = g_player.oldDirX * sin(g_player.rotSpeed) + g_player.dirY * cos(g_player.rotSpeed);
		g_player.oldPlaneX = g_player.planeX;
		g_player.planeX = g_player.planeX * cos(g_player.rotSpeed) - g_player.planeY * sin(g_player.rotSpeed);
		g_player.planeY = g_player.oldPlaneX * sin(g_player.rotSpeed) + g_player.planeY * cos(g_player.rotSpeed);*/
	}
}