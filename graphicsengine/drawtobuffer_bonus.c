/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawtobuffer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:57:26 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 20:50:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function exists essentially to provide convenient, one-stop access to
** the colors being drawn to buffer once we know what color we want to draw
** and where, allowing us to modify that color before drawing as appropriate to
** the situation or point in the game we define.
**
** Colors are sent as hexadecimal unsigned integers.
**
** If graphics mode is 1 or 2, shading is added. If we have invincibility frames
** the display flashes red every other frame until the invincibility wears off.
*/

void	drawtobuffer_bonus(unsigned int *buf, int pixel, unsigned int xcolor)
{
	if (g_framedata.lastlevel)
		xcolor = xcolor >> 1 & 0x007F7F7F;
	if (g_framedata.invincibilityframes % 2)
		xcolor = xcolor >> 1 & 0x007F0000;
	buf[pixel] = xcolor;
}
