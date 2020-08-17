/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlinkedlists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:32:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/17 15:14:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern error_t g_iamerror;

void	printsprites(void)
{
	unsigned int	y;
	spriteData_t	*sprtlistptr;

	y = 0;
	sprtlistptr = g_config.spriteList;
	if (!sprtlistptr)
		ft_printf(GREEN"NO SPRITES LOADED\n"RESET);
	else
	{
		while (sprtlistptr)
		{
			ft_printf(GREEN"\nSprite %5u: X %5u Y %5u Sprite Type: %c"RESET, \
			y + 1, (unsigned int)(round(sprtlistptr->posX)), \
			(unsigned int)(round(sprtlistptr->posY)), sprtlistptr->spriteType);
			sprtlistptr = sprtlistptr->next;
			y++;
		}
		ft_printf(YELLOW"\nTotal Number of Sprites: %d\n"RESET, y + 1);
	}
}

void	printbyteuse(unsigned int bytes)
{
	if (bytes < 100000)
		ft_printf(GREEN"%36cTotal Bytes Used By This Map: %d (^_^)\n"RESET, \
		'\0', bytes);
	else if (bytes < 500000)
		ft_printf(YELLOW"%36cTotal Bytes Used By This Map: %d (´･_･｀)\n"RESET, \
		'\0', bytes);
	else
		ft_printf(RED"%36cTotal Bytes Used By This Map: %d (°o°)\n"RESET, \
		'\0', bytes);
}

void	printmap(void)
{
	unsigned int	y;
	t_list			*lstptr;

	lstptr = g_config.Map;
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
	unsigned int	bytes;
	t_list			*lstptr;

	lstptr = g_config.Map;
	y = 0;
	bytes = 0;
	if (!lstptr)
		ft_printf(RED"\nNO MAP LOADED\n");
	else
	{
		while (lstptr)
		{
			ft_printf(MAGENTA"\nBytes %10u "BLUE"Line # %10u "RESET"%s", \
			(lstptr->len + 1 + sizeof(t_list)), (y + 1 + g_iamerror.premaplines), \
			(char *)lstptr->content);
			bytes += (lstptr->len + 1 + sizeof(t_list));
			lstptr = lstptr->next;
			y++;
		}
		ft_printf(GREEN"\n%36cTotal Map Rows: %d\n"RESET, '\0', y);
		printbyteuse(bytes);
	}
}
