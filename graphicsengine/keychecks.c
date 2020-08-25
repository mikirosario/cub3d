/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keychecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:44:48 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/25 19:29:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** If a key is being pressed, a bit is flipped to 1 to store this information.
**
** The stop function is triggered by the escape key. The right and left arrow
** keys correspond to r and l, respectively. The rest of the keys correspond to
** their namesakes in keydata.
**
** Keypress for Xubuntu Linux:
**
** int ft_keypress(int key, void *param)
** {
**	(void)param;
**	if (key == 0xff1b)
**		ft_stop(key, (void *)0);
**	//move forwards if no wall in front
**	if (key == 0x77)
**		g_keyData.w = 1;
**	//move backwards if no wall in front
**	if (key == 0x73)
**		g_keyData.s = 1;
**	//strafe right if no wall to right
**	if (key == 0x64)
**		g_keyData.d = 1;
**	//strafe left if no wall to left
**	if (key == 0x61)
**		g_keyData.a = 1;
**	//clockwise rotation
**	if (key == 0xff53)
**		g_keyData.r = 1;
**	//anticlockwise rotation
**	if (key == 0xff51)
**		g_keyData.l = 1;
**	if (key == 0x6d)
**	{
**		if (g_keyData.m == 2)
**			g_keyData.m = 0;
**		else
**
**			g_keyData.m += 1;
**	}
**	return (0);
** }
**
** Map:
*/

int	keypress(int key, void *param)
{
	(void)param;
	if (key == 0x35)
		ft_stop(key, (void *)0);
	if (key == 0xD)
		g_keyData.w = 1;
	if (key == 0x1)
		g_keyData.s = 1;
	if (key == 0x2)
		g_keyData.d = 1;
	if (key == 0x0)
		g_keyData.a = 1;
	if (key == 0x7C)
		g_keyData.r = 1;
	if (key == 0x7B)
		g_keyData.l = 1;
	if (key == 0x2E)
	{
		if (g_keyData.m == 2)
			g_keyData.m = 0;
		else
			g_keyData.m += 1;
	}
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
**		g_keyData.w = 0;
**	//move backwards if no wall in front
**	if (key == 0x73)
**		g_keyData.s = 0;
**	//strafe right if no wall to right
**	if (key == 0x64)
**		g_keyData.d = 0;
**	//strafe left if no wall to left
**	if (key == 0x61)
**		g_keyData.a = 0;
**	//clockwise rotation
**	if (key == 0xff53)
**		g_keyData.r = 0;
**	//anticlockwise rotation
**	if (key == 0xff51)
**		g_keyData.l = 0;
**	return (0);
** }
**
** Mac:
*/

int	keyrelease(int key, void *param)
{
	(void)param;
	if (key == 0xD)
		g_keyData.w = 0;
	if (key == 0x1)
		g_keyData.s = 0;
	if (key == 0x2)
		g_keyData.d = 0;
	if (key == 0x0)
		g_keyData.a = 0;
	if (key == 0x7C)
		g_keyData.r = 0;
	if (key == 0x7B)
		g_keyData.l = 0;
	return (0);
}
