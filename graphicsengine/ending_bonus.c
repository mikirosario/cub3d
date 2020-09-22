/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 03:00:07 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/22 05:15:01 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** Sound attribution for ending fanfare:
** eardeer, freesound.org.
*/

void	endingsounds(int frame)
{
	static char	stayout = 0;

	if (!stayout)
	{
		if (g_config.musicpid)
			kill(g_config.musicpid, 15);
		g_config.musicpid = 0;
		playsound(END);
		stayout = 1;
	}
	if (frame == 6 && stayout == 1)
	{
		stayout = 2;
		playsound(MEOW);
	}
}

/*
** Music
** "Into Battle" by Eric Matyas
** www.soundimage.org
*/

void	bossmusic(char spritetype)
{
	static char stayout = 0;

	if (!stayout && spritetype == '2')
	{
		if (g_config.musicpid)
			kill(g_config.musicpid, 15);
		g_config.musicpid = fork();
		if (!g_config.musicpid)
			playtrack(BOSS_THEME);
		stayout = 1;
	}
}

void	playending(t_raycasterdata *rdata)
{
	static int	i = 0;

	endingsounds(i);
	yput_to_buffer((g_config.screenw / 2 - g_ending.texw / 2) - 1, \
	(g_config.screenh / 2 - g_ending.texh / 2) - 1, rdata->buf, \
	g_ending.animation[i]);
	if (msec_diff(&rdata->endingtimer, NULL) > 2000)
	{
		i++;
		gettimeofday(&rdata->endingtimer, NULL);
	}
	if (i == 7)
		ft_stop(0, (void *)0);
	mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, \
	g_screendata.mlx_img_buffer, 0, 0);
}

void	teleport(void)
{
		g_player.posx = 29.5;
		g_player.posy = 18.2;
		g_player.dirx = (double)0;
		g_player.diry = (double)-1;
		g_player.planex = (double)0.66;
		g_player.planey = (double)0;
}

/*
** What happens when you beat the fearsome Norminette?
*/

void	ending(t_raycasterdata *rdata)
{
	static char	stayout = 0;

	if (!stayout)
	{
		teleport();
		stayout = 1;
		gettimeofday(&rdata->endingtimer, NULL);
	}
	else
		playending(rdata);
}
