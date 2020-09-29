/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:31:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/29 21:58:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

extern t_error	g_iamerror;

/*
** This function checks each map line for sprites ('2') or players ('NSEW').
** If a sprite is found, it is sent to spritecounter to be processed and
** configured. If a player is found and it is the first player found, it is
** sent to configureplayer to be processed and configured. If a player is
** found and it is the second player found, it is sent to the too many
** players function for error management, and the function then aborts and
** returns the number of players to the calling function.
**
** This function had to be needlessly split in two due to being normed. :p
** Here is the original function:
**
** {
**	t_list			*map;
**	unsigned int	x;
**	unsigned int	y;
**	char			c;
**
**	y = 0;
**	while ((map = maplistmem(y)))
**	{
**		x = 0;
**		while ((c = (*(char *)(map->content + x))))
**		{
**			if (c == '2')
**				spriteCounter((double)x, (double)y, c);
**			else if ((ft_strchr(mapchrs, c)) >= mapchrs + 4)
**			{
**				if ((foundplayer += 1) > 1)
**				{
**					g_iamerror.toomanyplayers[0] = x;
**					g_iamerror.toomanyplayers[1] = y;
**					return (foundplayer);
**				}
**				else
**					configureplayer(x, y, maplistdir(x, y));
**			}
**			x++;
**		}
**		y++;
**	}
**	return (foundplayer);
** }
*/

char	playerandspritescheck(char foundplayer, char *mapchrs)
{
	t_list			*map;
	unsigned int	x;
	unsigned int	y;
	char			c;

	y = 0;
	while ((map = maplistmem(y)))
	{
		x = 0;
		while ((c = (*(char *)(map->content + x))))
		{
			if (c == '2')
				spritecounter((double)x, (double)y, c);
			else if ((ft_strchr(mapchrs, c)) >= mapchrs + 4)
				if (!(playercounter(x, y, ++foundplayer)))
					return (foundplayer);
			x++;
		}
		y++;
	}
	return (foundplayer);
}

/*
** This is the function that checks a map line for validity. A line is invalid
** if any character not in the mapchrs string is found, or if the line is empty.
** A line is valid if only mapchrs have been found and the last character seen
** is NULL.
**
** The function runs through the line so long as NULL is not found AND a mapchr
** is found. Spaces ARE considered valid mapchars, but TAB or any similar
** elements are NOT as the way they are displayed is user defined.
**
** If a sprite is found, spriteCounter will be called to record its position
** and place it onto a sprite list called spritelist.
**
** If the line being analysed is the first line (!y) or the last line (endmap)
** and the char found is any of those in the mapchr list from N onward
** (NnSsEeWw) then the whole map will be considered invalid and, after freeing
** any memory that has been reserved, the function will order the calling
** function to abort.
**
** And there is one more little trick up this little function's sleeve. What
** happens if a mean or thoughtless user takes advantage of this program to
** reserve endless amounts of memory by passing a gigantic map to the program?
** Fret not, for every map line reserved and assigned we record its memory
** usage in the memusage variable, expressed in bytes. This will be strlen + 1
** (for the null terminator), plus the size of the t_list member linking it.
**
** Now, knowing that 42 Madrid Macs have 8GB of RAM, we can go pretty high.
** I use uints to iterate through strings, so we also don't want to go above
** the UINTMAX on any map axis, no matter how much memory we reserve.
** Originally I controlled for that, but then I did the calculations.
**
** Any given map line must be at *least* three characters long to enclose the
** player by walls (a hallway), which weighs four bytes when we account for the
** NULL terminator, plus the size of the t_list struct that links it and stores
** information about it (24 bytes). Yeah, vertical maps weigh more than
** horizontal maps... just deal with it. ;p
**
** So, at minimum, every line will weigh at *least* 28 bytes. C UINTMAX is
** 4,294,967,295, which, multiplied by 28, gives us a staggering
** 120,259,084,260 bytes for a map that is just one long vertical hallway
** before reaching the UINTMAX. That is about 120 gigabytes. O_O Now, for a map
** that is one long horizontal hallway, it would weigh less, "only" about 12.8
** gigabytes, because most of the memory would be taken up by the strings
** instead of the structs. But... it still just seems a bit *excessive*
** somehow. xD
**
** 0.2 megabytes seems like a nice, safe number to settle on, and should be
** MORE than enough for anyone serious. ;p Maps of this weight or less will
** also always be well within the UINTMAX, so no worries there. 1.44 megabytes
** gives us a vertical hallway map of about 51438 lines (28 bytes per
** line), and a horizontal hallway map of about 4,319,916 characters (
** that's 100000000 - size of t_list, 24, - 1, the NULL terminator, times 3
** lines). So we get a waaaaay bigger horizontal map than vertical map for the
** same memory use because I went with linked lists. ;) D'oh! No matter, just
** one of those newbie quirks.
**
** I will cap the amount of memory I'll allow the user to occupy
** with their map design to 200,000 bytes.
**
** If the map needs more than that, I will abort and scold the user with an
** unfriendly maptoobig error. :p Since this will always keep me well below
** UINTMAX on both axes, I will do away with the uintmax errors and define the
** MAPMEMCAP in cub3d.h so it can be easily changed there in the future.
**
** Admittedly, my highly optimized program takes a second even to parse a
** 0.2 MB map, so this may also have something to do that being the limit. xD
*/

