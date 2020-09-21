/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/21 20:13:50 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function detects sprite collisions. The collision circle will have a
** diameter of half of a map box, centred on the sprite. It's designed to work
** with the default movement speed parameters so don't be surprised if raising
** them too much gives you quantum teleportation powers that break the game. ;p
**
** If the player tries to move on any axis, the new position of the player
** after that movement will be passed to this function.
**
** Before we validate that movement, we will make sure that the player's
** position does not fall within the hit circle of any nearby sprite
** (in the closesprite array) as detected by the getdistance function in
** drawsprite. (See that function's description for more details).
**
** Closesprite tracks all sprites within 0.33 of the player location every
** frame. We know that at this distance, in the most tightly packed arrangement
** this will never be more than 6 circles, because Joseph Louise Lagrange
** proved it in 1773, so we only have to track up to six nearby sprites per
** frame. Thanks, Joe! ^_^
**
** We return 1 if a collision was detected and 0 if no collision was detected.
*/

int		sprcollide(double y, double x)
{
	int i;
	int	sprnum;

	i = 0;
	while (i < 6)
		if ((sprnum = g_framedata.closesprite[i++]) >= 0)
			if ((pow(x - g_config.sprt[sprnum]->posx, 2) + \
			pow(y - g_config.sprt[sprnum]->posy, 2)) <= 0.25)
				return (1);
	return (0);
}

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
	if (g_keydata.r || g_keydata.mousedragr)
	{
		ft_rotate_2d(g_player.dirx, g_player.diry, -3, g_player.newdirxy);
		g_player.dirx = g_player.newdirxy[0];
		g_player.diry = g_player.newdirxy[1];
		ft_rotate_2d(g_player.planex, g_player.planey, -3, g_player.newdirxy);
		g_player.planex = g_player.newdirxy[0];
		g_player.planey = g_player.newdirxy[1];
	}
	if (g_keydata.l || g_keydata.mousedragl)
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
** Originally these movement functions were more verbatim copies of the Lode
** tutorial (except where I use my rotate function instead of Lode's), but for
** the bonus I've modified them a bit more to help me organize my code for the
** collisions. They still say the same thing, except in addition to requiring
** the player's new location to be within a traversable square ('0') on the map
** we also require it to be outside the hit circle of any collidable sprite
** (sprcollide is false).
*/

int	adstrafe(void)
{
	double	newposx;
	double	newposy;
	char	*mapchr;

	ft_rotate_2d(g_player.dirx, g_player.diry, 90, g_player.newdirxy);
	if (g_keydata.a)
	{
		newposx = (g_player.posx + g_player.newdirxy[0] * g_player.movespeed);
		newposy = (g_player.posy + g_player.newdirxy[1] * g_player.movespeed);
		mapchr = &g_config.map[(int)g_player.posy][(int)newposx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(g_player.posy, newposx))
			g_player.posx = newposx;
		mapchr = &g_config.map[(int)newposy][(int)g_player.posx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(newposy, g_player.posx))
			g_player.posy = newposy;
	}
	if (g_keydata.d)
	{
		newposx = (g_player.posx - g_player.newdirxy[0] * g_player.movespeed);
		newposy = (g_player.posy - g_player.newdirxy[1] * g_player.movespeed);
		mapchr = &g_config.map[(int)g_player.posy][(int)newposx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(g_player.posy, newposx))
			g_player.posx = newposx;
		mapchr = &g_config.map[(int)newposy][(int)g_player.posx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(newposy, g_player.posx))
			g_player.posy = newposy;
	}
	return (1);
}

int	wsupdown(void)
{
	double	newposx;
	double	newposy;
	char	*mapchr;

	if (g_keydata.w)
	{
		newposx = g_player.posx + g_player.dirx * g_player.movespeed;
		newposy = g_player.posy + g_player.diry * g_player.movespeed;
		mapchr = &g_config.map[(int)g_player.posy][(int)newposx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(g_player.posy, newposx))
			g_player.posx = newposx;
		mapchr = &g_config.map[(int)newposy][(int)g_player.posx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(newposy, g_player.posx))
			g_player.posy = newposy;
	}
	if (g_keydata.s)
	{
		newposx = g_player.posx - g_player.dirx * g_player.movespeed;
		newposy = g_player.posy - g_player.diry * g_player.movespeed;
		mapchr = &g_config.map[(int)(g_player.posy)][(int)newposx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(g_player.posy, newposx))
			g_player.posx = newposx;
		mapchr = &g_config.map[(int)newposy][(int)g_player.posx];
		if (teleporter(mapchr))
			return (0);
		if ((*mapchr == '0' || *mapchr == 'O') && \
		!sprcollide(newposy, g_player.posx))
			g_player.posy = newposy;
	}
	return (1);
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
	if (!wsupdown())
		return ;
	if (!adstrafe())
		return ;
	rlrotate();
}
