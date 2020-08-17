/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcopy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:05:43 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 20:37:48 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	maparray(void)
{
	t_list	*map_ptr;
	char	**mapcopy;

	map_ptr = g_config.Map;
	
	g_config.map = ft_calloc((size_t)g_config.mapH + 1, sizeof(char *));
	mapcopy = g_config.map;

	while (map_ptr)
	{
		*mapcopy++ = ft_strdup((char *)map_ptr->content);
		map_ptr = map_ptr->next;
	}
	mapcopy = g_config.map;
	unsigned int i = 0;
	while (i <= g_config.mapH)
	{
		ft_printf("\n%s", *mapcopy);
		mapcopy++;
		i++;
	}
	printf("\n%f,%f", g_player.posY,g_player.posX);
}