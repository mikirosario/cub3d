/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlinkedlists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:32:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 06:49:09 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_error g_iamerror;

void	printsprites(void)
{
	unsigned int	y;
	t_spritedata	*sprtlistptr;

	y = 0;
	sprtlistptr = g_config.spritelist;
	if (!sprtlistptr)
		ft_printf(GREEN"NO SPRITES LOADED\n"RESET);
	else
	{
		while (sprtlistptr)
		{
			ft_printf(GREEN"\nSprite %5u: X %5u Y %5u Sprite Type: %c"RESET, \
			y + 1, (unsigned int)(round(sprtlistptr->posx)), \
			(unsigned int)(round(sprtlistptr->posy)), sprtlistptr->spritetype);
			sprtlistptr = sprtlistptr->next;
			y++;
		}
		ft_printf(YELLOW"\nTotal Number of Sprites: %d\n"RESET, y);
	}
}

void	printbyteuse(unsigned int y)
{
	unsigned int	bytes;

	bytes = g_iamerror.memusage + ((sizeof(t_list) * y) + \
	((sizeof(char *) * y) + 1));
	if (g_iamerror.memusage < MAPMEMCAP * 0.5)
		ft_printf(GREEN"%36cTotal Bytes Used By This Map: %d (^_^)\n"RESET, \
		'\0', g_iamerror.memusage);
	else if (g_iamerror.memusage < MAPMEMCAP * 0.75)
		ft_printf(YELLOW"%36cTotal Bytes Used By This Map: %d (´･_･｀)\n"RESET, \
		'\0', g_iamerror.memusage);
	else
		ft_printf(RED"%36cTotal Bytes Used By This Map: %d (°o°)\n"RESET, \
		'\0', g_iamerror.memusage);
	ft_printf("%36cTotal Bytes Used by Map, Linked List and Map Array: %d\n", \
	'\0', bytes);
}

void	printmap(void)
{
	unsigned int	y;
	t_list			*lstptr;

	lstptr = g_config.maplist;
	y = 0;
	if (!lstptr)
		ft_printf(RED"\nNO MAP LOADED\n");
	else
	{
		while (lstptr)
		{
			ft_printf(BLUE"\n%10u "RESET"%s", \
			(y + 1 + g_iamerror.premaplines), \
			(char *)lstptr->content);
			lstptr = lstptr->next;
			y++;
		}
		ft_printf(GREEN"\n%12cTotal Map Rows: %d\n"RESET, '\0', y);
	}
}

void	printmapbytes(void)
{
	unsigned int	y;
	t_list			*lstptr;

	lstptr = g_config.maplist;
	y = 0;
	if (!lstptr)
		ft_printf(RED"\nNO MAP LOADED\n");
	else
	{
		while (lstptr)
		{
			ft_printf(MAGENTA"\nBytes %10u "BLUE"Line # %10u "RESET"%s", \
			(lstptr->len + 1), (y + 1 + g_iamerror.premaplines), \
			(char *)lstptr->content);
			lstptr = lstptr->next;
			y++;
		}
		ft_printf(GREEN"\n%36cTotal Map Rows: %d\n"RESET, '\0', y);
		printbyteuse(y - 1);
	}
}
