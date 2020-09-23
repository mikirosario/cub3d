/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifysprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:37:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/23 18:10:19 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** This function cycles through animation textures of animated sprites.
*/

void	animate(t_spritedata *sprite)
{
	int speed;

	speed = 1;
	if (sprite->animspeed++ == speed && sprite->framelimit)
	{
		sprite->animspeed = 0;
		if (sprite->frame < sprite->framelimit)
			sprite->frame++;
		else
			sprite->frame = 0;
		sprite->texture = sprite->animtex[sprite->frame];
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
