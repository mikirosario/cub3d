/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dooranimator_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 03:34:28 by miki              #+#    #+#             */
/*   Updated: 2020/09/18 17:55:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** To continue the animation, if the timestamp hasn't been created yet (first
** animation frame) we open/close the door (depending on its present state) by
** 0.025 the first frame and get the timestamp. Otherwise, we check to see if
** at least 31.25 miliseconds have elapsed since the last timestamp (31.25 * 64
** animationframes gives us 2000 miliseconds, for our 2-second timer). If so, we
** we open/close the door by 0.0125. In either case, we increment
** animationframes.
**
** 0.0125 * 63 frames of animation + 0.025 = 0,8125, which is
** slightly greater than the 0.8 (80%) difference between an open and closed
** door. This creates a 'snap-back' effect when the doors are set by the
** enddooranimation function that simulates a 'rebound'.
**
** If the timer is active and 31.25 miliseconds have not yet elapsed since the
** last timestamp, we leave without doing anything.
**
** The door.wav launches on the first animation frame and plays back at reduced
** speed to match the animation.
**
** Sound attribution (door.wav): Daniel Simion, soundbible.com.
*/

void	continuedooranimation(t_raycasterdata *rdata, struct timeval *tstart)
{
	if (!tstart->tv_sec)
	{
		if (*(rdata->animatedoor->dooraddr) != 'O')
			rdata->animatedoor->doorend += 0.025;
		else
			rdata->animatedoor->doorend -= 0.025;
		rdata->animationframes++;
		system("afplay -r 0.65 ./door.wav &");
		gettimeofday(tstart, NULL);
	}
	else if (msec_diff(tstart, NULL) > 31.25)
	{
		if (*(rdata->animatedoor->dooraddr) != 'O')
			rdata->animatedoor->doorend += 0.0125;
		else
			rdata->animatedoor->doorend -= 0.0125;
		rdata->animationframes++;
		gettimeofday(tstart, NULL);
	}
}

/*
** To end the animation loop, if the door was closed before, its character is
** changed to 'O', a special character that the playermovement function treats
** as a traversable square. If it was open before, its character is set back to
** its spritetype ('-' or '|'). If it was open before and a player is inside the
** door square, it will reset to open again to avoid players becoming trapped by
** the door.
**
** Remember the doorend variable tracks door 'openness'. 0 is 0% open, 0.8 is
** 80% open. 0.8 is maximum openness, so you can still see the door edge and
** handle while it is open.
*/

void	enddooranimation(t_raycasterdata *rdata)
{
	if (*(rdata->animatedoor->dooraddr) == 'O' && \
	&(g_config.map[(int)g_player.posy][(int)g_player.posx]) == \
	rdata->animatedoor->dooraddr)
		rdata->animatedoor->doorend = 0.8;
	else
	{
		*(rdata->animatedoor->dooraddr) = \
		*(rdata->animatedoor->dooraddr) == 'O' ? \
		rdata->animatedoor->spritetype : 'O';
		rdata->animatedoor->doorend = *(rdata->animatedoor->dooraddr) == 'O' ? \
		0.8 : 0;
	}

}

/*
** The tstart structure gets the timestamp at each frame of animation. Each
** door animation lasts 64 frames over 2000 miliseconds (2 sec). If the tv_sec
** variable of tstart isn't 0 and the number of animationframes counted is 64,
** the animation is deemed finished. If the door was closed before, it is set as
** open. If it was open before, it is set as closed, unless the player is in the
** way of the door, in which case it is reset to open to prevent the player from
** becoming trapped. All relevant conditional variables are reset to NULL/0, and
** we return (0) to signal completion.
**
** If the animation has not begun (tv_sec not defined) or has not finished
** (animationframes less than 64), we start or continue the animation,
** respectively. If the door is open, we close it; if closed, we open it. The
** opening/closing is divided into 64 steps. The first step is purposely too
** big, which creates the illusion of a 'rebound' effect at the end when the
** door is set to its final state at the end of the animation. We return (1) to
** signal that the animation remains ongoing. Note that the spacebar will be
** unusable until the animation finishes.
*/

int		animatedoor(t_raycasterdata *rdata)
{
	static struct timeval	tstart = {0};

	if (tstart.tv_sec && rdata->animationframes == 64)
	{
		enddooranimation(rdata);
		tstart.tv_sec = 0;
		tstart.tv_usec = 0;
		rdata->animatedoor = NULL;
		rdata->animationframes = 0;
		return (0);
	}
	continuedooranimation(rdata, &tstart);
	return (1);

}

/*
** If no door is presently being animated the player will cast one ray right
** down the middle of the screen. If the player is at least 1.25 away from a
** door and is pointing at that door, we look up the door's map address in the
** g_config.door pointer array (which points to all members of the list of
** doors) and copy that address to the animatedoor flag in rdata, then we leave
** the function without reseting the spacebar key.
**
** If the animatedoor flag is set, we enter the animatedoor function to handle
** door animation. If animatedoor returns 1, animation is ongoing, and we again
** leave the function without resetting the spacebar key. If it returns 0, then
** animation has finished, and we reset the spacebar key before exiting.
**
** Sound attribution (discovery.wav): gsb1039, freesound.org.
*/

void	activatedoor(t_raycasterdata *rdata)
{
	char		mapchr;
	int			i;

	i = 0;
	if (!rdata->animatedoor)
	{
		castoneray((g_config.screenw - 1) / 2);
		if ((mapchr = g_config.map[g_raydata.mapy][g_raydata.mapx]) == '/' || mapchr == 'O')
		{
			if (fabs(g_raydata.perpwalldist) < 1.25)
			{
				while (g_config.door[i]->dooraddr != &g_config.map[g_raydata.mapy][g_raydata.mapx])
					i++;
				rdata->animatedoor = g_config.door[i];
				return ;
			}
		}
		else if (mapchr == 'v' && g_player.inventory.potions == 3)
		{
			g_config.map[g_raydata.mapy][g_raydata.mapx] = '/';
			system("afplay -t 2 ./discovery.wav &");
		}
	}
	else if (animatedoor(rdata))
		return ;
	g_keydata.sp = 0;
}