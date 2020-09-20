/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportplayer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 03:33:44 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/20 03:55:54 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int		teleporter(char *mapchr)
{
	int	i;

	if (*mapchr != '*')
		return (0);
	i = 0;
	while (g_config.door[i]->dooraddr != mapchr)
		i++;
	g_player.posx = g_config.door[i]->destaddr->posx + 0.5;
	g_player.posy = g_config.door[i]->destaddr->posy + 0.5;
	return(1);
}