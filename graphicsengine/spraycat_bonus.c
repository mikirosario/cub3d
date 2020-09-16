/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spraycat_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:12:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/16 20:26:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int		spraycat()
{
	
}