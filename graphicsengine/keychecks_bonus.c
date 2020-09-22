/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keychecks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:44:48 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 04:11:37 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function is launched when the user exits normally, by pressing escape
** or by clicking the X on the upper left of the window.
*/

int		ft_stop(int key, void *param)
{
	(void)param;
	if (key == 0x35 || key == 0x00)
	{
		freeme();
		ft_printf(GREEN"\n**** THANKS FOR PLAYING! :D ****\n\n"RESET);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/*
** If a key is being pressed, a bit is flipped to 1 to store this information.
**
** The stop function is triggered by the escape key. The right and left arrow
** keys correspond to r and l, respectively. The rest of the keys correspond to
** their namesakes in keydata.
*/

int	keypress(int key, void *param)
{
	(void)param;
	if (key == 0x35)
		ft_stop(key, (void *)0);
	if (key == 0xD)
		g_keydata.w = 1;
	if (key == 0x1)
		g_keydata.s = 1;
	if (key == 0x2)
		g_keydata.d = 1;
	if (key == 0x0)
		g_keydata.a = 1;
	if (key == 0x7C)
		g_keydata.r = 1;
	if (key == 0x7B)
		g_keydata.l = 1;
	if (key == 0x2E)
	{
		if (g_keydata.m == 2)
			g_keydata.m = 0;
		else
			g_keydata.m += 1;
	}
	if (key == 0x52)
		g_keydata.ctrl = 1;
	if (key == 0x31)
		g_keydata.sp = 1;
	if (key == 0x24)
		g_keydata.enter = 1;
	return (0);
}

/*
** If a key is not being pressed, this information is stored by fliping the
** key's bit to 0.
**
** Keyrelease for Xubuntu Linux
**
** int ft_keyrelease(int key, void *param)
** {
**	(void)param;
**	//move forwards if no wall in front
**	if (key == 0x77)
**		g_keydata.w = 0;
**	//move backwards if no wall in front
**	if (key == 0x73)
**		g_keydata.s = 0;
**	//strafe right if no wall to right
**	if (key == 0x64)
**		g_keydata.d = 0;
**	//strafe left if no wall to left
**	if (key == 0x61)
**		g_keydata.a = 0;
**	//clockwise rotation
**	if (key == 0xff53)
**		g_keydata.r = 0;
**	//anticlockwise rotation
**	if (key == 0xff51)
**		g_keydata.l = 0;
**	return (0);
** }
**
** Mac:
*/

int	keyrelease(int key, void *param)
{
	(void)param;
	if (key == 0xD)
		g_keydata.w = 0;
	if (key == 0x1)
		g_keydata.s = 0;
	if (key == 0x2)
		g_keydata.d = 0;
	if (key == 0x0)
		g_keydata.a = 0;
	if (key == 0x7C)
		g_keydata.r = 0;
	if (key == 0x7B)
		g_keydata.l = 0;
	return (0);
}
