/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texerrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:36:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/03 18:53:22 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

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
		
}