/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:10:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/17 18:52:45 by mrosario         ###   ########.fr       */
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
** This function used a system call to retrieve the native display resolution
** on MacOSX because our stripped-down version of X11 can't do that for us. :p
** I just use awk to find the Resolution in the system profiler and retrieve
** the relevant fields, then atoi to pass them to the variables where I store
** them. popen returns a stream and read uses file numbers, so I need to use
** fileno to convert it.
**
** It seemed like a good idea at the time, but we're not even allowed to use
** popen/pclose functions. :_( Anyway it doesn't matter, because the
** resolution MacOSX is reporting just does not agree with empirical
** observation. :p It gets the possible physical resolution but not the scaled
** resolution. There is an osascript that works, but it causes a confirmation
** window to pop up that will just confuse the user. There are a bunch
** programs that do it, but they can break depending on OS version.
**
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

void	initialize(void)
{
	g_player.rotspeed = 0.1;
	g_player.movespeed = 0.25;
	g_player.life = 6;
	g_player.inventory.potions = 0;
	g_player.inventory.rubies = 0;
	g_player.inventory.catsbane = 0;
	g_player.attack = 0;
	g_framedata.xfloorcolor = 0x00669999;
	g_framedata.xceilingcolor = 0x0066004b;
	g_config.spritenum = 0;
	g_config.doornum = 0;
	g_config.sprtexnum = 0;
	g_config.spritelist = NULL;
	g_config.maplist = NULL;
	g_config.wallmultiplier = 1;
	g_config.udiv = 1;
	g_config.vdiv = 1;
	g_keydata.w = 0;
	g_keydata.a = 0;
	g_keydata.s = 0;
	g_keydata.d = 0;
	g_keydata.r = 0;
	g_keydata.l = 0;
	g_keydata.m = 1;
	g_keydata.ctrl = 0;
	g_keydata.sp = 0;
	initializedoorline();
	getdisplayresolution();
}
