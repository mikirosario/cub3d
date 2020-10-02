/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeme_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:15 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/02 17:51:21 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

void	destroyobjectimages(void)
{
	int	i;

	i = 0;
	while (i < 3 && g_lifebar.ptr[i] && g_lifebar.ptr[i]->mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, \
		g_lifebar.ptr[i++]->mlx_img);
	i = 0;
	while (i < 2 && g_catsbane.ptr[i] && g_catsbane.ptr[i]->mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, \
		g_catsbane.ptr[i++]->mlx_img);
	i = 0;
	while (i < 2 && g_chisme.ptr[i] && g_chisme.ptr[i]->mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, \
		g_chisme.ptr[i++]->mlx_img);
}

/*
** This function handles the new imagedata structs, that may hold animation
** frames, destroying all created images. In this version it also handles the
** freeing of file paths, which are now stored in the texpaths array at the
** root image.
*/

void	destroyimages(t_imagedata *image)
{
	int i;

	i = 0;
	if (image->mlx_img)
	{
		while (i < 8 && image->animation[i])
		{
			if (image->animation[i]->mlx_img)
				mlx_destroy_image(g_screendata.mlx_ptr, \
				image->animation[i]->mlx_img);
			i++;
		}
		mlx_destroy_image(g_screendata.mlx_ptr, image->mlx_img);
	}
	i = 0;
	while (i < 8 && image->texpaths[i])
		del(image->texpaths[i++]);
}

/*
** This function will free all memory used by linked lists, including content.
** Also frees associated arrays.
*/

void	freelists(void)
{
	if (g_config.maplist)
		freelist(&g_config.maplist);
	if (g_config.map)
		del(g_config.map);
	if (g_config.spritelist)
		freesprtlist(&g_config.spritelist);
	if (g_config.sprt)
		del(g_config.sprt);
}

/*
** This function will destroy any wall or sprite images created, as well as the
** image buffer used to assemble frames before printing them.
*/

void	freeimgs(void)
{
	if (g_screendata.mlx_img_buffer)
		mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
	destroyimages(&g_nowallimg);
	destroyimages(&g_sowallimg);
	destroyimages(&g_wewallimg);
	destroyimages(&g_eawallimg);
	destroyimages(&g_sprt2img);
	destroyimages(&g_sprt3img);
	destroyimages(&g_sprt4img);
	destroyimages(&g_sprt5img);
	destroyimages(&g_sprt6img);
	destroyimages(&g_sprt7img);
	destroyimages(&g_sprt8img);
	destroyimages(&g_sprt9img);
	destroyimages(&g_floorimg);
	destroyimages(&g_ceilingimg);
	destroyimages(&g_potion);
	destroyimages(&g_ruby);
	destroyimages(&g_portal);
	destroyimages(&g_phrases);
	destroyobjectimages();
}

/*
** This function will check for the existence of any memory the program would
** normally reserve during runtime and free it, including for windows, linked
** lists and strings. As it checks before freeing it can be used at at any
** point in the program. Not really needed before exit, but in future I might
** want to do an exit to menu option or something from my stop function, so
** I have my freeme ready for that. :)
*/

void	freeme(void)
{
	if (g_screendata.mlx_ptr)
	{
		if (!g_screendata.mlx_win)
			del(g_screendata.mlx_ptr);
		else
		{
			freeimgs();
			mlx_destroy_window(g_screendata.mlx_ptr, g_screendata.mlx_win);
			del(g_screendata.mlx_ptr);
		}
	}
	freelists();
	if (g_config.spriteorder)
		del(g_config.spriteorder);
	if (g_config.zbuffer)
		del(g_config.zbuffer);
	if (g_config.musicpid)
		kill(g_config.musicpid, 15);
	system("stty sane");
}
