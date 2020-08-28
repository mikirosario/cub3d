/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texerrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:36:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/28 19:39:45 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error	g_iamerror;

/*
** This function simply checks all the conditions for going into the texerrors
** function, in case any texture configuration errors happened. There are so
** bloody many that I just gave it its own function to save lines. :p If any
** condition is true, it returns 1. If all are false, it returns 0. Simples.
**
** Note: we will only consider that sprite texture failures, such as failing
** to get a sprite path or failing to load a sprite image, count as an error
** condition if we actually found sprites on the map (g_config.spritenum).
*/

int		texerrorconditions(void)
{
	if (g_iamerror.getnofail || g_iamerror.getsofail || g_iamerror.getwefail \
	|| g_iamerror.geteafail || (g_config.spritenum && (g_iamerror.getsprfail \
	|| !g_sprt2img.mlx_img)) || g_iamerror.texpathfail \
	|| g_iamerror.texsizefail || g_iamerror.couldnotopenxpm \
	|| g_iamerror.walltexsizedif)
		return (1);
	return (0);
}

void	texreaderror(void)
{
	if (g_iamerror.texsizefail)
		ft_printf(YELLOW"%s%s\n"RESET, TEXSIZEFAIL, g_iamerror.texsizefail);
	if (g_iamerror.walltexsizedif)
		ft_printf(RED"%s\n"RESET, WALLTEXSIZEDIF);
	if (g_iamerror.couldnotopenxpm)
		ft_printf(RED"%s%s\n"RESET, OPENXPMFAIL, g_iamerror.couldnotopenxpm);
}

void	texpatherrors(void)
{
	if (!g_nowallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHNOFAIL, g_nowallimg.texpath);
	if (!g_sowallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHSOFAIL, g_sowallimg.texpath);
	if (!g_wewallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHWEFAIL, g_wewallimg.texpath);
	if (!g_eawallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHEAFAIL, g_eawallimg.texpath);
	if (g_config.spritenum && !g_sprt2img.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHSPRFAIL, g_sprt2img.texpath);
}
