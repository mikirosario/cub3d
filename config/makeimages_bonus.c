/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeimages_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:36:40 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/01 20:07:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];

int		createhudimages(void)
{
	g_lifebar.ptr[0] = &g_lifebar.fullheart;
	g_lifebar.ptr[1] = &g_lifebar.halfheart;
	g_lifebar.ptr[2] = &g_lifebar.emptyheart;
	if (!(g_lifebar.fullheart.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/fullheart.xpm", &g_lifebar.fullheart.texw, &g_lifebar.fullheart.texh)))
		return (0);
	else if (!(g_lifebar.halfheart.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/halfheart.xpm", &g_lifebar.halfheart.texw, &g_lifebar.halfheart.texh)))
		return (0);
	else if (!(g_lifebar.emptyheart.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	"./uielements/emptyheart.xpm", &g_lifebar.emptyheart.texw, &g_lifebar.emptyheart.texh)))
		return (0);
	return (1);
}

/*
** The variable g_config.sprtexnum states the highest sprite type number for
** which the user provided a path, so if there are any sprite types in our
** sprite list higher than that number, we know they don't have an image
** because none was ever provided by the user.
**
** The variable i states the lowest sprite type number for which an image was
** successfully loaded, so if there are any sprite types in our sprite list
** lower than that number, we know they don't have an image because, even
** though the user did provide one, the path was bad.
**
** The former will trigger a shiny, brand-spanking-new bonus error called
** orphansprites, which signals sprites without an image. Since I'm on a bit of
** a bitshifting kick, and exactly eight different sprites happen to be
** loadable in my game, I encode every sprite type that threw an error bitwise
** in the orphansprite variable so I can use it to inform the user which
** sprites are orphaned in their map. This will be << spritetype - 50, because
** remember we start our types with the ASCII digit 2, so 2 will be 0 bits
** shifted, 3 will be 1 bit shifted, etc.
**
** The latter will trigger ye olde bad path error. Do not declare sprites
** without an image, kids. It's just plain mean.
*/

int		checkimgs(void)
{
	int	i;
	t_spritedata *s;

	s = g_config.spritelist;
	while (s)
	{
		if (s->spritetype > g_config.sprtexnum + 48)
			g_iamerror.orphansprites |= (char)00000001 << (s->spritetype - 50);
		s = s->next;
	}
	i = g_config.sprtexnum;
	while (i > 1)
		if (!(*g_simg[i--]).mlx_img)
			break ;
	if (!g_nowallimg.mlx_img || !g_sowallimg.mlx_img || !g_wewallimg.mlx_img ||
	!g_eawallimg.mlx_img || !g_floorimg.mlx_img || !g_ceilingimg.mlx_img ||
	(i != 1 && g_config.spritenum))
		g_iamerror.texpathfail = 1;
	return (g_iamerror.orphansprites || g_iamerror.texpathfail ? 0 : 1);
}
/*
** This function compares the first retrieved wall texture resolution (for the
** north wall) with all other wall texture resolutions. If ANY of them are
** different, we throw a UN Security Council Breach error and abort the
** program. Yeah, I'm pretty serious about this requirement - the texture sizes
** of all the walls MUST match. It just looks horrible if they don't! xD
*/

int		comptexres(int *firstwallsize)
{
	t_imagedata	*texpath[5];
	int		i;

	texpath[0] = &g_sowallimg;
	texpath[1] = &g_wewallimg;
	texpath[2] = &g_eawallimg;
	texpath[3] = &g_floorimg;
	texpath[4] = &g_ceilingimg;
	i = 0;
	while (i < 5)
	{
		if (firstwallsize[0] == (texpath[i])->texw && firstwallsize[1] == (texpath[i]->texh))
			i++;
		else
			break ;
	}
	if (i < 5)
		g_iamerror.walltexsizedif = 1;
	return (i == 5 ? 1 : 0);
}

/*
** This hideous-looking block of Normed code is very simple. It just tries to
** convert all the XPM files provided by the user into mlx_img strings that
** minilibx can use. We use the paths we retrieved from the cub file, and
** we save the address of the resulting image at .mlx_img in the respective
** texture struct.
**
** We only try to create a sprite texture image if there are sprites in the
** map.
**
** When we're done, we check to see if we were successful. If any of the
** images are not created successfully, the pointers to them will be NULL.
** Again, we're only interested in the sprite image pointer if there are
** sprites on the map. If any of the pointers are NULL, we return 0 to
** indicate that we've failed to create all the images we'll need for
** the raycaster to run. If we succeed, we return 1 to tell the calling
** function to carry on.
**
** We NEVER want to go through THIS again, so we'll use the texpathfail flag
** to remember the result of all these checks in the future. xD
*/

int		getteximg(void)
{
	int i;

	i = g_config.sprtexnum;
	g_floorimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_floorimg.texpath, &g_floorimg.texw, &g_floorimg.texh);
	g_ceilingimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_ceilingimg.texpath, &g_ceilingimg.texw, &g_ceilingimg.texh);
	g_nowallimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_nowallimg.texpath, &g_nowallimg.texw, &g_nowallimg.texh);
	g_sowallimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_sowallimg.texpath, &g_sowallimg.texw, &g_sowallimg.texh);
	g_wewallimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_wewallimg.texpath, &g_wewallimg.texw, &g_wewallimg.texh);
	g_eawallimg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
	g_eawallimg.texpath, &g_eawallimg.texw, &g_eawallimg.texh);
	if (g_config.spritenum)
		while (i > 1)
		{
			(*g_simg[i]).mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
			(*g_simg[i]).texpath, &(*g_simg[i]).texw, &(*g_simg[i]).texh);
			i--;
		}
	return (checkimgs());
}

/*
** This function will attempt to create texture images in minilibx from the
** user-provided XPM files. One texture image will be created for each wall
** face (north, south, east and west). If the map has sprites, then a texture
** will also be created from the user-provided sprite texture XPM file. This
** is done in the getteximg function.
**
** If the attempt to get the texture images fails (the minilibx XPM file to
** image function returns a NULL pointer) for any of the required textures,
** the function will return 0. We will assume in this case that the problem
** is because the path provided by the user is wrong or no valid XPM file can
** be found at that location. It is not necessary to record this error
** explicitly, as the iamerror.c functions will check whether the image
** are NULL or not to determine whether it took place.
**
** If the XPM files were all successfully converted to minililbx images by
** getteximg, then -- so! I actually wrote a function to parse the XPM files
** and find the texture before I realized that mlx_file_to_image does that
** work for me already. Damn it! I'm so used to being up a creek without a
** paddle at 42 School I didn't even hesitate to jump to the conclusion that
** I'd have to parse the image to find the resolution myself. xD Since that
** fuctionality is handled by minilibx, and I find it convenient for getting
** different resolutions for different sprites in the bonus, I am using that
** here. You can find my original crazy parsing function in the standard
** makeimages.c file. xD
**
** The comptexres function will compare the texture sizes for the wall, ceiling
** and floor files and confirm that they all share the same width and height.
** If any do not share the same width or height, we will terminate with a UN
** Security Council red error. I am extreme about this requirement. ;)
*/

int		maketeximg(void)
{
	int	size[2];

	if (!getteximg())
		return (0);
	else
	{
		size[0] = g_nowallimg.texw;
		size[1] = g_nowallimg.texh;
	}
	if (!(comptexres(size)))
		return (0);
	g_config.texw = size[0];
	g_config.texh = size[1];
	createhudimages();
	return (1);
}
