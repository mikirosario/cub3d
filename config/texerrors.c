/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texerrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:36:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/07 20:27:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

/*
** This function simply checks all the conditions for going into the texerrors
** function, in case any texture configuration errors happened. There are so
** bloody many that I just gave it its own function to save lines. :p If any
** condition is true, it returns 1. If all are false, it returns 0. Simples.
**
** Note: we will only consider that sprite texture failures, such as failing
** to get a sprite path or failing to load a sprite image, count as an error
** condition if we actually found sprites on the map (g_config.spriteNum).
*/

int		texerrorconditions(void)
{
	if (g_iamerror.getnofail || g_iamerror.getsofail || g_iamerror.getwefail \
	|| g_iamerror.geteafail || (g_config.spriteNum && (g_iamerror.getsprfail \
	|| !g_normiImg.mlx_img)) || g_iamerror.texpathfail || g_iamerror.texsizefail \
	|| g_iamerror.couldnotopenxpm || g_iamerror.walltexsizedif)
		return (1);
	return (0);
}

void	texpatherrors(void)
{
	if (!g_blueMetalImg.mlx_img)
		ft_printf("%s%s\n", pathNOFail, g_blueMetalImg.texPath);
	if (!g_yellowMetalImg.mlx_img)
		ft_printf("%s%s\n", pathSOFail, g_yellowMetalImg.texPath);
	if (!g_greenMetalImg.mlx_img)
		ft_printf("%s%s\n", pathWEFail, g_greenMetalImg.texPath);
	if (!g_pinkMetalImg.mlx_img)
		ft_printf("%s%s\n", pathEAFail, g_pinkMetalImg.texPath);
	if (g_config.spriteNum && !g_normiImg.mlx_img)
		ft_printf("%s%s\n", pathSprFail, g_normiImg.texPath);
	if (g_iamerror.texsizefail)
		ft_printf("%s%s\n", texSizeFail, g_iamerror.texsizefail);
	if (g_iamerror.walltexsizedif)
		ft_printf("%s\n", wallTexSizeDif);
	if (g_iamerror.couldnotopenxpm)
		ft_printf("%s%s\n", couldNotOpenXPM, g_iamerror.couldnotopenxpm);
}
