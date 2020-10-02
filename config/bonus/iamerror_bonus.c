/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamerror_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:17:09 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/02 19:47:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

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
	ft_printf(RED"%s"RESET, REDERROR);
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
	ft_printf(YELLOW"%s"RESET, YELLOWERROR);
	ft_printf(YELLOW"%s"RESET, GETRESFAIL);
	if (g_iamerror.badressyn)
		ft_printf("Line %u: "YELLOW"%s"RESET, g_iamerror.badressyn, BADRESSYN);
	if (g_iamerror.badressize)
		ft_printf("Line %u: "YELLOW"%s"RESET, g_iamerror.badressize, \
		BADRESSIZE);
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
**
** For the bonus, the new orphansprites error sets each bit in the
** orphansprites variable when a sprite is found without a loaded texture.
** If any are set, we return an error message and check each bit to print all
** the affected sprite numbers on the terminal.
*/

void	texerrors(void)
{
	int		stype;

	ft_printf(RED"%s"RESET, REDERROR);
	gettexfail();
	texreaderror();
	if (g_iamerror.texpathfail)
		texpatherrors();
	if (g_iamerror.orphansprites)
	{
		stype = 2;
		ft_printf(RED"%s"RESET, ORPHANSPR);
		while (stype <= 9)
		{
			if (isbitset(g_iamerror.orphansprites, stype - 2))
				ft_printf("%d ", stype);
			stype++;
		}
		write(1, "\n", 1);
	}
}

/*
** The printerrors function refers to a global struct called iamerror to check
** whether flags have been set signalling certain errors. The flags are set by
** the program as they occur. If set, the corresponding error messages will
** be printed on screen.
**
** Map errors will not be printed unless a map has been found and checked.
**
** If no map was found, a no map found error will be displayed.
**
** There is a slight quirk here. Because the texture paths MUST be properly
** retrieved before the map begins, we don't look for the map until they have
** all been retrieved. This means that even if there *is* a valid map in the
** file, if a wall texture path hasn't been retrieved due to a bad syntax
** error, the map will never be registered, as the parser will go to the end of
** the file looking for the wall texture path first, and a false no map found
** error may thus be displayed alongside the texture path error.
**
** To control for this, I use the mapchecked flag, which really indicates
** whether the all of the wall texture paths were actually retrieved or not.
** Thus, the nomapfound error will only be displayed if the mapchecked flag
** is also true. Because of this, if the wall texture retrieval fails due to
** bad syntax, even if there is no map, a no map error will NOT be displayed
** as the parser will not look for a map until the texture path error is fixed.
** If it's fixed and there is still no map, obviously, you'll get the no map
** error.
*/

void	printerrors(void)
{
	if (g_iamerror.toomanyargs)
		ft_printf(RED"%s%s"RESET, REDERROR, TOOMANYARGS);
	if (g_iamerror.cubfilenotfound)
		ft_printf(RED"%s%s"RESET, REDERROR, CUBNOTFOUND);
	if (g_iamerror.weirdfd)
		ft_printf(RED"%s%s"RESET, REDERROR, WEIRDFD);
	if (g_iamerror.couldnotclose)
		ft_printf(YELLOW"%s%s"RESET, YELLOWERROR, COULDNOTCLOSE);
	if (g_iamerror.mapchecked && g_iamerror.nomapfound)
		ft_printf(RED"%s%s"RESET, REDERROR, NOMAPFOUND);
	if (g_iamerror.getresfail)
		reserrors();
	if (g_iamerror.outofbounds[2] || g_iamerror.noplayer || \
	g_iamerror.badmap3line || g_iamerror.toomanyplayers[2] || \
	g_iamerror.maptoobig)
		maperrors();
	else if (texerrorconditions())
		texerrors();
	if (g_iamerror.cubpolice)
		cuberrors();
	if (g_iamerror.mallocfail)
		ft_printf(RED"%s%s"RESET, REDERROR, MALLOCFAIL);
	write(1, "\n", 1);
	return ;
}
