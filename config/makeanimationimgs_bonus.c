/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeanimationimgs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:51:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/03 19:44:32 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;

int		getanimationptrs(t_spritedata *sprt, t_imagedata *simg)
{
	int	i;
	
	i = 0;
	sprt->firstframe = sprt->texture;
	while (simg->animation[i])
	{	if (!(sprt->animtex[i] = \
		(unsigned int *)mlx_get_data_addr(simg->animation[i]->mlx_img, \
		&simg->animation[i]->bpp, &simg->animation[i]->size_line, \
		&simg->animation[i]->endian)))
			return (0);
		i++;
	}
	return (1);
}

int		checkanimations(t_imagedata *simg)
{
	int i;

	i = 0;
	while (simg->animation[i])
		if (!simg->animation[i++]->mlx_img)
			return (0);
	return (1);
}

void	getanimationimgs(t_imagedata *simg)
{
	int i;

	i = 0;
	while (simg->texpaths[i])
	{
		if (!(simg->animation[i] = ft_calloc(1, sizeof(t_imagedata))))
		{
			g_iamerror.mallocfail = 1;
			break ;
		}
		simg->animation[i]->mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, \
		simg->texpaths[i], &simg->animation[i]->texw, &simg->animation[i]->texh);
		i++;
	}
}