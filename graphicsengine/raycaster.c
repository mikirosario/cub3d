/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:45 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/14 20:07:40 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

char	memreserve(void)
{
	char	memerror;

	memerror = 0;
	if (!(g_config.zbuffer = (ft_calloc(g_config.screenW, sizeof(double)))))
		memerror = 1;
	//if (!(g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, \
	//g_config.screenW, g_config.screenH)))
	//	memerror = 1;
	if (g_config.spriteNum && \
	!(g_config.spriteorder = (ft_calloc(g_config.spriteNum, sizeof(int)))))
		memerror = 1;
	if (memerror)
		return (0);
	return(1);
}

/*
** This function is launched before the first frame is built, the first time
** raycaster is called.
**
** Depending on the configured screen width we will reserve the appropriate
** amount of zbuffer space. If there are sprites, we will also reserve memory
** in which to save the sprite order from the player's vantage point at any
** given time/frame. The amount of memory will depend on the number of sprites.
** If either memory reservation fails the program will throw a memory error and
** abort.
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
**
*/

void	start(unsigned int **buf)
{
	spriteData_t	*sprtptr;
	
	if (!(g_config.zbuffer = (ft_calloc(g_config.screenW, sizeof(double)))) || \
	!(g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, \
	g_config.screenW, g_config.screenH)) ||	(g_config.spriteNum && \
	!(g_config.spriteorder = (ft_calloc(g_config.spriteNum, sizeof(int))))))
	{
		ft_printf(REDERROR mallocFail);
		ft_stop(0x0, (void *)0);
	}
	*buf = (unsigned int *)mlx_get_data_addr(g_screenData.mlx_img_buffer, &g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
	g_config.vMove = g_config.spriteH * g_config.vDiv;
	g_blueMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_blueMetalImg.mlx_img, &g_blueMetalImg.bpp, &g_blueMetalImg.size_line, &g_blueMetalImg.endian);
	g_yellowMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_yellowMetalImg.mlx_img, &g_yellowMetalImg.bpp, &g_yellowMetalImg.size_line, &g_yellowMetalImg.endian);
	g_greenMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_greenMetalImg.mlx_img, &g_greenMetalImg.bpp, &g_greenMetalImg.size_line, &g_greenMetalImg.endian);
	g_pinkMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_pinkMetalImg.mlx_img, &g_pinkMetalImg.bpp, &g_pinkMetalImg.size_line, &g_pinkMetalImg.endian);
	sprtptr = g_config.spriteList;
	while (sprtptr)
	{
		if (sprtptr->spriteType == '2') //asigna textura en función de sprite type
			sprtptr->texture = (unsigned int *)mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, &g_normiImg.size_line, &g_normiImg.endian);
		sprtptr = sprtptr->next;
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
** We get its address after the 
*/

int   ft_raycaster(int key, void *param)
{
	int x;
	static unsigned int *buf = NULL;
	static time_t seconds = 0; //ILLEGAL!
	time_t endTime; //ILLEGAL! Mi fpscounter.. Sniff.
	static int fps = 0; //FPS
	static int printFPS = 0; //FPS
	//static char stayout = 0;

	(void)param;
	(void)key;

	if (!seconds) //FPS
		seconds = time(NULL); //FPS
	x = 0;
	
	if (!buf)
		start(&buf);

	while (x < g_config.screenW)
	{
		castray(x);
		calculateframeline();
		drawframeline(x, buf);
		//set zBuffer for sprite casting
		g_config.zbuffer[x] = g_rayData.perpWallDist; //perpendicular distances to walls from camera
		x++;
	}
	//Sprite Casting
	castsprites(buf);

	//print image
	mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_screenData.mlx_img_buffer, 0, 0);
	
	readmovementkeys();

	//framecounter
	fps++;
	if ((endTime = time(NULL) != seconds))
	{
		//printf("%d, ", fps);
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 80, 0x0000ff00, ft_itoa(fps));
		printFPS = fps;
		seconds = 0;
		fps = 0;
	}
	else
	{
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 80, 0x0000ff00, ft_itoa(printFPS));       
	}

	//printf("%f, ", time_used);
	if (g_keyData.m == 0)
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 0 Grafx");
	else if (g_keyData.m == 1)
		mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 1 Grafx");
	else if (g_keyData.m == 2)
			mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 2 Grafx");
	return (0);
}