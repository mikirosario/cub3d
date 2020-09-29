/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maparray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:05:43 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:21:07 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

/*
** I discovered all too late that iterating through linked lists 60 times a
** second leads to hideous lag. (Hey, I'm learning here! xD). To patch this up
** without radically altering the map checking phase of my program, I assign
** the addresses of each map line to this handy-dandy array, such that in the
** actual raycaster part of the program I only use the array to access the map
** variables.
**
** So yeah, I reserve memory for an array of char pointers that is mapH + 1
** long and assign the address of every map line in the map list to the array
** pointers one by one. NOTE that to access variables using the array you must
** input the coordinates in the order YX, NOT XY, since the line is found
** first, that is, map[Y][X].
*/

int	maparray(void)
{
	t_list	*map_ptr;
	char	**maparray;

	map_ptr = g_config.maplist;
	if (!(g_config.map = ft_calloc((size_t)g_config.maph + 1, sizeof(char *))))
		return (0);
	maparray = g_config.map;
	while (map_ptr)
	{
		*maparray++ = (char *)map_ptr->content;
		map_ptr = map_ptr->next;
	}
	return (1);
}
