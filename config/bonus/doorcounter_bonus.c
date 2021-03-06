/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcounter_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:28:59 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/27 12:06:32 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

int		doorcounter(unsigned int x, unsigned int y, char *c)
{
	static t_spritedata	*lstptr = NULL;

	g_config.doornum++;
	if (!g_config.doorlist)
	{
		g_config.doorlist = ft_sprtlstnew((void *)0);
		lstptr = g_config.doorlist;
	}
	else
	{
		ft_sprtlstadd_back(&g_config.doorlist, (ft_sprtlstnew((void *)0)));
		lstptr = lstptr->next;
	}
	if (!lstptr)
		return (0);
	lstptr->posx = x;
	lstptr->posy = y;
	if ((lstptr->spritetype = *c) == '*')
		*c = 'A';
	lstptr->dooraddr = c;
	lstptr->destaddr = 0;
	lstptr->doorend = 0;
	return (1);
}
