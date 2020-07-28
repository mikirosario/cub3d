/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:17:09 by mrosario          #+#    #+#             */
/*   Updated: 2020/07/28 20:36:11 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t	g_iamerror;

/*
** Y + 1 (In text editor lines start with 1, not 0), + lines counted before the
** gives the line number of the error. X, saved as array value 0, gives the
** position before the error and can be passed to ft_printf as precision via the
** * flag to print up to the error. Then map retrieval functions can be used to
** print the rest of the bad line for the user.
*/
void	maperrors(void)
{
	unsigned int o;
	unsigned int x;
	unsigned int y;

	//guarreo
	t_list *map = g_config.Map;

	o = g_iamerror.premaplines;
	ft_printf("%s", REDERROR);
	if (g_iamerror.noplayer)
		ft_putstr(noPlayer, strlen(noPlayer));
	else
		*((char *)mapListDir(g_player.posX, g_player.posY)) = 'P';
	if (g_iamerror.badmap3line)
		ft_putstr(badMap3line, strlen(badMap3line));
	x = g_iamerror.outofbounds[0];
	y = g_iamerror.outofbounds[1];

	//guarreo general
	*((char *)mapListDir(x, y)) = 'K';
	
	if (g_iamerror.outofbounds[2])
		ft_printf("Line: %u: %.*s"RED"%c"RESET"%s\n%s\n", y + 1 + o, x, \
		mapListDir(0, y), mapList(x, y), mapListDir(x + 1, y), outOfBounds);
	
	//más guarreo
	while (map)
	{
		printf("%s\n", (char *)map->content);
		map = map->next;
	}

	//ft_printf("\n%s", mapListDir(0, y));
	
	x = g_iamerror.toomanyplayers[0];
	y = g_iamerror.toomanyplayers[1];
	if (g_iamerror.toomanyplayers[2])
		ft_printf("Line: %u: %.*s"RED"%c"RESET"%s\n%s\n", y + 1 + o, x, \
		mapListDir(0, y), mapList(x, y), mapListDir(x + 1, y), tooManyPlayers);
	if (g_config.spriteList)
		freeSprtList(&g_config.spriteList);
	if (g_config.Map)
		freeList(&g_config.Map);
}

void	reserrors(void)
{
	setdisplayresolution();
	ft_printf("%s", YELLOWERROR);
	ft_putstr(getResFail, ft_strlen(getResFail));
	if (g_iamerror.badresSyn)
		ft_printf("Line %u: %s", g_iamerror.badresSyn, badResSyn);
	if (g_iamerror.badresSize)
		ft_printf("Line %u: %s", g_iamerror.badresSize, badResSize);
	return ;
}

void	texerrors(void)
{
	ft_printf("%s", REDERROR);
	if (g_iamerror.getnofail)
		ft_putstr(getNOFail, ft_strlen(getNOFail));
	if (g_iamerror.badnosyn)
		ft_printf("Line %u: %s", g_iamerror.badnosyn, badNOSyn);
	if (g_iamerror.getsofail)
		ft_putstr(getSOFail, ft_strlen(getSOFail));
	if (g_iamerror.badsosyn)
		ft_printf("Line %u: %s", g_iamerror.badsosyn, badSOSyn);
	if (g_iamerror.getwefail)
		ft_putstr(getWEFail, ft_strlen(getWEFail));
	if (g_iamerror.badwesyn)
		ft_printf("Line %u: %s", g_iamerror.badwesyn, badWESyn);
	if (g_iamerror.geteafail)
		ft_putstr(getEAFail, ft_strlen(getEAFail));
	if (g_iamerror.badeasyn)
		ft_printf("Line %u: %s", g_iamerror.badeasyn, badEASyn);
	if (g_config.spriteNum && g_iamerror.getsprfail)
		ft_putstr(getSprFail, ft_strlen(getSprFail));
	if (g_config.spriteNum && g_iamerror.badsprsyn)
		ft_printf("Line %u: %s", g_iamerror.badsprsyn, badSprSyn);
}

void	ceilingfloorerrors(void)
{
	ft_printf("%s", YELLOWERROR);
	if (g_iamerror.fcolorinvalid)
		ft_putstr(FColorInvalid, ft_strlen(FColorInvalid));
	if (g_iamerror.badfcolorsyn)
		ft_printf("Line %u: %s", g_iamerror.badfcolorsyn, badFColorSyn);
	if (g_iamerror.ccolorinvalid)
		ft_putstr(CColorInvalid, ft_strlen(CColorInvalid));
	if (g_iamerror.badccolorsyn)
		ft_printf("Line %u: %s", g_iamerror.badccolorsyn, badCColorSyn);
}

/*
** printerrors refers to a global struct called iamerror to check
** whether flags are set signalling certain errors. The flags are set by
** the program as they occur. If set, the corresponding error message will
** be printed on screen. Map errors will not be printed if preceding errors
** caused the program to abort. In the case of the nomapfound error this is
** controlled with the mapchecked flag; subsequently, because the errors will
** only be set programatically if a map has been found first.
**
** I might change this to have the flags and strings arrays with
** with corresponding memory positions (error[x] prints message[x]), so that
** the function can be reduced to a while loop... Maybe...
*/

void	printerrors(void)
{
	if (g_iamerror.cubfilenotfound)
		ft_putstr(cubFileNotFound, ft_strlen(cubFileNotFound));
	if (g_iamerror.weirdfd)
		ft_putstr(weirdFD, ft_strlen(weirdFD));
	if (g_iamerror.getresfail)
		reserrors();
	if (g_iamerror.getnofail || g_iamerror.getsofail || g_iamerror.getwefail \
	|| g_iamerror.geteafail || (g_config.spriteNum && g_iamerror.getsprfail))
		texerrors();
	if (g_iamerror.fcolorinvalid || g_iamerror.ccolorinvalid)
		ceilingfloorerrors();
	if (g_iamerror.outofbounds[2] || g_iamerror.noplayer || g_iamerror.badmap3line || g_iamerror.toomanyplayers[2])
		maperrors();
	if (g_iamerror.mapchecked && g_iamerror.nomapfound)
		ft_putstr(noMapFound, ft_strlen(noMapFound));
	if (g_iamerror.couldnotclose)
		ft_putstr(couldNotClose, ft_strlen(couldNotClose));
	write(1, "\n", 1);
	printf("\nReal Resolution: %d, %d\n", g_config.screenW, g_config.screenH);
	return ;
}
