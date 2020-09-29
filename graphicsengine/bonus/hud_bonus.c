/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 05:27:18 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/27 11:57:28 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

int		usepotion(void)
{
	g_keydata.ctrl = 0;
	if (g_player.inventory.potions && g_player.life < 6)
	{
		g_player.inventory.potions--;
		g_player.life += g_player.life == 5 ? 1 : 2;
		return (1);
	}
	return (0);
}

void	refreshcatsbane(unsigned int *buf, t_raycasterdata *rdata)
{
	if (g_player.inventory.catsbane)
	{
		if (!g_keydata.enter)
			yput_to_buffer((g_config.screenw / 2) - g_catsbane.idle.texw / 2, \
			g_config.screenh - g_catsbane.idle.texh - 1, buf, \
			&g_catsbane.idle);
		else
		{
			if (!rdata->catsbanetimer.tv_sec)
			{
				gettimeofday(&rdata->catsbanetimer, NULL);
				g_player.attack = 1;
			}
			yput_to_buffer((g_config.screenw / 2) - g_catsbane.idle.texw / 2, \
			g_config.screenh - g_catsbane.idle.texh - 1, buf, \
			&g_catsbane.attack);
			if (msec_diff(&rdata->catsbanetimer, NULL) > 500)
			{
				g_keydata.enter = 0;
				g_player.attack = 0;
				reset_timer(&rdata->catsbanetimer);
			}
		}
	}
}

void	refreshchisme(unsigned int *buf, t_raycasterdata *rdata)
{
	static int	bit = 0;

	if (g_player.inventory.chisme)
	{
		if (g_framedata.secretwallcompass < 20)
			yput_to_buffer(g_config.screenw - g_chisme.idle.texw - 1, \
			g_config.screenh - g_chisme.idle.texh - 1, buf, g_chisme.ptr[0]);
		else
		{
			if (!rdata->chismetimer.tv_sec)
				gettimeofday(&rdata->chismetimer, NULL);
			if (msec_diff(&rdata->chismetimer, NULL) > \
			(60 * g_config.screenw) / g_framedata.secretwallcompass)
			{
				bit ^= 1;
				reset_timer(&rdata->chismetimer);
			}
			yput_to_buffer(g_config.screenw - g_chisme.idle.texw - 1, \
			g_config.screenh - g_chisme.idle.texh - 1, buf, g_chisme.ptr[bit]);
		}
	}
}

void	refreshrubies(unsigned int *buf)
{
	int	inventory;
	int	i;

	inventory = g_player.inventory.rubies;
	i = 44;
	while (inventory--)
	{
		yput_to_buffer(g_config.screenw - i, 10, buf, &g_ruby);
		i += 44;
	}
}

void	refreshpotions(unsigned int *buf)
{
	int	full;
	int half;
	int empty;
	int	inventory;
	int	i;

	if (g_keydata.ctrl)
		usepotion();
	full = g_player.life / 2;
	half = g_player.life % 2;
	empty = 3 - (full + half);
	i = 0;
	while (full--)
		yput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.fullheart);
	while (half--)
		yput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.halfheart);
	while (empty--)
		yput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.emptyheart);
	i = 0;
	inventory = g_player.inventory.potions;
	while (inventory--)
	{
		yput_to_buffer(i, g_config.screenh - 200, buf, &g_potion);
		i += 25;
	}
}
