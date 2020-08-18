/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeme.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:15 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/18 19:50:02 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function will free all strings reserved to store file path data
** retrieved during cub file configuration.
*/

void	freestrings(void)
{
	if (nowallimg.texpath)
		del(nowallimg.texpath);
	if (sowallimg.texpath)
		del(sowallimg.texpath);
	if (wewallimg.texpath)
		del(wewallimg.texpath);
	if (eawallimg.texpath)
		del(eawallimg.texpath);
	if (g_normiImg.texpath)
		del(g_normiImg.texpath);
}

/*
** This function will free all memory used by linked lists, including content.
*/

void	freelists(void)
{
	if (g_config.Map)
		freelist(&g_config.Map);
	if (g_config.map)
		del(g_config.map);
	if (g_config.spriteList)
		freesprtlist(&g_config.spriteList);
}

/*
** This function will destroy any wall or sprite images created, as well as the
** image buffer used to assemble frames before printing them.
*/

void	freeimgs(void)
{
	if (g_screenData.mlx_img_buffer)
		mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
	if (nowallimg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, nowallimg.mlx_img);
	if (sowallimg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, sowallimg.mlx_img);
	if (wewallimg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, wewallimg.mlx_img);
	if (eawallimg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, eawallimg.mlx_img);
	if (g_normiImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_normiImg.mlx_img);
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
	if (g_screenData.mlx_ptr)
	{
		if (!g_screenData.mlx_win)
			del(g_screenData.mlx_ptr);
		else
		{
			mlx_destroy_window(g_screenData.mlx_ptr, g_screenData.mlx_win);
			freeimgs();
			del(g_screenData.mlx_ptr);
		}
	}
	freelists();
	freestrings();
	if (g_config.spriteorder)
		del(g_config.spriteorder);
	if (g_config.zbuffer)
		del(g_config.zbuffer);
}
