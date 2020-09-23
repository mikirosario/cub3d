/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportplayer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 03:33:44 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/23 20:38:15 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** Music
** "Sewer Monsters Town Hall Meeting" by Eric Matyas
** www.soundimage.org
*/

void	lastlevel(void)
{
	g_framedata.phrase = 4;
	g_framedata.lastlevel = 1;
	kill(g_config.musicpid, 15);
	g_config.musicpid = fork();
	if (!g_config.musicpid)
		playtrack(HALL_THEME);
}

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
	if (g_config.door[i]->destaddr->posx == 29 && \
	g_config.door[i]->destaddr->posy == 21)
		lastlevel();
	return (1);
}
