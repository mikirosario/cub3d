/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:24:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/18 18:34:41 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** This function will sort the sprites in the sprite list in order of their
** distance from the player, from furthest to closest.
*/

void	ft_sortsprites(int *spriteorder)
{
	double	distance[g_config.spriteNum];
	int		tmp;
	int		i;

	i = 0;
	while (i < g_config.spriteNum)
	{
		spriteorder[i] = i;
		distance[i] = ((g_player.posX - (spriteiter(i))->posX) * \
		(g_player.posX - (spriteiter(i))->posX) + (g_player.posY - \
		(spriteiter(i))->posY) * (g_player.posY - (spriteiter(i))->posY));
		i++;
	}
	i = -1;
	while (g_config.spriteNum > 1 && ++i < g_config.spriteNum - 1)
	{
		if (distance[i] < distance[i + 1])
		{
			tmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = tmp;
			tmp = spriteorder[i];
			spriteorder[i] = spriteorder[i + 1];
			spriteorder[i + 1] = tmp;
			i = -1;
		}
	}
}
