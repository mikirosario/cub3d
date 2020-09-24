/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeanimationimgs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:51:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/24 18:23:18 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;

int		companimsizes(t_imagedata **simg)
{
	int	i;
	int	j;

	i = g_config.sprtexnum;
	while (i > 1)
	{
		j = 0;
		while (j < 7 && simg[i]->animation[j + 1])
		{
			if ((simg[i]->animation[j]->texw != simg[i]->animation[j + 1]->texw)
			|| (simg[i]->animation[j]->texh != simg[i]->animation[j + 1]->texh))
			{
				g_iamerror.animtexsizedif = i + 48;
				return (0);
			}
			j++;
		}
		i--;
	}
	return (1);
}

int		checkanimations(t_imagedata *simg)
{
	int i;

	i = 0;
	while (i < 8 && simg->animation[i])
		if (!simg->animation[i++]->mlx_img)
			return (0);
	return (1);
}

void	getanimationimgs(t_imagedata *simg)
{
	int i;

	i = 0;
	while (i < 8 && simg->texpaths[i])
	{
		if (!(simg->animation[i] = \
		ft_calloc(1, sizeof(t_imagedata))))
		{
			g_iamerror.mallocfail = 1;
			break ;
		}
		simg->animation[i]->mlx_img = \
		mlx_xpm_file_to_image(g_screendata.mlx_ptr, simg->texpaths[i], \
		&simg->animation[i]->texw, &simg->animation[i]->texh);
		i++;
	}
}
