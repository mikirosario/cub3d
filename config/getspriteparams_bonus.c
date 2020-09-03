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

int		animationframes(const char **line, int frame, unsigned int linenum, int stype)
{
	int	i;
	if (!**line || **line == stype + 1)
		return (1);
	else if (**line != stype || *(*line + 1) != '.' || *(*line + 2) != '/')
	{
		g_iamerror.badsprsyn = linenum;
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
	if (!((g_simg[stype - 48])->texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy((g_simg[stype - 48])->texpath, line, i);
    g_config.sprtexnum += stype == 50 ? 2 : 1;
    line = ft_skipspaces(&line[i]);
	if (!animationframes(&line, 0, linenum, stype))
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
