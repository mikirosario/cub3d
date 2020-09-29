/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gatekeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:00 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/29 22:23:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

extern t_error	g_iamerror;

/*
** These functions exist because I've been informed that the predominant
** interpretation of the project instructions is that the map must end the file,
** meaning nothing is allowed below the map in the file, and that duplicate
** parameter declarations should not be allowed.
**
** Before this modification, my parser was liberal and tolerant of strange text
** floating around. It retrieved the first parameter it found and ignored any
** subsequent parameters, leaving them free to live their lives as they liked.
** It held hands with the other functions and sang songs about fraternal love.
**
** Those naive and happy days are now over. Henceforth, all parameters in the
** .cub file must obey the law, under penalty of DEATH. A new error flag has
** arisen called cubpolice. If the cubpolice complain about a .cub file, the
** program will be terminated with EXTREME prejudice. You have been warned.
*/

int	duplicateparam(int linenum, int param)
{
	g_iamerror.duplicateparam[param] = linenum;
	ft_printf("\nDUPLICATE LINE %d\n", linenum);
	return (0);
}

int	endcub(char *line, int endfile)
{
	if (line && endfile && (*line)) //si primera línea existe y ya es eof y no es nulo, mapa NO ES endfile
		return (0);
	return (endfile);
}