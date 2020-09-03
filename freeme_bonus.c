/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeme_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:15 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/03 17:43:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Free bonus images.
*/

void	freebonusimgs(void)
{
	int i;

	if (g_sprt3img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt3img.mlx_img);
	if (g_sprt4img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt4img.mlx_img);
	if (g_sprt5img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt5img.mlx_img);
	if (g_sprt6img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt6img.mlx_img);
	if (g_sprt7img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt7img.mlx_img);
	if (g_sprt8img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt8img.mlx_img);
	if (g_sprt9img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt9img.mlx_img);
	if (g_floorimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_floorimg.mlx_img);
	if (g_ceilingimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_ceilingimg.mlx_img);
	i = 0;
	while (i < 3)
	{
		if (g_lifebar.ptr[i] && g_lifebar.ptr[i]->mlx_img)
			mlx_destroy_image(g_screendata.mlx_ptr, g_lifebar.ptr[i]->mlx_img);
		i++;
	}
		
}

/*
** This function will free all strings reserved to store file path data
** retrieved during cub file configuration.
*/

void	freestrings(void)
{
	if (g_floorimg.texpath)
		del(g_floorimg.texpath);
	if	(g_ceilingimg.texpath)
		del(g_ceilingimg.texpath);
	if (g_nowallimg.texpath)
		del(g_nowallimg.texpath);
	if (g_sowallimg.texpath)
		del(g_sowallimg.texpath);
	if (g_wewallimg.texpath)
		del(g_wewallimg.texpath);
	if (g_eawallimg.texpath)
		del(g_eawallimg.texpath);
	if (g_sprt2img.texpath)
		del(g_sprt2img.texpath);
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
		del (g_config.sprt);
}

/*
** This function will destroy any wall or sprite images created, as well as the
** image buffer used to assemble frames before printing them.
*/

void	freeimgs(void)
{
	if (g_screendata.mlx_img_buffer)
		mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
	if (g_nowallimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_nowallimg.mlx_img);
	if (g_sowallimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sowallimg.mlx_img);
	if (g_wewallimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_wewallimg.mlx_img);
	if (g_eawallimg.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_eawallimg.mlx_img);
	if (g_sprt2img.mlx_img)
		mlx_destroy_image(g_screendata.mlx_ptr, g_sprt2img.mlx_img);
	freebonusimgs();
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
			mlx_destroy_window(g_screendata.mlx_ptr, g_screendata.mlx_win);
			freeimgs();
			del(g_screendata.mlx_ptr);
		}
	}
	freelists();
	freestrings();
	if (g_config.spriteorder)
		del(g_config.spriteorder);
	if (g_config.zbuffer)
		del(g_config.zbuffer);
}
