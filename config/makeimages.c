/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeimages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:36:40 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 18:19:48 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

/*
** This function retrieves the width and height in pixels (resolution) of the
** an XPM file. IMPORTANT, this function is designed to work with XPM ONLY. It
** does NOT work with XPM2! I haven't tested with XPM3... it should work with
** XPM3, but it's untested.
**
** In XPM files resolution information is stored in the first string, below the
** header information beside the first '"', so that is where we'll look for it.
** It should be the first two numbers, respectively. Once we have them, we exit.
** If we can't find the information, we return 0 and throw a texsizefail error.
** Since the most common cause will likely be attempting to use XPM2 or XPM3
** files with the program, the error will explicitly warn the user that only XPM
** is compatible.
**
** I use a pointer array here. The first pointer member line[0] is used to store
** the address of the first characer in the line string. The second member
** line[1] is used as an index to iterate through the string. This saves me from
** having to declare and initialize an integer to use as an index, or declare a
** second pointer, so it saves me lines... in words, Norminette made me do it.
**
** Since gotres is always incremented after being checked against 2 in the
** in the while, when it fails the check it increments to 3, so the value we
** need to check against at the end of the function to determine whether it
** got both resolutions is 3, not 2. I'd prefer to have that counter inside
** the while so that it terminates neatly on 2, but... Norminette made me do
** it.
**
** If the retrieval succeeds we return 1.
*/

int		getxpmres(int *texres, char *xpmpath)
{
	int		fd;
	char	*line[2];
	int		gotres;

	fd = open(xpmpath, O_RDONLY, S_IRUSR);
	gotres = 0;
	if (fd < 0)
		g_iamerror.couldnotopenxpm = xpmpath;
	else if (fd >= 0 && fd < 3)
		g_iamerror.weirdfd = 1;
	else
	{
		while (!gotres && ft_get_next_line(fd, &line[0]))
		{
			line[1] = line[0];
			while (*line[1] && *line[1] != '"')
				line[1]++;
			while ((line[1] = getnextnum(line[1])) && gotres++ < 2)
				*texres++ = (ft_atoi(line[1]));
			del(line[0]);
		}
	}
	g_iamerror.texsizefail = gotres < 3 ? xpmpath : g_iamerror.texsizefail;
	g_iamerror.couldnotclose = close(fd) < 0 ? 1 : g_iamerror.couldnotclose;
	return (gotres == 3 ? 1 : 0);
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
	char	*texpath[3];
	int		texres[2];
	int		i;

	texpath[0] = sowallimg.texpath;
	texpath[1] = wewallimg.texpath;
	texpath[2] = eawallimg.texpath;
	i = 0;
	while (i < 3)
	{
		getxpmres(texres, texpath[i]);
		if (firstwallsize[0] == texres[0] && firstwallsize[1] == texres[1])
			i++;
		else
			break ;
	}
	if (i < 3)
		g_iamerror.walltexsizedif = 1;
	return (i == 3 ? 1 : 0);
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
	nowallimg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, \
	nowallimg.texpath, &g_config.texW, &g_config.texH);
	sowallimg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, \
	sowallimg.texpath, &g_config.texW, &g_config.texH);
	wewallimg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, \
	wewallimg.texpath, &g_config.texW, &g_config.texH);
	eawallimg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, \
	eawallimg.texpath, &g_config.texW, &g_config.texH);
	if (g_config.spriteNum)
		g_normiImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, \
		g_normiImg.texpath, &g_config.spriteW, &g_config.spriteH);
	if (!nowallimg.mlx_img || !sowallimg.mlx_img || \
	!wewallimg.mlx_img || !eawallimg.mlx_img || \
	(!g_normiImg.mlx_img && g_config.spriteNum))
	{
		g_iamerror.texpathfail = 1;
		return (0);
	}
	return (1);
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
** getteximg, then we will parse the XPM file for the north wall texture to
** discover its resolution (how many pixels high and how many pixels wide it
** is). This is only necessary for one of the wall texture files, because in
** our program we will require all wall textures to have the same resolution,
** for the sake of keeping things looking nice. We will also do this for the
** sprite texture, if there are sprites to load. These values are stored in
** the g_config struct. If this fails we will throw a texsizefail error. This
** is a yellow error, and if it is thrown the program will attempt to continue
** using a default resolution of 64x64 (which is typical for this kind of
** application), but it will warn the user that the image is using a default
** resolution and may not be displayed correctly.
**
** The comptexres function will then use getxpmres on the remaining wall files
** and confirm that they all share the same width and height. If any do not
** share the same width or height, we will terminate with a UN Security Council
** red error. I am extreme about this requirement. ;)
*/

int		maketeximg(void)
{
	int	size[2];

	if (!getteximg() || !getxpmres(size, nowallimg.texpath))
		return (0);
	else
	{
		g_config.texW = size[0];
		g_config.texH = size[1];
	}
	if (!(comptexres(size)))
		return (0);
	if (g_normiImg.mlx_img && !getxpmres(size, g_normiImg.texpath))
		return (0);
	else
	{
		g_config.spriteW = size[0];
		g_config.spriteH = size[1];
	}
	return (1);
}
