/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/02 20:19:22 by mrosario         ###   ########.fr       */
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

void	refreshui(unsigned int *buf)
{
	int	full;
	int half;
	int empty;
	int	i;

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
	xput_to_buffer(g_config.screenw - 200, g_config.screenh - 200, buf, &g_potion);
}

/*
** Upon starting the raycaster for the first time, we need to reserve memory
** for the thing to work. Everything we need to reserve is reserved here.
**
** We need space for the image buffer (where we'll paint each frame before
** dumping it to the screen).
**
** If there are sprites on the map we must also reserve a zbuffer array to
** save the perpendicular distance from each pixel on the player camera plane
** to the first wall in their line of sight (that is, the distance along the
** z-axis or depth), because we will compare these to the distance to the next
** sprite along the same axis to determine whether each line of sprite should
** or should not be considered hidden behind the wall. We must also reserve
** memory for an array of ints which we'll use to reorder the sprites depending
** on their distances from the player each frame.
**
** If any of these *indispensable* memory allocations fail, we signal memerror
** and abort the program. If they succeed, we merrily carry on.
*/

char	xmemreserve(void)
{
	char	memerror;

	memerror = 0;
	if (!(g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, \
	g_config.screenw, g_config.screenh)))
		memerror = 1;
	if (g_config.spritenum && \
	(!(g_config.zbuffer = (ft_calloc(g_config.screenw, sizeof(double)))) ||
	!(g_config.spriteorder = (ft_calloc(g_config.spritenum, sizeof(int))))))
		memerror = 1;
	if (memerror)
		return (0);
	return (1);
}

/*
** This function is launched before the first frame is built, the first time
** raycaster is called.
**
** We will reserve all the memory we need to run the raycaster using the
** memreserve function, or die trying. If the memreserve fails... well, that0s
** all she wrote. We throw a mallocfail error and abort. Otherwise...
**
** g_config.vmove controls the vertical position of the sprite on
** screen. It is defined within the raycaster as being equal to the height of
** the sprite times vDiv (g_config.spriteh * g_config.vdiv). This will always
** keep the sprites appearing to remain on the ground, regardless of how they
** are resized here, so long as the wall multiplier is 1. It isn't refreshed,
** so you shouldn't fiddle with the values during game time - anyway, they're
** ints, so they aren't very precise. If you change the wall multiplier you'll
** need to fiddle with this to get it right.
**
** We get the wall texture data addresses, casting the char* file that is
** returned by the minilibx function mlx_get_data_addr as unsigned int* to make
** parsing easier (pixel colors are stored in 4 byte RGBT blocks).
**
** Finally, we will also assign each sprite's texture depending on its type.
** For the basic cub3d, there is only one sprite type - '2' - so we only use
** the sprite texture passed by the user for all the sprites. But if you want
** more textures for additional types, you can assign them here. :)
*/

/*void	start(unsigned int **buf)
{
	if (!memreserve())
	{
		ft_printf(RED"%s%s"RESET, REDERROR, MALLOCFAIL);
		ft_stop(0x0, (void *)0);
	}
	*buf = (unsigned int *)mlx_get_data_addr(g_screendata.mlx_img_buffer,
	&g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian);
	g_config.vmove = g_config.spriteh * g_config.vdiv;
	g_floorimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_floorimg.mlx_img, \
	&g_floorimg.bpp, &g_floorimg.size_line, &g_floorimg.endian);
	g_ceilingimg.tex_ptr = (unsigned int *)mlx_get_data_addr( \
	g_ceilingimg.mlx_img, &g_ceilingimg.bpp, &g_ceilingimg.size_line,\
	&g_ceilingimg.endian);
	g_nowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_nowallimg.mlx_img,
	&g_nowallimg.bpp, &g_nowallimg.size_line, &g_nowallimg.endian);
	g_sowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_sowallimg.mlx_img,
	&g_sowallimg.bpp, &g_sowallimg.size_line, &g_sowallimg.endian);
	g_wewallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_wewallimg.mlx_img,
	&g_wewallimg.bpp, &g_wewallimg.size_line, &g_wewallimg.endian);
	g_eawallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_eawallimg.mlx_img,
	&g_eawallimg.bpp, &g_eawallimg.size_line, &g_eawallimg.endian);
	loadsprites();
	loadui();
}*/


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

int		raycaster_bonus(unsigned int *buf)
{
	int					x;
	static time_t		timestart = 0;

	x = 0;
	if (!timestart)
		timestart = time(NULL);
	if (g_framedata.invincibilityframes)
			g_framedata.invincibilityframes--;
	if (g_keydata.m != 2)
		cast_ceiling_floor(buf);
	while (x < g_config.screenw)
	{
		castray(x);
		calculateframeline();
		drawframeline(x, buf);
		if (g_config.spritenum)
			g_config.zbuffer[x] = g_raydata.perpwalldist;
		x++;
	}
	castsprites(buf);
	refreshui(buf);
	mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, \
	g_screendata.mlx_img_buffer, 0, 0);
	if (g_config.screenshot)
		screenshot(buf);
	readmovementkeys();
	//other key presses (inventory, menu, etc.) here
	countframes(&timestart);
	displaygraphicsmode();
	return (0);
}
