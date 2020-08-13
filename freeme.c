/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeme.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:44:15 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/11 18:01:20 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function will free all strings reserved to store file path data
** retrieved during cub file configuration.
*/

void	freestrings(void)
{
	if (g_blueMetalImg.texPath)
		del(g_blueMetalImg.texPath);
	if (g_yellowMetalImg.texPath)
		del(g_yellowMetalImg.texPath);
	if (g_greenMetalImg.texPath)
		del(g_greenMetalImg.texPath);
	if (g_pinkMetalImg.texPath)
		del(g_pinkMetalImg.texPath);
	if (g_normiImg.texPath)
		del(g_normiImg.texPath);
}

/*
** This function will free all memory used by linked lists, including content.
*/

void	freelists(void)
{
	if (g_config.Map)
		freelist(&g_config.Map);
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
	if (g_blueMetalImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_blueMetalImg.mlx_img);
	if (g_yellowMetalImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_yellowMetalImg.mlx_img);
	if (g_greenMetalImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_greenMetalImg.mlx_img);
	if (g_pinkMetalImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_pinkMetalImg.mlx_img);
	if (g_normiImg.mlx_img)
		mlx_destroy_image(g_screenData.mlx_ptr, g_normiImg.mlx_img);
}

/*
** This function will check for the existence of any memory the program would
** normally reserve during runtime and free it, including for windows, linked
** lists and strings. As it checks before freeing it can be used before exit
** at any point in the program.
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
