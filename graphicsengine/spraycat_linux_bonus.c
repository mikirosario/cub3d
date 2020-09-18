/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spraycat_linux_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:12:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/18 12:30:22 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This is a bit of a janky solution, but I'm kind of in a rush to turn this
** project in already. xD Since I already check each sprite's distance to the
** player every frame, for hit detection I first ask if the player has Catsbane
** in their inventory, then if the enter button is active (it stays active half
** a second after being pressed). If both are true, we check every sprite that
** is 0.33 from the player or less to see if any of its pixels to be drawn fall
** on x = screenw / 2 - 1 (the centre line). If so, we'll consider that this
** sprite has been damaged. ;) Since sprites are drawn after everything else is
** drawn, the spritecaster does take occlusion by walls into account (it won't
** take occlusion by other sprites into account, but this is basically a melee
** weapon that only works when you're close enough to the sprite that no other
** sprites could fit between you because of their colliders with diameter 0.5).
**
** So... yeah. Bit of a quick and dirty solution, but I am really ready for the
** next project at this point... I spent way too long on the sliding doors! xD
*/

void	spraycat(t_spritedata *sprite)
{
	int	pid;

	if (g_player.attack) 
	{
		if (--sprite->life < 1) //enemy loses life, dies if at zero
			sprite->remove = 1;
		//enemy damage anim/colour flag
		pid = fork();
		if (!pid)
		{
			system("aplay ./meow.wav");
			exit(EXIT_SUCCESS);
		}
		//shrill meow sound effect
		g_player.attack = 0;
		sprite->checkdamage = 0;
		sprite->texture = sprite->animtex[1];
		sprite->hitanimationframes = 15;
	}
}