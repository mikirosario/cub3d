/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/14 14:46:16 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];

/*
** This function will draw lines of pixels to the buffer starting at the x, y
** position passed as arguments, from top to bottom row by row, excluding
** transparent colors. Note that on MAC this seems to be marked by making the
** A channel 00, and on Linux by making it FF. :p I don't know why that is.
**
** It's unprotected, so make sure your image will fit into your buffer. :p
*/

void	xput_to_buffer(int x, int y, unsigned int *buf, t_imagedata *img)
{
	int bx;
	int	tx;
	int	ty;

	ty = 0;
	while (ty < img->texh - 1)
	{
		bx = x + (y * g_config.screenw);
		tx = ty * img->texw;
		while (tx < ty * img->texw + img->texw)
		{
			if (img->tex_ptr[tx] != 0xff000000)
				buf[bx] = img->tex_ptr[tx];
			bx++;
			tx++;
		}
		y++;
		ty++;
	}
}

/*
** Like xput_to_buffer, but draws lines vertically column by column instead of
** horizontally row by row.
*/

void	yput_to_buffer(int x, int y, unsigned int *buf, t_imagedata *img)
{
	int bx;
	int	tx;
	int	ty;

	tx = 0;
	while (tx < img->texw)
	{
		bx = x + y * g_config.screenw;
		ty = tx;
		while (ty < tx + img->texh * img->texw)
		{
			if (img->tex_ptr[ty] != 0xff000000)
				buf[bx] = img->tex_ptr[ty];
			bx += g_config.screenw;
			ty += img->texw;
		}
		x++;
		tx++;
	}
}

int		usepotion(void)
{
	if (g_player.inventory && g_player.life < 6)
	{
		g_player.inventory--;
		g_player.life++;
		return (1);
	}
	return (0);
}

void	refreshui(unsigned int *buf)
{
	int	full;
	int half;
	int empty;
	int	inventory;
	int	i;

	if (g_keydata.ctrl)
	{
		usepotion();
		g_keydata.ctrl = 0;
	}
	//ft_printf("%d\n", g_keydata.w);
	full = g_player.life / 2;
	half = g_player.life % 2;
	empty = 3 - (full + half);
	i = 0;
	while (full--)
		xput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.fullheart);
	while (half--)
		xput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.halfheart);
	while (empty--)
		xput_to_buffer((10 + 36) * i++, 10, buf, &g_lifebar.emptyheart);
	i = 300;
	inventory = g_player.inventory;
	while (inventory--)
	{
		xput_to_buffer(g_config.screenw - i, g_config.screenh - 200, buf, &g_potion);
		i -= 25;
	}
}

void	activatedoor(void)
{
	char	mapchr;
	int		i;

	g_keydata.sp = 0;
	i = 0;
	castoneray((g_config.screenw - 1) / 2);
	if ((mapchr = g_config.map[g_raydata.mapy][g_raydata.mapx]) == '-' || mapchr == '|' || mapchr == 'O')
		if (g_raydata.perpwalldist < 0.45)
		{
			while (g_config.door[i]->dooraddr != &g_config.map[g_raydata.mapy][g_raydata.mapx])
				i++;
			g_config.door[i]->doorend = g_config.door[i]->doorend == 0 ? 0.8 : 0;
			if (mapchr == g_config.door[i]->spritetype)
				g_config.map[g_raydata.mapy][g_raydata.mapx] = 'O';
			else
				g_config.map[g_raydata.mapy][g_raydata.mapx] = g_config.door[i]->spritetype;
		}
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
	int					x;
	static time_t		timestart = 0;

	x = 0;
	if (!timestart)
		timestart = time(NULL);
	if (g_framedata.invincibilityframes)
			g_framedata.invincibilityframes--;
	if (g_keydata.m != 2)
		cast_ceiling_floor(rdata->buf);
	while (x < g_config.screenw)
	{
		castray(x);
		calculateframeline();
		drawframeline(x, rdata->buf);
		if (g_config.spritenum)
			g_config.zbuffer[x] = g_raydata.perpwalldist;
		x++;
	}
	castsprites(rdata->buf);
	if (g_keydata.sp)
		activatedoor();
	refreshui(rdata->buf);
	mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, \
	g_screendata.mlx_img_buffer, 0, 0);
	if (g_config.screenshot)
		screenshot(rdata->buf);
	readmovementkeys();
	//other key presses (inventory, menu, etc.) here
	countframes(&timestart);
	displaygraphicsmode();
	return (0);
}
