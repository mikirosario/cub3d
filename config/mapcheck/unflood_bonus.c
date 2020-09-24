/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unflood_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:26:18 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/24 20:35:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	replacedoors(char *mapchr)
{
	int	d;

	d = 0;
	while (d < g_config.doornum && g_config.door[d]->dooraddr != mapchr)
		d++;
	if (d < g_config.doornum)
		*mapchr = g_config.door[d]->spritetype;
	else
		*mapchr = '0';
}

/*
** This function will take the map left by the floodfill function, which fills
** all traversable spaces in the map with 'A' and/or 'T' characters until all
** spaces reachable by the player are filled or an out of bounds position is
** reached, and change all the 'A' and/or 'T' character to '0' so that the
** raycaster can read the map.
**
** The function has two modes, normal mode, which is launched by default, and
** 'error' mode. In normal mode filled characters are changed to '0'. In error
** mode, filled characters are changed to '.', to show the user where the
** floodfill checked before discovering the error in the map.
**
** To launch error mode, pass the function "error" as its only argument. To
** launch normal mode, pass it any other string (including an empty string).
**
** For the bonus version, any doors found on the map and eliminated by floodfill
** will be replaced.
*/

void	unfloodmap(char *flag)
{
	t_list	*mapptr;
	char	*mapchr;
	char	mode;
	int		i;

	mapptr = g_config.maplist;
	mode = 'p';
	if (!(ft_strncmp(flag, "error", 5)))
		mode = 'e';
	while (mapptr)
	{
		i = 0;
		while ((*(mapchr = (char *)(mapptr->content + i))))
		{
			if (*mapchr == 'T' || *mapchr == 'A')
			{
				if (mode == 'p')
					replacedoors(mapchr);
				else
					*mapchr = '.';
			}
			i++;
		}
		mapptr = mapptr->next;
	}
}
