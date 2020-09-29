/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:21:07 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

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
		ft_rotate_2d(g_player.dirx, g_player.diry, -3, g_player.newdirxy);
		g_player.dirx = g_player.newdirxy[0];
		g_player.diry = g_player.newdirxy[1];
		ft_rotate_2d(g_player.planex, g_player.planey, -3, g_player.newdirxy);
		g_player.planex = g_player.newdirxy[0];
		g_player.planey = g_player.newdirxy[1];
	}
	if (g_keydata.l)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, 3, g_player.newdirxy);
		g_player.dirx = g_player.newdirxy[0];
		g_player.diry = g_player.newdirxy[1];
		ft_rotate_2d(g_player.planex, g_player.planey, 3, g_player.newdirxy);
		g_player.planex = g_player.newdirxy[0];
		g_player.planey = g_player.newdirxy[1];
	}
}

/*
** These movement functions closely follow the Lode tutorial, even though they
** are a tad redundant. (In the bonus I reduced the code). One significant
** modification I do make is to add a bit of padding to the wall check, so
** you'll actually detect a wall slightly before you reach the very edge of it.
** This will prevent you from potentially being able to put the camera through
** the wall. People have been bugging me about that since the beginning. ;)
** See, I told you all I'd fix it before the evaluation. Sheesh. ;p
**
** Depending on whether we are gaining or losing number on our axis, for the
** check we'll want to add or subtract a bit. If we're gaining we want to add
** and if we're losing we want to subtract, so that we gain/lose even more,
** and 'see' the wall ahead of time, before we're at the very edge.
*/

void	adstrafe(void)
{
	double	newposxy[2];

	ft_rotate_2d(g_player.dirx, g_player.diry, 90, g_player.newdirxy);
	if (g_keydata.a)
	{
		newposxy[0] = g_player.posx + g_player.newdirxy[0] * g_player.movespeed;
		newposxy[1] = g_player.posy + g_player.newdirxy[1] * g_player.movespeed;
		if (g_config.map[(int)g_player.posy][(int)(newposxy[0] + \
		(newposxy[0] < g_player.posx ? -0.1 : 0.1))] == '0')
			g_player.posx = newposxy[0];
		if (g_config.map[(int)(newposxy[1] + \
		(newposxy[1] < g_player.posy ? -0.1 : 0.1))][(int)g_player.posx] == '0')
			g_player.posy = newposxy[1];
	}
	if (g_keydata.d)
	{
		newposxy[0] = g_player.posx - g_player.newdirxy[0] * g_player.movespeed;
		newposxy[1] = g_player.posy - g_player.newdirxy[1] * g_player.movespeed;
		if (g_config.map[(int)g_player.posy][(int)(newposxy[0] + \
		(newposxy[0] < g_player.posx ? -0.1 : 0.1))] == '0')
			g_player.posx = newposxy[0];
		if (g_config.map[(int)(newposxy[1] + \
		(newposxy[1] < g_player.posy ? -0.1 : 0.1))][(int)g_player.posx] == '0')
			g_player.posy = newposxy[1];
	}
}

void	wsupdown(void)
{
	double	newposxy[2];

	if (g_keydata.w)
	{
		newposxy[0] = g_player.posx + g_player.dirx * g_player.movespeed;
		newposxy[1] = g_player.posy + g_player.diry * g_player.movespeed;
		if (g_config.map[(int)g_player.posy][(int)(newposxy[0] + \
		(newposxy[0] < g_player.posx ? -0.1 : 0.1))] == '0')
			g_player.posx = newposxy[0];
		if (g_config.map[(int)(newposxy[1] + \
		(newposxy[1] < g_player.posy ? -0.1 : 0.1))][(int)g_player.posx] == '0')
			g_player.posy = newposxy[1];
	}
	if (g_keydata.s)
	{
		newposxy[0] = g_player.posx - g_player.dirx * g_player.movespeed;
		newposxy[1] = g_player.posy - g_player.diry * g_player.movespeed;
		if (g_config.map[(int)(g_player.posy)][(int)(newposxy[0] + \
		(newposxy[0] < g_player.posx ? -0.1 : 0.1))] == '0')
			g_player.posx = newposxy[0];
		if (g_config.map[(int)(newposxy[1] + \
		(newposxy[1] < g_player.posy ? -0.1 : 0.1))][(int)g_player.posx] == '0')
			g_player.posy = newposxy[1];
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
