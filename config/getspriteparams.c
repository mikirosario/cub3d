/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getspriteparams.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:08:49 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/03 19:04:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t g_iamerror;

int		getsprite(const char *line, unsigned int linenum)
{
	int	i;

	if (!line)
		return (0);
	line = ft_skipspaces(line);
	if (*line != 'S' && *line != 's')
		return (0);
	line = ft_skipspaces(++line);
	if (*line != '.' || *(line + 1) != '/')
	{
		g_iamerror.badsprsyn = linenum;
		return (0);
	}
	i = 0;
	while (line[i] && ft_isprint(line[i]))
		i++;
	if (!(g_normiImg.texPath = ft_calloc(i + 1, 1)))
	{
		g_iamerror.mallocfail = 1;
		return (0);
	}
	ft_memcpy(g_normiImg.texPath, line, i);
	ft_printf("Quantum Path Info E Wall: \n%s\n", g_config.spriteTexPath);
	return (1);
}
