/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:10:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/06 17:42:53 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Initial variable values. Note: many values are left uninitialized because
** they are defined during configuration, and never accessed before then.
**
** Note: uDiv and vDiv are divisors that can be used to resize the sprites.
** uDiv controls horizontal size and vDiv controls vertical size. Another
** variable, g_config.vMove, controls the vertical position of the sprite on
** screen. It is defined within the raycaster as being equal to the height of
** the sprite times vDiv (g_config.spriteH * g_config.vDiv). This will always
** keep the sprites appearing to remain on the ground, regardless of how they
** are resized here. It isn't refreshed, so you shouldn't fiddle with the
** values during game time - anyway, they're ints, so they aren't very precise.
**
** 1 is the original sprite size, 2 is half of the original sprite size, 3 is
** a third of the original sprite size, and so on.
**
** The wallMultiplier variable will similarly increase the height of walls,
** where 2 means twice the height, 3 means three times the height, and so on.
**
** The wallMultiplier variable will similarly increase the height of walls,
** where 2 means twice the height, 3 means three times the height, and so on.
** I haven't figured out how to get this to scale with the sprite sizes though
** so you'll have to fiddle with the divisors to get it to look right. ;)
*/

void	initialize(void)
{
	g_player.rotSpeed = 0.1;
	g_player.moveSpeed = 0.25;
	g_frameData.ofloorColor = 0x00669999;
	g_frameData.oceilingColor = 0x0066004b;
	g_config.spriteNum = 0;
	g_config.spriteList = NULL;
	g_config.Map = NULL;
	g_config.wallMultiplier = 1;
	g_config.uDiv = 1;
	g_config.vDiv = 1;
	g_keyData.w = 0;
	g_keyData.a = 0;
	g_keyData.s = 0;
	g_keyData.d = 0;
	g_keyData.r = 0;
	g_keyData.l = 0;
	g_keyData.m = 1;
}
