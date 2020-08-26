/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:24:16 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 20:05:10 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Here we get the distance from the player position of each sprite. I really
** regret going for linked lists... it's so expensive. :p I need to make a
** sprite pointer array in the future, but it wasn't nearly as urgent as the
** map pointer array. xD
*/

void	getdistances(double *distance, int *spriteorder)
{
	int i;

	i = 0;
	while (i < g_config.spritenum)
	{
		spriteorder[i] = i;
		distance[i] = ((g_player.posx - (spriteiter(i))->posx) * \
		(g_player.posx - (spriteiter(i))->posx) + (g_player.posy - \
		(spriteiter(i))->posy) * (g_player.posy - (spriteiter(i))->posy));
		i++;
	}
}

/*
** This function will sort the sprites in the sprite list in order of their
** distance from the player, from furthest to closest. The spriteorder array
** will then be used to address the sprites in that order while drawing them
** for the frame.
*/

void	sortsprites(int *spriteorder)
{
	double	distance[g_config.spritenum];
	int		tmp;
	int		i;

	getdistances(distance, spriteorder);
	i = -1;
	while (g_config.spritenum > 1 && ++i < g_config.spritenum - 1)
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
