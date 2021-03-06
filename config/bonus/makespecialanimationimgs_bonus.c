/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makespecialanimationimgs_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:19:47 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/27 12:06:32 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

extern t_error g_iamerror;

int		makeending(t_imagedata *ending)
{
	int		i;
	char	*p[7];

	p[0] = "./bonustextures/textboxes/ending1.xpm";
	p[1] = "./bonustextures/textboxes/ending2.xpm";
	p[2] = "./bonustextures/textboxes/ending3.xpm";
	p[3] = "./bonustextures/textboxes/ending4.xpm";
	p[4] = "./bonustextures/textboxes/ending5.xpm";
	p[5] = "./bonustextures/textboxes/ending6.xpm";
	p[6] = "./bonustextures/textboxes/ending7.xpm";
	i = 0;
	while (i < 7)
	{
		if (!(ending->animation[i] = ft_calloc(1, sizeof(t_imagedata))))
		{
			g_iamerror.mallocfail = 1;
			return (0);
		}
		ending->animation[i]->mlx_img = \
		mlx_xpm_file_to_image(g_screendata.mlx_ptr, p[i], \
		&ending->animation[i]->texw, &ending->animation[i]->texh);
		i++;
	}
	return (1);
}

int		makephrases(t_imagedata *phrases)
{
	int		i;
	char	*p[4];

	p[0] = "./bonustextures/textboxes/orenline1.xpm";
	p[1] = "./bonustextures/textboxes/marvinline1.xpm";
	p[2] = "./bonustextures/textboxes/marvinline2.xpm";
	p[3] = "./bonustextures/textboxes/normiannounce.xpm";
	i = 0;
	while (i < 4)
	{
		if (!(phrases->animation[i] = ft_calloc(1, sizeof(t_imagedata))))
		{
			g_iamerror.mallocfail = 1;
			return (0);
		}
		phrases->animation[i]->mlx_img = \
		mlx_xpm_file_to_image(g_screendata.mlx_ptr, p[i], \
		&phrases->animation[i]->texw, &phrases->animation[i]->texh);
		i++;
	}
	return (1);
}

int		makeportalanimation(t_imagedata *portal)
{
	int		i;
	char	*p[8];

	p[0] = "./bonustextures/portalanimation/portal1.xpm";
	p[1] = "./bonustextures/portalanimation/portal2.xpm";
	p[2] = "./bonustextures/portalanimation/portal3.xpm";
	p[3] = "./bonustextures/portalanimation/portal4.xpm";
	p[4] = "./bonustextures/portalanimation/portal5.xpm";
	p[5] = "./bonustextures/portalanimation/portal6.xpm";
	p[6] = "./bonustextures/portalanimation/portal7.xpm";
	p[7] = "./bonustextures/portalanimation/portal8.xpm";
	i = 0;
	while (i < 8)
	{
		if (!(portal->animation[i] = ft_calloc(1, sizeof(t_imagedata))))
		{
			g_iamerror.mallocfail = 1;
			return (0);
		}
		portal->animation[i]->mlx_img = \
		mlx_xpm_file_to_image(g_screendata.mlx_ptr, p[i], \
		&portal->animation[i]->texw, &portal->animation[i]->texh);
		i++;
	}
	return (1);
}
