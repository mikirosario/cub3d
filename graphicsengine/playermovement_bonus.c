/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:03:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 06:17:17 by miki             ###   ########.fr       */
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
** to my way of doing it. :P
**
** My method, just applies 3 degrees of rotation to the player/camera for every
** frame the l (anticlockwise) or r (clockwise) keys are depressed). For the
** bonus compilation r and l will also be triggered by dragging the mouse in the
** desired direction of rotation.
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
** (sprcollide is false). They also substitute player movement for teleportation
** if the player moves into a teleportation square.
**
** To stop players from ever being able to get close enough to a wall to 'see
** through' it I add a bit of padding to the wall check, so you'll actually
** detect a wall and be denied further movement a bit before you get to the
** very quantum edge of it. ;p See, I told you all I'd fix it before the
** evaluation. Sheesh. ;p
*/

int		movecheck(double newposx, double newposy)
{
	char	*mapchr[2];
	double	padx;
	double	pady;

	padx = newposx < g_player.posx ? -0.1 : 0.1;
	pady = newposy < g_player.posy ? -0.1 : 0.1;
	mapchr[0] = &g_config.map[(int)g_player.posy][(int)(newposx + padx)];
	mapchr[1] = &g_config.map[(int)(newposy + pady)][(int)g_player.posx];
	if (teleporter(mapchr[0]) || teleporter(mapchr[1]))
		return (0);
	if ((*mapchr[0] == '0' || *mapchr[0] == 'O') && \
	!sprcollide(g_player.posy, newposx))
		g_player.posx = newposx;
	if ((*mapchr[1] == '0' || *mapchr[1] == 'O') && \
	!sprcollide(newposy, g_player.posx))
		g_player.posy = newposy;
	return (1);
}

void	getmovedir(int key, double *dirxy)
{
	if (key == 0)
	{
		dirxy[0] = g_player.dirx;
		dirxy[1] = g_player.diry;
	}
	else if (key == 1)
	{
		dirxy[0] = -g_player.dirx;
		dirxy[1] = -g_player.diry;
	}
	else if (key == 2)
	{
		dirxy[0] = g_player.newdirxy[0];
		dirxy[1] = g_player.newdirxy[1];
	}
	else if (key == 3)
	{
		dirxy[0] = -g_player.newdirxy[0];
		dirxy[1] = -g_player.newdirxy[1];
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
	char	wsad[4];
	double	movedirxy[2];
	double	newposxy[2];
	int		i;

	wsad[0] = g_keydata.w;
	wsad[1] = g_keydata.s;
	wsad[2] = g_keydata.a;
	wsad[3] = g_keydata.d;
	if (wsad[2] || wsad[3])
		ft_rotate_2d(g_player.dirx, g_player.diry, 90, g_player.newdirxy);
	i = 0;
	while (i < 4)
	{
		if (wsad[i])
		{
			getmovedir(i, movedirxy);
			newposxy[0] = g_player.posx + movedirxy[0] * g_player.movespeed;
			newposxy[1] = g_player.posy + movedirxy[1] * g_player.movespeed;
			if (!(movecheck(newposxy[0], newposxy[1])))
				return ;
		}
		i++;
	}
	rlrotate();
}
