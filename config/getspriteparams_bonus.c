/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getspriteparams_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:08:49 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/03 17:32:33 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;
t_imagedata *g_simg[10];

/*
** This function is definitely not winning any beauty contests, but it works.
** It is recursive like its calling function, and will check for animation
** frames alongside a listed frame path. If more than one sprite path (up to
** eight in total) are found with the same sprite number, they will be
** collected and used to create an animated sprite.
**
** The functions will return 1 if they reach a NULL character or the next type.
**
** They will return 0 if the frame limit is exceeded (causing a toomanyframes
** and syntax error), or just a syntax error if the sprite number is out of
** order or the path is not in the game directory, or a memory failure if malloc
** can't allocate.
**
** Otherwise it will merrily collect the provided paths and store them, just
** like it's cousin, but will store each animation path within a t_imagedata
** pointer array within its parent sprite's struct for easy access later.
**
** Note that line must be dereferenced *before* being iterated through as it
** is a double pointer, and I mean to iterate through the array pointed at by
** the pointer it points to, not the double pointer itself. I do this so I can
** change the address of that pointer without returning it back, since I want
** to return a success/failure indication instead.
*/

int		animationframes(const char **line, int frame, unsigned int linenum, int stype)
{
	int	i;
	if (!**line || **line == stype + 1)
		return (1);
	else if (**line != stype || *(*line + 1) != '.' || *(*line + 2) != '/' \
	|| frame == 8)
	{
		g_iamerror.badsprsyn = linenum;
		if (frame == 8)
			g_iamerror.toomanyframes = 1;
		return (0);
	}
	i = 0;
	*line += 1;
	while ((*line)[i] && ft_isprint((*line)[i]) && !(ft_isspace((*line)[i])))
		i++;
	if (!((g_simg[stype - 48])->texpaths[frame] = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy((g_simg[stype - 48])->texpaths[frame++], *line, i);
	*line = ft_skipspaces(&((*line)[i]));
	return (animationframes(line, frame, linenum, stype));
}

/*
** This recursive function will check for bad syntax first, which means the
** sprite number is not in ascending order or the path goes outside the game
** directory. If malloc fails then we return a mallocfail error.
**
** Otherwise we take the path and record the highest sprite type for which
** a path has been collected in sprttexnum. The first sprite type number is
** 2 (50 in ASCII), and we allow for up to eight sprites, so from 2 to 9 (50 to
** 57). The simg pointer array doesn't use the first two memory spaces so that
** it can keep a direct correspondence with sprite type, such that simg[2]
** points to sprite type 2, etc. This is for convenience.
**
** Another novelty for the bonus is the ability to animate sprites! By
** repeating the same sprite type beside another path in the .cub file,
** the animationframes will collect up to seven additional image paths, for a
** total of eight, to use as animation frames.
*/

int     sprtpaths(const char *line, unsigned int linenum, int stype)
{
    int i;

    if (*line != stype || *(line + 1) != '.' || *(line + 2) != '/')
	{
		g_iamerror.badsprsyn = linenum;
		return (0);
	}
	i = 0;
    line++;
	while (line[i] && ft_isprint(line[i]) && !(ft_isspace(line[i])))
		i++;
	if (!((g_simg[stype - 48])->texpaths[0] = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy((g_simg[stype - 48])->texpaths[0], line, i);
    g_config.sprtexnum += stype == 50 ? 2 : 1;
    line = ft_skipspaces(&line[i]);
	if (!animationframes(&line, 1, linenum, stype))
		return (0);
    return (++stype < 58 && *line ? sprtpaths(line, linenum, stype) : 1);
}

/*
** Note: To distinguish this line from the SO/so line that passes the south
** wall texture path, after skipping any initial spaces, we will terminate
** this function if the character we find is NOT an 'S' and is NOT an 's',
** OR (that is, even if it IS) if the character following it IS an 'O' or IS
** an 'o'. I don't like segfaults, so I also tell it to terminate the function
** if it finds a NULL there. ;p
**
** For the bonus I do things a bit differently. To cope with multiple possible
** sprite textures, here we put all eight possible sprite texture paths,
** numbered from 2 to 9, in an array. The array is ten bytes, and the first two
** bytes are unused, this is so that the sprite number and index number will
** line up, for ease of programming. Note I find the occasion for my very first
** TRIPLE POINTER, a pointer to an array of pointers to pointers. Woot!! xD
** Ugh, never mind, I needed the struct address more than the texpath address
** so it's back to being a boring old double pointer. Yawn. xD
**
** On the sprite line the user can leave up to eight paths.
*/

int		getsprite(const char *line, unsigned int linenum)
{
    int         stype;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if ((*line != 'S' && *line != 's') || (!(*(line + 1)) || \
	*(line + 1) == 'O' || *(line + 1) == 'o'))
		return (0);
	line = ft_skipspaces(++line);
    stype = 50;
    g_simg[2] = &g_sprt2img;
    g_simg[3] = &g_sprt3img;
    g_simg[4] = &g_sprt4img;
    g_simg[5] = &g_sprt5img;
    g_simg[6] = &g_sprt6img;
    g_simg[7] = &g_sprt7img;
    g_simg[8] = &g_sprt8img;
    g_simg[9] = &g_sprt9img;
	return (*line ? sprtpaths(line, linenum, stype) : 0);
}
