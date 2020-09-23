/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_start_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:37:21 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 23:23:18 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];



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

void	loadui(void)
{
	t_lifebar	*b;

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
	g_potion.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_potion.mlx_img, \
	&g_potion.bpp, &g_potion.size_line, &g_potion.endian);
	g_catsbane.idle.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_catsbane.idle.mlx_img, \
	&g_catsbane.idle.bpp, &g_catsbane.idle.size_line, &g_catsbane.idle.endian);
	g_catsbane.attack.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_catsbane.attack.mlx_img, \
	&g_catsbane.attack.bpp, &g_catsbane.attack.size_line, &g_catsbane.attack.endian);
	g_ruby.tex_ptr = (unsigned int *)mlx_get_data_addr(g_ruby.mlx_img, &g_ruby.bpp, \
	&g_ruby.size_line, &g_ruby.endian);
	g_chisme.idle.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_chisme.idle.mlx_img, \
	&g_chisme.idle.bpp, &g_chisme.idle.size_line, &g_chisme.idle.endian);
	g_chisme.active.tex_ptr = \
	(unsigned int *)mlx_get_data_addr(g_chisme.active.mlx_img, \
	&g_chisme.active.bpp, &g_chisme.active.size_line, &g_chisme.active.endian);
	
}

int		loadsprites(void)
{
	t_spritedata	*sprtptr;
	int				stype;

	sprtptr = g_config.spritelist;
	while (sprtptr)
	{
		stype = (sprtptr->spritetype) - 48;
		if (!(sprtptr->animtex[0] = (unsigned int *)
		mlx_get_data_addr(g_simg[stype]->mlx_img, &g_simg[stype]->bpp, \
		&g_simg[stype]->size_line, &g_simg[stype]->endian)))
			return (0);
		sprtptr->texture = sprtptr->animtex[0];
		if (g_simg[stype]->animation[1])
			if (!(getanimationptrs(sprtptr, g_simg[stype])))
				return (0);
		if (sprtptr->spritetype == '4' || sprtptr->spritetype == '7')
		{
			sprtptr->vdiv = 4;
			sprtptr->udiv = 4;
			sprtptr->vmove = (g_config.screenh + (sprtptr->vdiv * g_simg[stype]->texh)) / sprtptr->vdiv; 
			//sprt->vmove = simg->texh * sprt->vdiv;
		}
		if (sprtptr->spritetype == '5')
		{
			sprtptr->vdiv = 4;
			sprtptr->udiv = 3;
			sprtptr->vmove = (g_config.screenh + g_simg[stype]->texh) / sprtptr->vdiv; 
		}
//g_simg[stype]->texh * (sprtptr->vdiv / 2);
		sprtptr = sprtptr->next;
	}
	return (1);
}

int		getimgaddresses(t_raycasterdata *rdata)
{
	rdata->buf = (unsigned int *)mlx_get_data_addr(g_screendata.mlx_img_buffer,
	&g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian); \
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
	g_nowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_nowallimg.mlx_img,
	&g_nowallimg.bpp, &g_nowallimg.size_line, &g_nowallimg.endian);
	g_sowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_sowallimg.mlx_img,
	&g_sowallimg.bpp, &g_sowallimg.size_line, &g_sowallimg.endian);
	g_wewallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_wewallimg.mlx_img,
	&g_wewallimg.bpp, &g_wewallimg.size_line, &g_wewallimg.endian);
	g_eawallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_eawallimg.mlx_img,
	&g_eawallimg.bpp, &g_eawallimg.size_line, &g_eawallimg.endian);
	g_skybox.tex_ptr = (unsigned int *)mlx_get_data_addr(g_skybox.mlx_img, \
	&g_skybox.bpp, &g_skybox.size_line, &g_skybox.endian);
	getalltexpointers(&g_portal, 8);
	getalltexpointers(&g_phrases, 4);
	getalltexpointers(&g_ending, 7);
	loadsprites();
	loadui();
	return (1);
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
	//int		i;

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

int		raycaster_start(t_raycasterdata *rdata)
{
	if (!memreserve() || !getimgaddresses(rdata))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	return (1);
}
