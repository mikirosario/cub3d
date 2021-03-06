/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texerrors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:36:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/05 15:25:07 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

extern t_error	g_iamerror;
extern t_imagedata *g_simg[10];

void	bonustexfailures(void)
{
	if (g_iamerror.toomanyframes)
		ft_printf(RED"%s"RESET, TOOMANYFRAMES);
	if (g_iamerror.getfloorfail)
		ft_printf(RED"%s"RESET, GETFLFAIL);
	if (g_iamerror.badfloorsyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badfloorsyn, BADFLSYN);
	if (g_iamerror.getceilfail)
		ft_printf(RED"%s"RESET, GETCEFAIL);
	if (g_iamerror.badceilsyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badceilsyn, BADCESYN);
}

void	gettexfail(void)
{
	if (g_iamerror.getnofail)
		ft_printf(RED"%s"RESET, GETNOFAIL);
	if (g_iamerror.badnosyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badnosyn, BADNOSYN);
	if (g_iamerror.getsofail)
		ft_printf(RED"%s"RESET, GETSOFAIL);
	if (g_iamerror.badsosyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badsosyn, BADSOSYN);
	if (g_iamerror.getwefail)
		ft_printf(RED"%s"RESET, GETWEFAIL);
	if (g_iamerror.badwesyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badwesyn, BADWESYN);
	if (g_iamerror.geteafail)
		ft_printf(RED"%s"RESET, GETEAFAIL);
	if (g_iamerror.badeasyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badeasyn, BADEASYN);
	if (g_iamerror.getsprfail)
		ft_printf(RED"%s"RESET, GETSPRFAIL);
	if (g_iamerror.badsprsyn)
		ft_printf("Line %u: "RED"%s"RESET, g_iamerror.badsprsyn, BADSPRSYN);
	bonustexfailures();
}

/*
** This function simply checks all the conditions for going into the texerrors
** function, in case any texture configuration errors happened. There are so
** bloody many that I just gave it its own function to save lines. :p If any
** condition is true, it returns 1. If all are false, it returns 0. Simples.
**
** Note: we will only consider that sprite texture failures, such as failing
** to get a sprite path or failing to load a sprite image, count as an error
** condition if we actually found sprites on the map (g_config.spritenum).
*/

int		texerrorconditions(void)
{
	if (g_iamerror.getnofail || g_iamerror.getsofail || g_iamerror.getwefail \
	|| g_iamerror.geteafail || g_iamerror.getfloorfail \
	|| g_iamerror.getceilfail || (g_config.spritenum && g_iamerror.getsprfail)
	|| g_iamerror.badsprsyn || g_iamerror.texpathfail \
	|| g_iamerror.orphansprites || g_iamerror.texsizefail \
	|| g_iamerror.couldnotopenxpm || g_iamerror.walltexsizedif \
	|| g_iamerror.animtexsizedif)
		return (1);
	return (0);
}

void	texreaderror(void)
{
	if (g_iamerror.texsizefail)
		ft_printf(YELLOW"%s%s\n"RESET, TEXSIZEFAIL, g_iamerror.texsizefail);
	if (g_iamerror.walltexsizedif)
		ft_printf(RED"%s\n"RESET, WALLTEXSIZEDIF);
	if (g_iamerror.animtexsizedif)
		ft_printf(RED"%s"RESET"Sprite: 4\n", ANIMSIZDIF, \
		g_iamerror.animtexsizedif);
	if (g_iamerror.couldnotopenxpm)
		ft_printf(RED"%s%s\n"RESET, OPENXPMFAIL, g_iamerror.couldnotopenxpm);
}

void	texpatherrors(void)
{
	int i;

	i = 2;
	if (!g_nowallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHNOFAIL, g_nowallimg.texpath);
	if (!g_sowallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHSOFAIL, g_sowallimg.texpath);
	if (!g_wewallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHWEFAIL, g_wewallimg.texpath);
	if (!g_eawallimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHEAFAIL, g_eawallimg.texpath);
	if (g_config.spritenum)
		while (i <= g_config.sprtexnum)
		{
			if (!g_simg[i]->mlx_img)
				ft_printf(RED"%s%s\n"RESET, PATHSPRFAIL, (*g_simg[i]).texpath);
			if (g_simg[i]->texpaths[0])
				animationtexerrors(g_simg[i]);
			i++;
		}
	if (!g_floorimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHFLFAIL, g_floorimg.texpath);
	if (!g_ceilingimg.mlx_img)
		ft_printf(RED"%s%s\n"RESET, PATHCEFAIL, g_ceilingimg.texpath);
}
