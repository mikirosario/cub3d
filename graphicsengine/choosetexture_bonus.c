/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choosetexture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 06:08:28 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/22 20:54:33 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

unsigned int	*portal(t_raycasterdata *rdata)
{
	if (!rdata->portalvisible)
		rdata->portalvisible = 1;
	return (g_portal.tex_ptr);
}

unsigned int	*verdoor(void)
{
	if (g_raydata.stepx > 0)
		return (g_doorleftimg.tex_ptr);
	else
		return (g_doorrightimg.tex_ptr);
}

unsigned int	*hordoor(void)
{
	if (g_raydata.stepy > 0)
		return (g_doorrightimg.tex_ptr);
	else
		return (g_doorleftimg.tex_ptr);
}

unsigned int	*choosetexture(t_raycasterdata *rdata)
{
	unsigned int *texptr;

	texptr = NULL;
	if (g_raydata.hit == 2)
		texptr = hordoor();
	else if (g_raydata.hit == 3)
		texptr = verdoor();
	else if (g_raydata.hit == 4)
		texptr = portal(rdata);
	else if (g_raydata.side == 1 && g_raydata.stepy > 0)
		texptr = g_sowallimg.tex_ptr;
	else if (g_raydata.side == 1 && g_raydata.stepy < 0)
		texptr = g_nowallimg.tex_ptr;
	else if (g_raydata.side == 0 && g_raydata.stepx > 0)
		texptr = g_eawallimg.tex_ptr;
	else if (g_raydata.side == 0 && g_raydata.stepx < 0)
		texptr = g_wewallimg.tex_ptr;
	return (texptr);
}
