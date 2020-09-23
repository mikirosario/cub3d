/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monologue_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:16:48 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/23 18:10:58 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	orentalk(int sprnum, double playerdistance)
{
	static char	stayout = 0;

	if (!stayout && !g_framedata.phrase && playerdistance <= 2.6 && \
	g_config.sprt[sprnum]->spritetype == '6')
	{
		g_framedata.phrase = 1;
		stayout = 1;
	}
}

void	marvintalk(int sprnum, double playerdistance)
{
	static char	stayout = 0;

	if (!stayout && g_player.inventory.rubies == 3)
		stayout = 1;
	if (!stayout && !g_framedata.phrase && playerdistance <= 2.6 && \
	g_config.sprt[sprnum]->spritetype == '3')
		g_framedata.phrase = 2;
	else if (stayout == 1 && !g_framedata.phrase && playerdistance <= 2.6 && \
	g_config.sprt[sprnum]->spritetype == '3')
	{
		g_framedata.phrase = 3;
		if (!g_player.inventory.chisme)
		{
			g_player.inventory.rubies = 0;
			g_player.inventory.chisme = 1;
			playsound(CHISME);
		}
	}
}
