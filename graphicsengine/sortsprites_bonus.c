/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsprites_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:24:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/04 18:06:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function will control the player's health bar. If the player is within
** .33 of an enemy sprite, the player will lose 1 health per
** invincibilityframes frames per enemy at that distance.
**
** If the player is within .33 of a healing sprite, the player will gain life
** at a rate of 1 per frame.
*/

void	getplayerdamage(int sprnum)
{
	//si si no tenemos invincibility frames y es enemigo
	if (!g_framedata.invincibilityframes && g_config.sprt[sprnum]->spritetype == '2')
	{
			if (g_player.life && (g_framedata.invincibilityframes = 15))
				g_player.life--;
	}
	if (g_config.sprt[sprnum]->spritetype == '4' && g_player.inventory < 3)
	{
			g_config.sprt[sprnum]->remove = 1;
			g_player.inventory++;
	}
	//	if (g_player.life < 6)
	//		g_player.life++;
}

/*
** Here we get the distance from the player position of each sprite.
**
** Remember our reference distance is 1, which is the distance between two
** opposite sides of a map square.
**
** In the bonus compilation we're also interested in any sprites at a distance
** of .25 from the player. At that distance, assuming every object in the game
** has a hit circle with a radius of .25 projected around it, only six sprites
** should be able to fit at a time without colliding with each other (the
** hexagonal circle packing arrangement gives maximum density for packing
** identical circles - check Wikipedia on this topic for details).
**
** Therefore, to enforce the hit circle, we need to monitor at most the
** positions of six other objects at a time within the player's vicinity
** (and the sprites, if the sprites have a movement AI).
**
** Starting from this most densely packed arrangement, where six objects are
** exactly at a distance of .25 from the player, if we add a distance of .08
** between the centre of every object and the player and make them adjacent
** again in a circle around the player, we open up only .08 * 6 == .48 of
** space, which is not enough for another hit circle of diameter .5 to fit.
**
** Therefore, we know that, given a hit circle radius of .25, an object will be
** within a distance of .25 + .08 == .33 of no more than six other collidable
** objects at any given time, which we'll call 'neighbors'. Each potential
** 'neighbor' can be abstracted to a 'slot' in a collision array called
** closesprite[6].
**
** Thus, if getdistances detects any sprite at neighboring distance (<= .33)
** from the player, it becomes a collision hazard. We will ID it and send its
** ID (sprite number) to the collision array for use by playermovement to avoid
** a collision in subsequent frames if the player approaches too close. If
** values in that array are at -1, it will mean no sprite has been IDed
** in that slot in this frame.
**
** Since we only have to track at maximum six sprites at a time, this will
** limit the number of additional operations we need to do per frame to enforce
** collision detection, even if many sprites are in the map. Woot. ^_^
**
** It's a bit weird to have this in sortsprites I suppose, but since I get
** distances here it is very convenient. This function calls getplayerdamage,
** which will determine whether the player is cruising for a bruising. If
** within 0.33 of an enemy sprite, we'll damage the player and start a timer
** called invincibilityframes that will have the effect of blocking further
** damage and causing the screen to flash red every other frame. Heart meter
** will also go down by half, of course.
*/

void	getdistances(double *distance, int *spriteorder)
{
	int i;
	int s;

	i = 0;
	s = 6;
	while (s--)
		g_framedata.closesprite[s] = -1;
	s++;
	while (i < g_config.spritenum)
	{
		spriteorder[i] = i;
		distance[i] = ((g_player.posx - g_config.sprt[i]->posx) * \
		(g_player.posx - g_config.sprt[i]->posx) + (g_player.posy - \
		g_config.sprt[i]->posy) * (g_player.posy - g_config.sprt[i]->posy));
		if (distance[i] <= 0.33)
		{
			g_framedata.closesprite[s] = i;
			getplayerdamage(i);
			s++;
		}
		i++;
	}
}

/*
** This function will sort the sprites in the sprite list in order of their
** distance from the player, from furthest to closest. The spriteorder array
** will then be used to address the sprites in that order while drawing them
** for the frame.
*/

void	sortsprites(int *spriteorder)
{
	double	distance[g_config.spritenum];
	int		tmp;
	int		i;

	getdistances(distance, spriteorder);
	i = -1;
	while (g_config.spritenum > 1 && ++i < g_config.spritenum - 1)
	{
		if (distance[i] < distance[i + 1])
		{
			tmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = tmp;
			tmp = spriteorder[i];
			spriteorder[i] = spriteorder[i + 1];
			spriteorder[i + 1] = tmp;
			i = -1;
		}
	}
}
