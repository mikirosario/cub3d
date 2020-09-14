/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcaster_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:09:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/14 13:29:44 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** Hodoor? Horror door? This took me FOREVER to figure out. The pain. The agony!
** The maths! All to discover this simple solution after a week of clawing at
** my face!
**
** Note that doorend tracks 'how open' a door is. 0 means 0% open. 0.1 means
** 10% open. 0.2 means 20% open. 1 means 100% open. 1 corresponds to the west,
** where the door ends when fully open, and 0 to the east side of the map, where
** it ends when fully closed.
**
** We follow the ray halfway through the square with the door and record its
** landing location. Then we just ask if it is less than doorend plus whatever
** mapx we are in. If it is, the ray is allowed to go on its merry way. If not,
** it hits door.
**
** We record the offset from the edge of the square (based on door openness) to
** offset the texture (walltexparams in calculateframeline_bonus.c) by the same
** proportion. We also record perpwall dist to the door if the ray is for the
** centre of the screen, which is the distance we'll use to decide whether a
** player is close enough to try to open a door.
*/

int		hordoorslide(void)
{
	t_localraydata	local;
	t_spritedata	**door;


	//if we came from below

		local.perpwalldist = ((double)(g_raydata.mapy + (0.5 * g_raydata.stepy)) - g_player.posy + \
		(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
		local.wallx = g_player.posx + local.perpwalldist * g_raydata.raydirx;


		door = g_config.door;
		while ((*door)->dooraddr != &g_config.map[g_raydata.mapy][g_raydata.mapx])
			door++;
		if (local.wallx > (*door)->doorend + g_raydata.mapx && local.wallx <= 1 + g_raydata.mapx)
		{
			g_framedata.dooroffset = (*door)->doorend;
			g_raydata.perpwalldist = local.perpwalldist;
//			if (!g_player.camerax)
//				g_framedata.middleraydoordist = local.perpwalldist;	
			return (1);
		}
	
	return (0);
}

/*
** This is like hordoor, but all vectors are perpendicular.
**
** Note that doorend tracks 'how open' a door is. 0 means 0% open. 0.1 means
** 10% open. 0.2 means 20% open. 1 means 100% open. In this case, 0 corresponds
** to the south, where the door ends when fully open, and 1 to the north side of
** the map, where it ends when fully closed.
**
** We follow the ray halfway through the square with the door and record its
** landing location. Then we just ask if it is less than doorend plus whatever
** mapy we are in. If it is, the ray is allowed to go on its merry way. If not,
** it hits door.
**
** We record the offset from the edge of the square (based on door openness) to
** offset the texture (walltexparams in calculateframeline_bonus.c) by the same
** proportion.
**
** We also record perpwall dist to the door if the ray is for the
** centre of the screen, which is the distance we'll use to decide whether a
** player is close enough to try to open a door.
**
** These functions supersede and replace hordoorhitcheck and verdoorhitcheck.
*/

int		verdoorslide(void)
{
	t_localraydata	local;
	t_spritedata	**door;


	//if we came from the side

		local.perpwalldist = ((double)(g_raydata.mapx + (0.5 * g_raydata.stepx)) - g_player.posx + \
		(1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
		local.wallx = g_player.posy + local.perpwalldist * g_raydata.raydiry;


		door = g_config.door;
		while ((*door)->dooraddr != &g_config.map[g_raydata.mapy][g_raydata.mapx])
			door++;
		if (local.wallx > (*door)->doorend + g_raydata.mapy && local.wallx <= 1 + g_raydata.mapy)
		{
			g_framedata.dooroffset = (*door)->doorend;
			g_raydata.perpwalldist = local.perpwalldist;
//			if (!g_player.camerax) Do I really want 1080 comparisons more per frame...? ¬¬
//				g_framedata.middleraydoordist = local.perpwalldist;	
			return (1);
		}
	
	return (0);
}
