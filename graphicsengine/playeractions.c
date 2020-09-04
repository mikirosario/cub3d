/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playeractions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:42:01 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/04 20:47:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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