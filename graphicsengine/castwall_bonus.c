/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castwall_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 04:54:32 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/21 04:56:13 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	castwall(t_raycasterdata *rdata)
{
	int	x;

	x = 0;
	while (x < g_config.screenw)
	{
		castray(x);
		calculateframeline();
		drawframeline(x, rdata);
		if (g_config.spritenum)
			g_config.zbuffer[x] = g_raydata.perpwalldist;
		x++;
	}
}