int		linecheck(char *line, unsigned int y, char *mapchrs)
{
	unsigned int	x;
	char			*match;
	t_list			*listptr;

	x = 0;
	if (!line)
		return (0);
	while (x <= MAPMEMCAP && line[x] && (match = ft_strchr(mapchrs, line[x])))
		x++;
	if ((g_iamerror.memusage += x + 1) <= MAPMEMCAP && x > 0 && !line[x])
	{
		listptr = ft_lstnew(((char *)ft_strdup(line)));
		listptr->len = ft_strlen((const char *)line);
		!y ? g_config.maplist = listptr : ft_lstadd_back(&g_config.maplist, \
		listptr);
	}
	else
		return (0);
	return (1);
}

int		checkmap(char *mapchrs, char endfile)
{
	char foundplayer;

	foundplayer = 0;
	if (!endfile)
		return(-7);
	if (g_iamerror.mallocfail)
		return (-6);
	if (g_iamerror.memusage > MAPMEMCAP)
		return (-5);
	if (g_config.maph < 2)
		return (-2);
	if ((foundplayer = playerandspritescheck(foundplayer, mapchrs)) > 1)
		return (-4);
	else if (!foundplayer)
		return (-3);
	ft_printf(MAGENTA"\n**** MAP RETRIEVED ****\n"RESET);
	printmapbytes();
	ft_printf(MAGENTA"\n**** SPRITES RETRIEVED ****\n"RESET);
	printsprites();
	ft_printf(GREEN"\n**** CHECKING MAP... ****\n"RESET);
	if (!(floodfill()))
		return (-1);
	ft_printf(GREEN"\n**** LOADING MAP... ****\n");
	return (1);
}

/*
** If we end the maplist maker with lnchk, it means we ended the map at EOF,
** because the last line we checked was a valid mapline and so only endfile
** could have terminated the while.
**
** If we end with !lnchk, it means we ended the map before EOF and there are
** still lines below it. The new gatekeeper regime will analyse these lines to
** determine whether or not they are acceptable.
*/

int		makemaplist(int fd, char *firstline)
{
	unsigned int	y;
	char			*line;
	char			endfile;
	int				lnchk;

	y = 0;
	endfile = 0;
	line = firstline;
	while ((lnchk = linecheck(line, y, MAPCHRS)) && !endfile)
	{
		del(line);
		if (!(ft_get_next_line(fd, &line)))
			endfile = 1;
		if (!line)
			g_iamerror.mallocfail = 1;
		y++;
	}
	if(!lnchk)
		endfile = endcub(line, endfile);
	line ? del(line) : line;
	g_config.maph = !lnchk || g_iamerror.memusage > MAPMEMCAP ? --y : y;
	if (!maparray())
		g_iamerror.mallocfail = 1;
	return (checkmap(MAPCHRS, endfile));
}
