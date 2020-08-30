/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getspriteparams_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:08:49 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:17:43 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;
t_imagedata *sprimg[10];

int     sprtpaths(const char *line, unsigned int linenum, t_imagedata **sprimg, \
int stype)
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
	if (!((*sprimg[stype - 48]).texpath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy((*sprimg[stype - 48]).texpath, line, i);
    g_config.sprtexnum += stype == 50 ? 2 : 1;
    line = ft_skipspaces(&line[i]);
    return (++stype < 58 && *line ? sprtpaths(line, linenum, sprimg, stype) : \
    1);
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
    sprimg[2] = &g_sprt2img;
    sprimg[3] = &g_sprt3img;
    sprimg[4] = &g_sprt4img;
    sprimg[5] = &g_sprt5img;
    sprimg[6] = &g_sprt6img;
    sprimg[7] = &g_sprt7img;
    sprimg[8] = &g_sprt8img;
    sprimg[9] = &g_sprt9img;
	return (*line ? sprtpaths(line, linenum, sprimg, stype) : 0);
}
