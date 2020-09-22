/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 18:51:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];

void	refreshui(unsigned int *buf, t_raycasterdata *rdata)
{
	refreshpotions(buf);
	refreshrubies(buf);
	refreshchisme(buf, rdata);
	refreshcatsbane(buf, rdata);
}

void	gameloop(t_raycasterdata *rdata, time_t *timestart)
{
	if (g_config.screenshot)
		screenshot(rdata->buf);
	refreshui(rdata->buf, rdata);
	displayspeech(rdata);
	mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, \
	g_screendata.mlx_img_buffer, 0, 0);
	displaygraphicsmode();
	countframes(timestart);
}

void	endingloop(t_raycasterdata *rdata)
{
	if (g_config.ending == 1)
	{
		if (!rdata->endingtimer.tv_sec)
			gettimeofday(&rdata->endingtimer, NULL);
		else if (msec_diff(&rdata->endingtimer, NULL) > 2000)
			g_config.ending = 2;
	}
	else if (g_config.ending == 2)
		ending(rdata);
}

/*
** X will be used to describe each pixel position on a given screen line, from
** 0 to screen width.
**
** The start sequence will set up the parameters and reserve the memory we need
** before the first frame is built. It will assign an image buffer, so if there
** is no image buffer it has not yet been run; if there is, then it has.
**
** buf points to the a minilibx image space the size and width of the screen
** where we will build the image every frame before dumping it onto the screen.
**
** Then we evaluate key presses to determine movement and other game
** interactions.
*/

int		raycaster_bonus(t_raycasterdata *rdata)
{
	static time_t		timestart = 0;

	rdata->portalvisible = 0;
	g_framedata.secretwallcompass = 0;
	if (!timestart)
		timestart = time(NULL);
	if (g_framedata.invincibilityframes)
		g_framedata.invincibilityframes--;
	if (g_keydata.m != 2)
		cast_ceiling_floor(rdata->buf);
	castwall(rdata);
	castsprites(rdata->buf);
	castdoors(rdata);
	if (g_config.ending < 2)
		gameloop(rdata, &timestart);
	if (g_config.ending)
		endingloop(rdata);
	readmovementkeys();
	return (0);
}
