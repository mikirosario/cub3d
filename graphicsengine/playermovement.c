/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 20:33:17 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Lode has another method for doing this, but by the time I read it I had
** already come up with my own matrix rotation function and became attached
** to my way of doing it. :P Anyway here is the Lode method, which also
** works, and below that my method, which just applies 3 degrees of rotation to
** the player/camera for every frame the l (anticlockwise) or r (clockwise)
** keys are depressed):
**
** Lode method clockwise (r) rotation
**	g_player.oldDirX = g_player.dirX;
**	g_player.dirX = g_player.dirX * cos(-g_player.rotSpeed) - g_player.dirY * sin(-g_player.rotSpeed);
**	g_player.dirY = g_player.oldDirX * sin(-g_player.rotSpeed) + g_player.dirY * cos(-g_player.rotSpeed);
**	g_player.oldPlaneX = g_player.planeX;
**	g_player.planeX = g_player.planeX * cos(-g_player.rotSpeed) - g_player.planeY * sin(-g_player.rotSpeed);
**	g_player.planeY = g_player.oldPlaneX * sin(-g_player.rotSpeed) + g_player.planeY * cos(-g_player.rotSpeed);
**
** Lode method anticlockwise rotation (l)
**	g_player.oldDirX = g_player.dirX;
**	g_player.dirX = g_player.dirX * cos(g_player.rotSpeed) - g_player.dirY * sin(g_player.rotSpeed);
**	g_player.dirY = g_player.oldDirX * sin(g_player.rotSpeed) + g_player.dirY * cos(g_player.rotSpeed);
**	g_player.oldPlaneX = g_player.planeX;
**	g_player.planeX = g_player.planeX * cos(g_player.rotSpeed) - g_player.planeY * sin(g_player.rotSpeed);
**	g_player.planeY = g_player.oldPlaneX * sin(g_player.rotSpeed) + g_player.planeY * cos(g_player.rotSpeed);
*/

void	rlrotate(void)
{
	if (g_keyData.r)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW - 100, 0, 0xFF00000, "CLOCKWISE");
		ft_rotate_2d(g_player.dirX, g_player.dirY, -3, 6, (double *)(&g_player.newDirXY));
		g_player.dirX = g_player.newDirXY[0];
		g_player.dirY = g_player.newDirXY[1];
		ft_rotate_2d(g_player.planeX, g_player.planeY, -3, 6, (double *)(&g_player.newDirXY));
		g_player.planeX = g_player.newDirXY[0];
		g_player.planeY = g_player.newDirXY[1];
	}
	if (g_keyData.l)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "COUNTERCLOCKWISE");
		ft_rotate_2d(g_player.dirX, g_player.dirY, 3, 6, (double *)(&g_player.newDirXY));
		g_player.dirX = g_player.newDirXY[0];
		g_player.dirY = g_player.newDirXY[1];
		ft_rotate_2d(g_player.planeX, g_player.planeY, 3, 6, (double *)(&g_player.newDirXY));
		g_player.planeX = g_player.newDirXY[0];
		g_player.planeY = g_player.newDirXY[1];
	}
}

void	adstrafe(void)
{
	if (g_keyData.a)
	{
		ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 10, g_config.screenH / 2, 0xFF00000, "LEFT");
		//if (maplist((int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
		if (g_config.map[(int)g_player.posY][(int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed)] == '0')
			g_player.posX += g_player.newDirXY[0] * g_player.moveSpeed;
		//if (maplist((int)g_player.posX, (int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
		if (g_config.map[(int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)][(int)g_player.posX] == '0')
			g_player.posY += g_player.newDirXY[1] * g_player.moveSpeed;
	}
	if (g_keyData.d)
	{
		ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW - 64, g_config.screenH / 2, 0xFF00000, "RIGHT");
		//if (maplist((int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
		if (g_config.map[(int)g_player.posY][(int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed)] == '0')
			g_player.posX -= g_player.newDirXY[0] * g_player.moveSpeed;
		//if (maplist((int)g_player.posX, (int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
		if (g_config.map[(int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)][(int)g_player.posX] == '0')
			g_player.posY -= g_player.newDirXY[1] * g_player.moveSpeed;
	}
}

void	wsupdown(void)
{
	if (g_keyData.w)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 5, 0xFF00000, "UP");
		//if ((maplist((int)(g_player.posX + g_player.dirX * g_player.moveSpeed), (int)g_player.posY)) == '0')
		if (g_config.map[(int)g_player.posY][(int)(g_player.posX + g_player.dirX * g_player.moveSpeed)] == '0')
			g_player.posX += g_player.dirX * g_player.moveSpeed;
		//if ((maplist((int)g_player.posX, (int)(g_player.posY + g_player.dirY * g_player.moveSpeed))) == '0')
		if (g_config.map[(int)(g_player.posY + g_player.dirY * g_player.moveSpeed)][(int)g_player.posX] == '0')
			g_player.posY += g_player.dirY * g_player.moveSpeed;
	}
	if (g_keyData.s)
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, g_config.screenH - 24, 0xFF00000, "DOWN");
		//if ((maplist((int)(g_player.posX - g_player.dirX * g_player.moveSpeed), (int)(g_player.posY)) == '0'))
		if (g_config.map[(int)(g_player.posY)][(int)(g_player.posX - g_player.dirX * g_player.moveSpeed)] == '0')
			g_player.posX -= g_player.dirX * g_player.moveSpeed;
		//if ((maplist((int)g_player.posX, (int)(g_player.posY - g_player.dirY * g_player.moveSpeed))) == '0')
		if (g_config.map[(int)(g_player.posY - g_player.dirY * g_player.moveSpeed)][(int)g_player.posX] == '0')
			g_player.posY -= g_player.dirY * g_player.moveSpeed;
	}
	
}

/*
** We check the wasd keys first, starting with w and s, controlling up and down
** movement, then a and d, controlling left and right strafing. Then we check
** the left and right arrow keys (l and r) controlling left and right rotation.
** If any of these keys are being depressed, we change the player's position
** or orientation along the corresponding vectors. Note these key presses or
** releases will always take effect in the next frame.
*/

void	readmovementkeys(void)
{
	wsupdown();
	adstrafe();
	rlrotate();
}