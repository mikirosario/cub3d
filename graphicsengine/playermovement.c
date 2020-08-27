/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/27 17:44:01 by mrosario         ###   ########.fr       */
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
**	g_player.oldDirX = g_player.dirx;
**	g_player.dirx = g_player.dirx * cos(-g_player.rotspeed) - \
**	g_player.diry * sin(-g_player.rotspeed);
**	g_player.diry = g_player.oldDirX * sin(-g_player.rotspeed) + \
**	g_player.diry * cos(-g_player.rotspeed);
**	g_player.oldPlaneX = g_player.planex;
**	g_player.planex = g_player.planex * cos(-g_player.rotspeed) - \
**	g_player.planey * sin(-g_player.rotspeed);
**	g_player.planey = g_player.oldPlaneX * sin(-g_player.rotspeed) + \
**	g_player.planey * cos(-g_player.rotspeed);
**
** Lode method anticlockwise rotation (l)
**	g_player.oldDirX = g_player.dirx;
**	g_player.dirx = g_player.dirx * cos(g_player.rotspeed) - \
**	g_player.diry * sin(g_player.rotspeed);
**	g_player.diry = g_player.oldDirX * sin(g_player.rotspeed) + \
**	g_player.diry * cos(g_player.rotspeed);
**	g_player.oldPlaneX = g_player.planex;
**	g_player.planex = g_player.planex * cos(g_player.rotspeed) - \
**	g_player.planey * sin(g_player.rotspeed);
**	g_player.planey = g_player.oldPlaneX * sin(g_player.rotspeed) + \
**	g_player.planey * cos(g_player.rotspeed);
*/

void	rlrotate(void)
{
	if (g_keydata.r)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, -3, \
		(double *)(&g_player.newdirxy));
		g_player.dirx = g_player.newdirxy[0];
		g_player.diry = g_player.newdirxy[1];
		ft_rotate_2d(g_player.planex, g_player.planey, -3, \
		(double *)(&g_player.newdirxy));
		g_player.planex = g_player.newdirxy[0];
		g_player.planey = g_player.newdirxy[1];
	}
	if (g_keydata.l)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, 3, \
		(double *)(&g_player.newdirxy));
		g_player.dirx = g_player.newdirxy[0];
		g_player.diry = g_player.newdirxy[1];
		ft_rotate_2d(g_player.planex, g_player.planey, 3, \
		(double *)(&g_player.newdirxy));
		g_player.planex = g_player.newdirxy[0];
		g_player.planey = g_player.newdirxy[1];
	}
}

void	adstrafe(void)
{
	if (g_keydata.a)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, 90, \
		(double *)(&g_player.newdirxy));
		if (g_config.map[(int)g_player.posy][(int)(g_player.posx + \
		g_player.newdirxy[0] * g_player.movespeed)] == '0')
			g_player.posx += g_player.newdirxy[0] * g_player.movespeed;
		if (g_config.map[(int)(g_player.posy + g_player.newdirxy[1] * \
		g_player.movespeed)][(int)g_player.posx] == '0')
			g_player.posy += g_player.newdirxy[1] * g_player.movespeed;
	}
	if (g_keydata.d)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, 90, \
		(double *)(&g_player.newdirxy));
		if (g_config.map[(int)g_player.posy][(int)(g_player.posx - \
		g_player.newdirxy[0] * g_player.movespeed)] == '0')
			g_player.posx -= g_player.newdirxy[0] * g_player.movespeed;
		if (g_config.map[(int)(g_player.posy - g_player.newdirxy[1] * \
		g_player.movespeed)][(int)g_player.posx] == '0')
			g_player.posy -= g_player.newdirxy[1] * g_player.movespeed;
	}
}

void	wsupdown(void)
{
	if (g_keydata.w)
	{
		if (g_config.map[(int)g_player.posy][(int)(g_player.posx + \
		g_player.dirx * g_player.movespeed)] == '0')
			g_player.posx += g_player.dirx * g_player.movespeed;
		if (g_config.map[(int)(g_player.posy + g_player.diry * \
		g_player.movespeed)][(int)g_player.posx] == '0')
			g_player.posy += g_player.diry * g_player.movespeed;
	}
	if (g_keydata.s)
	{
		if (g_config.map[(int)(g_player.posy)][(int)(g_player.posx - \
		g_player.dirx * g_player.movespeed)] == '0')
			g_player.posx -= g_player.dirx * g_player.movespeed;
		if (g_config.map[(int)(g_player.posy - g_player.diry * \
		g_player.movespeed)][(int)g_player.posx] == '0')
			g_player.posy -= g_player.diry * g_player.movespeed;
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
