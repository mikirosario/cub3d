/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:31:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/05 20:10:31 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

extern error_t	g_iamerror;

/*
** This function assigns the player's starting position and configures the
** associated initial data set - player position (posX, posY), relative camera
** plane position and orientation (planeX, planeY), player orientation (dirX,
** dirY).
**
** Initial player position is simply the location where the player was found
** in map, offset by 0.5 in both axes to bring the player to the centre of the
** square. The rest of the data will depend on initial player orientation,
** which is encoded in the letter representing the player character, where N
** is for north facing, S is for south facing, E is for east facing, and W is
** for west facing. Each orientation has its own set of starting data.
**
** Finally, after the starting position data is set, the character in the map
** is changed to A. This will tell the floodfill function, which will be used
** subsequently to check whether the player is within an area bounded by walls
** or not, that this spot needs to be checked.
**
** As for why this function looks like an it was run over by a car, there is
** is a simple answer for that. Norminette made me do it. This is a 42 school
** project, and we are limited to functions of no more than 25 lines. I had to
** mutilate this function to the form you see here to get it to fit. The 'real'
** clean function it is based off of is very straightforward and looks like
** this (^_^):
**
** void		configureplayer(unsigned int x, unsigned int y, char *playerchar)
** {
**	g_player.posX = (double)x + 0.5;
**	g_player.posY = (double)y + 0.5;
**	if (*playerchar == 'N' || *playerchar == 'n')
**	{
**		g_player.dirX = (double)0;
**		g_player.dirY = (double)-1;
**		g_player.planeX = (double)0.66;
**		g_player.planeY = (double)0;
**	}
**	else if (*playerchar == 'S' || *playerchar == 's')
**	{
**		g_player.dirX = (double)0;
**		g_player.dirY = (double)1;
**		g_player.planeX = (double)-0.66;
**		g_player.planeY = (double)0;
**	}
**	else if (*playerchar == 'E' || *playerchar == 'e')
**	{
**		g_player.dirX = (double)1;
**		g_player.dirY = (double)0;
**		g_player.planeX = (double)0;
**		g_player.planeY = (double)0.66;
**	}
**	else if (*playerchar == 'W' || *playerchar == 'w')
**	{
**		g_player.dirX = (double)-1;
**		g_player.dirY = (double)0;
**		g_player.planeX = (double)0;
**		g_player.planeY = (double)-0.66;
**	}
**	*playerchar = 'A';
** }
*/

void	configureplayer(unsigned int x, unsigned int y, char *playerchar)
{
	g_player.posX = (double)x + 0.5;
	g_player.posY = (double)y + 0.5;
	if (*playerchar == 'N' || *playerchar == 'n' || \
	*playerchar == 'S' || *playerchar == 's')
	{
		g_player.dirX = (double)0;
		g_player.planeY = (double)0;
		g_player.dirY = *playerchar == 'N' || *playerchar == 'n' ? \
		(double)-1 : (double)1;
		g_player.planeX = *playerchar == 'N' || *playerchar == 'n' ? \
		(double)0.66 : (double)-0.66;
	}
	else if (*playerchar == 'E' || *playerchar == 'e' || \
	*playerchar == 'W' || *playerchar == 'w')
	{
		g_player.dirY = (double)0;
		g_player.planeX = (double)0;
		g_player.dirX = *playerchar == 'E' || *playerchar == 'e' ? \
		(double)1 : (double)-1;
		g_player.planeY = *playerchar == 'E' || *playerchar == 'e' ? \
		(double)0.66 : (double)-0.66;
	}
	*playerchar = 'A';
}

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
			{
				if ((foundplayer += 1) > 1)
					return (toomanyplayers(x, y, foundplayer));
				else
					configureplayer(x, y, maplistdir(x, y));
			}
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
** and place it onto a sprite list called spriteList.
**
** If the line being analysed is the first line (!y) or the last line (endmap)
** and the char found is any of those in the mapchr list from N onward
** (NnSsEeWw) then the whole map will be considered invalid and, after freeing
** any memory that has been reserved, the function will order the calling
** function to abort.
*/

int		linecheck(char *line, int y, char *mapchrs)
{
	unsigned int	x;
	char			*match;
	t_list			*listptr;

	x = 0;
	if (!line)
		return (0);
	while (x < UINT_MAX && line[x] && (match = ft_strchr(mapchrs, line[x])))
		x++;
	g_iamerror.uintxmax = x == UINT_MAX ? 1 : 0;
	if (!g_iamerror.uintxmax && x > 0 && !line[x])
	{
		listptr = ft_lstnew(((char *)ft_strdup(line)));
		listptr->len = ft_strlen((const char *)line);
		!y ? g_config.Map = listptr : ft_lstadd_back(&g_config.Map, listptr);
	}
	else
		return (0);
	return (1);
}

int		checkmap(unsigned int y, char *mapchrs)
{
	char foundplayer;

	foundplayer = 0;
	if (y < 2)
		return (-2);
	if ((foundplayer = playerandspritescheck(foundplayer, mapchrs)) > 1)
		return (-4);
	else if (!foundplayer)
		return (-3);
	ft_printf(MAGENTA"\n**** MAP RETRIEVED ****\n"RESET);
	printmapbytes();
	ft_printf(MAGENTA"\n**** SPRITES RETRIEVED ****\n"RESET);
	printsprites();
	if (!(floodfill()))
		return (-1);
	return (1);
}

int		makemaplist(int fd, char *firstline)
{
	unsigned int	y;
	char			*line;
	char			endfile;
	char			*mapchrs;

	y = 0;
	endfile = 0;
	line = firstline;
	mapchrs = " 012NnSsEeWw";
	while (y < UINT_MAX && linecheck(line, y, mapchrs) && !endfile)
	{
		del(line);
		if (!(ft_get_next_line(fd, &line)))
			endfile = 49;
		if (!line)
			g_iamerror.mallocfail = 1;
		y++;
	}
	line ? del(line) : line;
	if (y == UINT_MAX)
		g_iamerror.uintymax = 1;
	g_config.mapH = !endfile || !line || y == g_iamerror.uintymax || \
	g_iamerror.uintxmax ? --y : y;
	return (checkmap(y, mapchrs));
}
