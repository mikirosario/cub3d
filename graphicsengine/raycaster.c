/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/25 20:06:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

void	loadsprites(void)
{
	spriteData_t	*sprtptr;

	sprtptr = g_config.spriteList;
	while (sprtptr)
	{
		if (sprtptr->spriteType == '2')
			sprtptr->texture = (unsigned int *)\
			mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, \
			&g_normiImg.size_line, &g_normiImg.endian);
		sprtptr = sprtptr->next;
	}
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

char	memreserve(void)
{
	char	memerror;

	memerror = 0;
	if (!(g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, \
	g_config.screenW, g_config.screenH)))
		memerror = 1;
	if (g_config.spriteNum && \
	(!(g_config.zbuffer = (ft_calloc(g_config.screenW, sizeof(double)))) ||
	!(g_config.spriteorder = (ft_calloc(g_config.spriteNum, sizeof(int))))))
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
** g_config.vMove controls the vertical position of the sprite on
** screen. It is defined within the raycaster as being equal to the height of
** the sprite times vDiv (g_config.spriteH * g_config.vDiv). This will always
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

void	start(unsigned int **buf)
{
	if (!memreserve())
	{
		ft_printf(RED"\nError\n"RESET mallocFail);
		ft_stop(0x0, (void *)0);
	}
	*buf = (unsigned int *)mlx_get_data_addr(g_screenData.mlx_img_buffer, \
	&g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
	g_config.vMove = g_config.spriteH * g_config.vDiv;
	nowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(nowallimg.mlx_img, \
	&nowallimg.bpp, &nowallimg.size_line, &nowallimg.endian);
	sowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(sowallimg.mlx_img, \
	&sowallimg.bpp, &sowallimg.size_line, &sowallimg.endian);
	wewallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(wewallimg.mlx_img, \
	&wewallimg.bpp, &wewallimg.size_line, &wewallimg.endian);
	eawallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(eawallimg.mlx_img, \
	&eawallimg.bpp, &eawallimg.size_line, &eawallimg.endian);
	loadsprites();
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

int		raycaster(int key, void *param)
{
	static unsigned int	*buf = NULL;
	int					x;

	(void)param;
	(void)key;
	x = 0;
	if (!buf)
		start(&buf);
	while (x < g_config.screenW)
	{
		castray(x);
		calculateframeline();
		drawframeline(x, buf);
		if (g_config.spriteNum)
			g_config.zbuffer[x] = g_rayData.perpWallDist;
		x++;
	}
	castsprites(buf);
	mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, \
	g_screenData.mlx_img_buffer, 0, 0);
	if (g_config.screenshot)
		screenshot(buf);
	readmovementkeys();
	return (0);
}
