/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animationerrors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:52:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/03 19:04:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_error g_iamerror;

/*
** No more error functions... please... for the love of Turing... no more...
*/

void	animationtexerrors(t_imagedata *simg)
{
	int i;

	i = 0;
	while (simg->texpaths[i])
	{
		if (!(simg->animation[i]->mlx_img))
			ft_printf(RED"%s%s\n"RESET, PATHSPRFAIL, (simg->texpaths[i]));
		i++;
	}
}