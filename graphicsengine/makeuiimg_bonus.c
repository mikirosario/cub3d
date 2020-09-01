/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeuiimg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:41:02 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/01 17:32:16 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	buildui(unsigned int *buf)
{
	int	bx;
	int	tx;
	int	y;

	y = 0;
	while (y < g_border.top_left.texh - 1)
	{
		bx = y * g_config.screenw;
		tx = y * g_border.top_left.texw;
		while (tx < y * g_border.top_left.texw + g_border.top_left.texw)
		{
			if (g_border.top_left.tex_ptr[tx] != 0xFF000000)
				buf[bx] = g_border.top_left.tex_ptr[tx];
			bx++;
			tx++;
		}
		y++;
	}
}