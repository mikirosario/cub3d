/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:17:09 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 18:28:51 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error	g_iamerror;

/*
** This function prints the RED ERROR message and then calls the functions
** generalmaperrors and localizedmaperrors to handle and print the associated
** error routines and messages. These functions are defined in the maperrors.c
** file.
**
** The mapsweeps variable registers how many times floodfill has scanned the
** map. If floodfill is called, this will be at least 1. If mapsweeps is 0,
** it means floodfill has not been called. Thereefore, we can use this datum
** to know if floodfill has or hasn't been called. Noplayer is a variable that
** is true when NO PLAYER has been found, but it is also false by default.
**
** If noplayer is false *and* floodfill was called, it means we made it past
** the first battery of tests where we finish looking for a player, so the
** noplayer variable cannot be false just because it was left that way by
** default and the program aborted for an unrelated reason (like finding only
** 3 lines in the map) before it could finish looking for players. Rather,
** we know if noplayer is false by the time we reach floodfill, it is because
** we DID find a player somewhere in the map, so even if the player location
** coordinates are 0,0, we know there is an actual player found there.
**
** We do this test just to print out the player's location for the user to make
** it easier to see where an out of bounds problem might be in the map. We
** will signal the player's location with a 'P', unflood the map with the
** error flag to replace any spaces checked by floodfill with '.' in the event
** of an out of bounds error, print the map, and then print any errors that
** were found below it.
*/

void	maperrors(void)
{
	if (!g_iamerror.noplayer && g_iamerror.mapsweeps)
		*((char *)maplistdir(g_player.posx, g_player.posy)) = 'P';
	unfloodmap("error");
	printmap();
	ft_printf("%s", REDERROR);
	generalmaperrors();
	localizedmaperrors();
}

/*
** This function will be triggered if for any reason any part of the
** user-declared resolution could not be retrieved, or if no resolution was
** declared by the user, or if the user-declared resolution was too small, or
** greater than the supported display resolution.
**
** First it will call the setdisplayresolution function to set the resolution
** to the default resolution. Since these errors do not impede the program
** from launching, the YELLOW ERROR message will be printed, followed by the
** failed resolution retrieval message, and any specific errors along with the
** cub file line where they were detected.
**
** Possible specific errors are the syntax error and the bad resolution size
** error.
*/

void	reserrors(void)
{
	ft_printf("%s", YELLOWERROR);
	ft_putstr(getResFail, ft_strlen(getResFail));
	if (g_iamerror.badressyn)
		ft_printf("Line %u: %s", g_iamerror.badressyn, badResSyn);
	if (g_iamerror.badressize)
		ft_printf("Line %u: %s", g_iamerror.badressize, badresosize);
	return ;
}

/*
** This function will be triggered if for any reason the program was unable
** to retrieve the user-supplied textures.
**
** Depending on the errors present, the associated error messages will be
** printed. For syntax errors, the line where the error was detected will be
** reported to the user. Possible errors are retrieval errors and syntax
** errors.
*/

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
	if (g_config.spritenum && g_iamerror.getsprfail)
		ft_putstr(getSprFail, ft_strlen(getSprFail));
	if (g_config.spritenum && g_iamerror.badsprsyn)
		ft_printf("Line %u: %s", g_iamerror.badsprsyn, badSprSyn);
	texreaderror();
	if (g_iamerror.texpathfail)
		texpatherrors();
}

/*
** This function handles retrieval errors for the color values supplied
** by the user to define ceiling and floor colors.
**
** Since these errors do not impede the program from launching, the YELLOW
** ERROR message will be printed, followed by the failed color value retrieval
** message.
**
** Depending on the errors present, the associated error messages will be
** printed. For syntax errors, the line where the error was detected will be
** reported to the user. Possible errors are retrieval errors and syntax
** errors.
*/

void	ceilingfloorerrors(void)
{
	ft_printf("%s", YELLOWERROR);
	if (g_iamerror.fcolorinvalid)
		ft_putstr(FColorInvalid, ft_strlen(FColorInvalid));
	if (g_iamerror.badfcolorsyn)
		ft_printf("Line %u: %s", g_iamerror.badfcolorsyn, badFColorSyn);
	if (g_iamerror.fcoloroutofrange)
		ft_printf(badcolorrange);
	if (g_iamerror.ccolorinvalid)
		ft_putstr(CColorInvalid, ft_strlen(CColorInvalid));
	if (g_iamerror.badccolorsyn)
		ft_printf("Line %u: %s", g_iamerror.badccolorsyn, badCColorSyn);
	if (g_iamerror.ccoloroutofrange)
		ft_printf(badcolorrange);
}

/*
** The printerrors function refers to a global struct called iamerror to check
** whether flags have been set signalling certain errors. The flags are set by
** the program as they occur. If set, the corresponding error messages will
** be printed on screen.
**
** Map errors will not be printed unless a map has been found and checked.
**
** If no map was found, a no map found error will be displayed. However, if
** errors before the map could be checked cause the program to abort, no map
** error will be displayed, even if the nomapfound error is flagged. This is
** controlled with the mapchecked flag, which indicates whether the map was
** checked.
*/

void	printerrors(void)
{
	if (g_iamerror.cubfilenotfound)
		ft_putstr(cubFileNotFound, ft_strlen(cubFileNotFound));
	if (g_iamerror.weirdfd)
		ft_putstr(weirdFD, ft_strlen(weirdFD));
	if (g_iamerror.getresfail)
		reserrors();
	if (g_iamerror.fcolorinvalid || g_iamerror.ccolorinvalid)
		ceilingfloorerrors();
	if (g_iamerror.outofbounds[2] || g_iamerror.noplayer || \
	g_iamerror.badmap3line || g_iamerror.toomanyplayers[2] || \
	g_iamerror.maptoobig)
		maperrors();
	else if (texerrorconditions())
		texerrors();
	if (g_iamerror.mapchecked && g_iamerror.nomapfound)
		ft_putstr(noMapFound, ft_strlen(noMapFound));
	if (g_iamerror.couldnotclose)
		ft_putstr(couldNotClose, ft_strlen(couldNotClose));
	write(1, "\n", 1);
	return ;
}
