/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gatekeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:00 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/01 21:23:04 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

extern t_error	g_iamerror;

int	sumresarray(int *result)
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

int	validitycheck(int *result, char *line, int sum, int linenum)
{
	char *singlecubchrs;
	char *cubchr;

	(void)result;

	singlecubchrs = "RSFCrsfcNSEWnsew";

	if (!(*line)) //inocente, se aceptan líneas vacías
		return (1);
	//culpable hasta que se demuestre inocente
	if (sum > 7 && ismap(line)) //mapline válida a partir de 3 parámetros
		return (1);
	line = ft_skipspaces(line);
	if (!(cubchr = (ft_strchr(singlecubchrs, *line)))) //nos saltamos los espacios y *line no es un cubchr, bien por ser otro chr o bien por ser NULL: CULPABLE
	{
		g_iamerror.cubpolice = 1;
		g_iamerror.badline = linenum;
		return (0);
	}
	//*line es un cubchr de los que tienen dos letras
	else if (   ((*cubchr == 'N' || *cubchr == 'n') && (*(line + 1) == 'O' || (*(line + 1) == 'o'))) || \
		((*cubchr == 'S' || *cubchr == 's') && (*(line + 1) == 'O' || (*(line + 1) == 'o'))) || \
		((*cubchr == 'W' || *cubchr == 'w') && (*(line + 1) == 'E' || (*(line + 1) == 'e'))) || \
		((*cubchr == 'E' || *cubchr == 'e') && (*(line + 1) == 'A' || (*(line + 1) == 'a'))) || \
		//line es un cubchr singular
		((*cubchr == 'R' || *cubchr == 'r')) || ((*cubchr == 'S' || *cubchr == 's')) || \
		((*cubchr == 'F' || *cubchr == 'f')) || ((*cubchr == 'C' || *cubchr == 'c'))  )
			return (2); //line consta de uno o dos cubchrs válidos
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

int	endcub(char *line, int endfile)
{
	if (line && endfile && (*line)) //si primera línea existe y ya es eof y no es nulo, mapa NO ES endfile
		endfile = 0;
	if (!endfile)
		g_iamerror.badendcub = 1;
	return (endfile);
}