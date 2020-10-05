/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gatekeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:00 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/05 13:16:33 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

extern t_error	g_iamerror;

int		isparam(char *cubchr, char *line)
{
	if (((*cubchr == 'N' || *cubchr == 'n') && \
	(*(line + 1) == 'O' || (*(line + 1) == 'o'))) || \
	((*cubchr == 'S' || *cubchr == 's') && \
	(*(line + 1) == 'O' || (*(line + 1) == 'o'))) || \
	((*cubchr == 'W' || *cubchr == 'w') && \
	(*(line + 1) == 'E' || (*(line + 1) == 'e'))) || \
	((*cubchr == 'E' || *cubchr == 'e') && \
	(*(line + 1) == 'A' || (*(line + 1) == 'a'))) || \
	((*cubchr == 'R' || *cubchr == 'r')) || \
	((*cubchr == 'S' || *cubchr == 's')) || \
	((*cubchr == 'F' || *cubchr == 'f')) || \
	((*cubchr == 'C' || *cubchr == 'c')))
		return (1);
	return (0);
}

/*
** The police report tells us how many parameters we managed to find. This will
** help the user identify where the misconfiguration in their cub file is when
** they get a cub error, as we will print any missing parameters for them.
**
** There happen to be 8 parameters we need to check before the map file is
** loaded, and there happen to be 8 bits in a byte. You know what that means...
** Time to practise bitshifting. ;) I'll use my new bit setting and reading
** functions here. We'll set a bit to 1 for every parameter we've found in the
** g_iamerror.gotparam unsigned char.
**
** We'll also reset the results table to 0 to throw all the retrieval errors,
** since a cub error means we couldn't retrieve anything.
*/

void	policereport(int *result, int *checked)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (checked[i])
			g_iamerror.gotparam = setbit(g_iamerror.gotparam, i);
		i++;
	}
	ft_bzero(result, 8 * 4);
}

int		sumresarray(int *result)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 8)
		sum += result[i++];
	return (sum);
}

/*
** Checks for valid cub lines. There are two types of valid cubline. We accept
** empty lines (lines that consist of a NULL). We also accept lines with valid
** cub parameters, as long as that parameter has not already been passed. For
** the first type we return (1). For the second type we return (2). The second
** type will become invalid if, at the end of the cubread while, the sum of the
** result array has not gone up by 1.
**
** Otherwise, the line is invalid and will be placed under arrest by the cub
** police.
*/

int		validitycheck(char *line, int sum, int linenum)
{
	char *singlecubchrs;
	char *cubchr;

	singlecubchrs = "RSFCrsfcNSEWnsew";
	if (!(*line))
		return (1);
	if (sum > 7 && ismap(line))
		return (1);
	line = ft_skipspaces(line);
	if (!(cubchr = (ft_strchr(singlecubchrs, *line))))
	{
		g_iamerror.cubpolice = 1;
		g_iamerror.badline = linenum;
		return (0);
	}
	else if (isparam(cubchr, line))
		return (2);
	g_iamerror.cubpolice = 1;
	g_iamerror.badline = linenum;
	return (0);
}

/*
** These functions exist because I've been informed that the predominant
** interpretation of the project instructions is that the map must end the file,
** meaning nothing is allowed below the map in the file, and that duplicate
** parameter declarations should not be allowed.
**
** Before this modification, my parser was liberal and tolerant of strange text
** floating around. It retrieved the first parameter it found and ignored any
** subsequent parameters, leaving them free to live their lives as they liked.
** It held hands with the other functions and sang songs about fraternal love.
**
** Those naive and happy days are now over. Henceforth, all parameters in the
** .cub file must obey the law, under penalty of DEATH. A new error flag has
** arisen called cubpolice. If the cubpolice complain about a .cub file, the
** program will be terminated with EXTREME prejudice. You have been warned.
*/

int		endcub(char *line, int endfile)
{
	if (line && endfile && (*line))
		endfile = 0;
	if (!endfile)
		g_iamerror.badendcub = 1;
	return (endfile);
}
