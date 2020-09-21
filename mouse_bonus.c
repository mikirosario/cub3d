/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:20:38 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/21 20:20:16 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** This function detects when the player is dragging the mouse left or right,
** and signals this using the mutually exclusive mousedragr and mousedragl
** flags. We can then use these flags for movement control.
*/

int		mousemove(int x, int y, void *param)
{
	(void)param;
	(void)y;
	if (g_keydata.lbutton.status)
	{
		if (x > g_keydata.lbutton.startx)
		{
			g_keydata.mousedragr = 1;
			g_keydata.mousedragl = 0;
		}
		else if (x < g_keydata.lbutton.startx)
		{
			g_keydata.mousedragl = 1;
			g_keydata.mousedragr = 0;
		}
	}
	return (0);
}

int		mouserelease(int button, int x, int y, void *param)
{
	(void)param;
	if (button == 1)
	{
		g_keydata.lbutton.status = 0;
		g_keydata.mousedragl = 0;
		g_keydata.mousedragr = 0;
		g_keydata.lbutton.endx = x;
		g_keydata.lbutton.endy = y;
	}
	if (button == 2)
	{
		g_keydata.rbutton.status = 0;
		g_keydata.rbutton.endx = x;
		g_keydata.rbutton.endy = y;
	}
	if (button == 3)
	{
		g_keydata.wheel.status = 0;
		g_keydata.wheel.endx = x;
		g_keydata.wheel.endy = y;
	}
	return (0);
}

int		mousepress(int button, int x, int y, void *param)
{
	(void)param;
	if (button == 1)
	{
		g_keydata.lbutton.status = 1;
		g_keydata.lbutton.startx = x;
		g_keydata.lbutton.starty = y;
	}
	if (button == 2)
	{
		g_keydata.rbutton.status = 1;
		g_keydata.rbutton.startx = x;
		g_keydata.rbutton.starty = y;
	}
	if (button == 3)
	{
		g_keydata.wheel.status = 1;
		g_keydata.wheel.startx = x;
		g_keydata.wheel.starty = y;
	}
	return (0);
}
