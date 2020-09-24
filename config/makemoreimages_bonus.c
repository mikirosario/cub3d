/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemoreimages_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:45:33 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/24 17:44:36 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_imagedata *g_simg[10];

/*
** I check for the existence of all image paths passed by the user in a function
** called checkimgs. I do a bad thing and don't check for the validity of my own
** files, so if you move or rename them you will crash the program ungracefully.
*/

void	sethudobjectpointers(void)
{
	g_lifebar.ptr[0] = &g_lifebar.fullheart;
	g_lifebar.ptr[1] = &g_lifebar.halfheart;
	g_lifebar.ptr[2] = &g_lifebar.emptyheart;
	g_catsbane.ptr[0] = &g_catsbane.idle;
	g_catsbane.ptr[1] = &g_catsbane.attack;
	g_chisme.ptr[0] = &g_chisme.idle;
	g_chisme.ptr[1] = &g_chisme.active;
}

void	createhudimages(void)
{
	g_lifebar.fullheart.mlx_img = \
	mlx_xpm_file_to_image(g_screendata.mlx_ptr, "./uielements/fullheart.xpm", \
	&g_lifebar.fullheart.texw, &g_lifebar.fullheart.texh);
	g_lifebar.halfheart.mlx_img = \
	mlx_xpm_file_to_image(g_screendata.mlx_ptr, "./uielements/halfheart.xpm", \
	&g_lifebar.halfheart.texw, &g_lifebar.halfheart.texh);
	g_lifebar.emptyheart.mlx_img = \
	mlx_xpm_file_to_image(g_screendata.mlx_ptr, "./uielements/emptyheart.xpm", \
	&g_lifebar.emptyheart.texw, &g_lifebar.emptyheart.texh);
	g_potion.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/uipotion.xpm", &g_potion.texw, &g_potion.texh);
	g_catsbane.idle.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr,
	"./uielements/uispray1.xpm", &g_catsbane.idle.texw, &g_catsbane.idle.texh);
	g_catsbane.attack.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr,
	"./uielements/uispray2.xpm", &g_catsbane.attack.texw, \
	&g_catsbane.attack.texh);
	g_ruby.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/ruby.xpm", &g_ruby.texw, &g_ruby.texh);
	g_chisme.idle.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/chisme1.xpm", &g_chisme.idle.texw, &g_chisme.idle.texh);
	g_chisme.active.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/chisme2.xpm", &g_chisme.active.texw, &g_chisme.active.texh);
	sethudobjectpointers();
}

void	getbonussprites(void)
{
	int i;

	i = g_config.sprtexnum;
	if (g_config.spritenum)
		while (i > 1)
		{
			g_simg[i]->mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
			g_simg[i]->texpaths[0], &g_simg[i]->texw, &g_simg[i]->texh);
			if (&g_simg[i]->texpaths[1])
				getanimationimgs(g_simg[i]);
			i--;
		}
}

void	getbonusteximg(void)
{
	g_floorimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_floorimg.texpath, &g_floorimg.texw, &g_floorimg.texh);
	g_ceilingimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_ceilingimg.texpath, &g_ceilingimg.texw, &g_ceilingimg.texh);
	g_doorrightimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"doorright.XPM", &g_doorrightimg.texw, &g_doorrightimg.texh);
	g_doorleftimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"doorleft.XPM", &g_doorleftimg.texw, &g_doorleftimg.texh);
	g_portal.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./portalanimation/portal1.xpm", &g_portal.texw, &g_portal.texh);
	g_phrases.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./textboxes/orenline1.xpm", &g_phrases.texw, &g_phrases.texh);
	g_ending.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./textboxes/ending1.xpm", &g_ending.texw, &g_ending.texh);
	g_skybox.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./skybox.xpm", &g_skybox.texw, &g_skybox.texh);
}
