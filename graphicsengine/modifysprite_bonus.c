/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifysprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:37:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/13 02:33:02 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function cycles through animation textures of animated sprites.
*/

void	animate(t_spritedata *sprite)
{
	if (sprite->framelimit)
	{
		sprite->texture = sprite->animtex[sprite->frame];
		if (sprite->frame < sprite->framelimit)
			sprite->frame++;
		else
			sprite->frame = 0;
	}
}

/*
** This function removes sprites from the map.
*/

void	removesprite(t_spritedata *sprite)
{
	t_spritedata	*tmp;
	int				i;

	ft_movesprttoback(g_config.spritelist, sprite);
	g_config.spritenum--;
	tmp = g_config.spritelist;
	i = 0;
	while (i < g_config.spritenum)
	{
		g_config.sprt[i++] = tmp;
		tmp = tmp->next;
	}
}
