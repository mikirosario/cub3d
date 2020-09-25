/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbonusimgaddresses_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:51:23 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/25 19:39:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];

int		getanimationptrs(t_spritedata *sprt, t_imagedata *simg)
{
	int	i;

	i = 1;
	while (i < 8 && simg->animation[i])
	{
		if (!(sprt->animtex[i] = \
		(unsigned int *)mlx_get_data_addr(simg->animation[i]->mlx_img, \
		&simg->animation[i]->bpp, &simg->animation[i]->size_line, \
		&simg->animation[i]->endian)))
			return (0);
		i++;
	}
	sprt->framelimit = i - 1;
	return (1);
}

void	getalltexpointers(t_imagedata *img, int animations)
{
	int	i;

	i = 0;
	img->tex_ptr = (unsigned int *)mlx_get_data_addr(img->mlx_img, \
	&img->bpp, &img->size_line, &img->endian);
	while (i < animations)
	{
		img->animation[i]->tex_ptr = \
		(unsigned int *)mlx_get_data_addr(img->animation[i]->mlx_img, \
		&img->animation[i]->bpp, &img->animation[i]->size_line, \
		&img->animation[i]->endian);
		i++;
	}
}

/*
** You know how it is... you know how it is... ;)
*/

void	loadmoreui(void)
{
	g_chisme.idle.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_chisme.idle.mlx_img, \
	&g_chisme.idle.bpp, &g_chisme.idle.size_line, &g_chisme.idle.endian);
	g_chisme.active.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_chisme.active.mlx_img, \
	&g_chisme.active.bpp, &g_chisme.active.size_line, &g_chisme.active.endian);
	g_potion.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_potion.mlx_img, \
	&g_potion.bpp, &g_potion.size_line, &g_potion.endian);
	g_ruby.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_ruby.mlx_img, &g_ruby.bpp, \
	&g_ruby.size_line, &g_ruby.endian);
}

void	loadui(void)
{
	t_lifebar	*b;
	t_catsbane	*w;

	b = &g_lifebar;
	b->fullheart.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(b->fullheart.mlx_img, \
	&b->fullheart.bpp, &b->fullheart.size_line, &b->fullheart.endian);
	b->halfheart.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(b->halfheart.mlx_img, \
	&b->halfheart.bpp, &b->halfheart.size_line, &b->halfheart.endian);
	b->emptyheart.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(b->emptyheart.mlx_img, \
	&b->emptyheart.bpp, &b->emptyheart.size_line, &b->emptyheart.endian);
	w = &g_catsbane;
	w->idle.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(w->idle.mlx_img, &w->idle.bpp, \
	&w->idle.size_line, &w->idle.endian);
	w->attack.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(w->attack.mlx_img, &w->attack.bpp, \
	&w->attack.size_line, &w->attack.endian);
	loadmoreui();
}

void	getbonusimgaddresses(t_raycasterdata *rdata)
{
	g_floorimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_floorimg.mlx_img, \
	&g_floorimg.bpp, &g_floorimg.size_line, &g_floorimg.endian);
	g_ceilingimg.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_ceilingimg.mlx_img, \
	&g_ceilingimg.bpp, &g_ceilingimg.size_line, &g_ceilingimg.endian);
	g_doorrightimg.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_doorrightimg.mlx_img, \
	&g_doorrightimg.bpp, &g_doorrightimg.size_line, &g_doorrightimg.endian);
	g_doorleftimg.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_doorleftimg.mlx_img, \
	&g_doorleftimg.bpp, &g_doorleftimg.size_line, &g_doorleftimg.endian);
	g_skybox.tex_ptr = (unsigned int *)mlx_get_data_addr(g_skybox.mlx_img, \
	&g_skybox.bpp, &g_skybox.size_line, &g_skybox.endian);
	rdata->skyboxsidewidth = g_skybox.texw / 4;
}
