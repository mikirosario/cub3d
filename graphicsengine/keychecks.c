/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keychecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:44:48 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 18:54:45 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
