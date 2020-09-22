/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:10:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 18:38:27 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	initializedoorline(void)
{
	g_door.startx = 0;
	g_door.starty = 0.5;
	g_door.endx = 1;
	g_door.endy = 0.5;
}

/*
** Bonus privilege. I use Core Graphics library to set the native display size.
** Now we're talking!
*/

void	getdisplayresolution(void)
{
	CGDirectDisplayID displayid;

	displayid = CGMainDisplayID();
	g_config.nativedisplayw = CGDisplayPixelsWide(displayid);
	g_config.nativedisplayh = CGDisplayPixelsHigh(displayid);
}

/*
** I am not even pretending this is anything other than what it is. :p
*/

void	initialize2(t_raycasterdata *rdata)
{
	g_keydata.w = 0;
	g_keydata.a = 0;
	g_keydata.s = 0;
	g_keydata.d = 0;
	g_keydata.r = 0;
	g_keydata.l = 0;
	g_keydata.m = 1;
	g_keydata.ctrl = 0;
	g_keydata.sp = 0;
	g_keydata.enter = 0;
	rdata->animatedoor = NULL;
	rdata->animationframes = 0;
	rdata->portalanimframes = 0;
	reset_timer(&rdata->catsbanetimer);
	reset_timer(&rdata->phrasetimer);
	reset_timer(&rdata->chismetimer);
	reset_timer(&rdata->endingtimer);
	initializedoorline();
}
/*
** Initial variable values. Note: many values are left uninitialized because
** they are defined during configuration, and never accessed before then.
**
** Note: uDiv and vDiv are divisors that can be used to resize the sprites.
** uDiv controls horizontal size and vDiv controls vertical size. Another
** variable, g_config.vmove, controls the vertical position of the sprite on
** screen. It is defined within the raycaster as being equal to the height of
** the sprite times vDiv (g_config.spriteh * g_config.vdiv). This will always
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

void	initialize(t_raycasterdata *rdata)
{
	g_player.rotspeed = 0.1;
	g_player.movespeed = 0.25;
	g_player.life = 6;
	g_player.inventory.potions = 0;
	g_player.inventory.rubies = 0;
	g_player.inventory.catsbane = 0;
	g_player.inventory.chisme = 0;
	g_player.attack = 0;
	g_framedata.xfloorcolor = 0x00669999;
	g_framedata.xceilingcolor = 0x0066004b;
	g_framedata.phrase = 0;
	g_framedata.lastlevel = 0;
	g_config.spritenum = 0;
	g_config.doornum = 0;
	g_config.sprtexnum = 0;
	g_config.spritelist = NULL;
	g_config.maplist = NULL;
	g_config.wallmultiplier = 1;
	g_config.udiv = 1;
	g_config.vdiv = 1;
	g_config.musicpid = 0;
	g_config.ending = 0;
	initialize2(rdata);
	getdisplayresolution();
}
