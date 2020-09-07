/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:37:36 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/07 20:38:26 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Line intersect detector, finds where two lines intersect. Mathematic hell.
*/

int		findintersection(t_line *linea, t_line *lineb, double *xresult, double *yresult)
{
	double	a1;
	double	b1;
	double	c1;
	double	a2;
	double	b2;
	double	c2;
	double	det;
	double	xintersect;
	double	yintersect;

	a1 = linea->endy - linea->starty;
	b1 = linea->startx - linea->endx;
	c1 = (a1 * linea->startx + b1 * linea->starty);
	a2 = (lineb->endy - lineb->starty);
	b2 = (lineb->startx - lineb->endx);
	c2 = (a2 * lineb->startx + b2 * lineb->starty);
	det = a1 * b2 - a2 * b1;
	if (det)
	{
		xintersect = (b2 * c1 - b1 * c2)/det;
		yintersect = (a1 * c2 - a2 * c1)/det;
		*xresult = xintersect;
		*yresult = yintersect;
		return (1);
	}
	return (0);
}


/*
** Simple function to tell you whether a given bit is set in a byte. Another
** libft candidate. ;) Bit 0 is the rightmost bit.
*/

int				isbitset(unsigned char byte, int bit)
{
	unsigned char	mask;

	mask = (unsigned char)1 << bit;
	return (mask & byte);
}

/*
** This function is a generic, run-of-the-mill "free this memory and set the
** pointer to NULL" function that should really be in my libft by now. :p
*/

void			del(void *freethis)
{
	free(freethis);
	freethis = NULL;
}

/*
** This is a little function I've found very useful. It finds the next number
** from the position in a string passed as an argument.
**
** If your pointer is pointing to a number in a string, it will go through the
** number until the end and then go through any non-numerical characters after
** the number until it finds the next number or a NULL. If you're pointing to a
** part of the string that isn't a number, it will of course ignore the first
** while and directly go to the second one to find the next number.
**
** If it finds another number, it returns a pointer to it, otherwise it returns
** a NULL pointer. Great line saver. ^_^
**
** This is going in my libft.
*/

char			*getnextnum(char *num)
{
	while (*num && ft_isdigit(*num))
		num++;
	while (*num && !(ft_isdigit(*num)))
		num++;
	return (*num ? num : NULL);
}

/*
** This function converts a trgb color value into a little-endian hexadecimal
** color value. I'd give it the superpower of being able to choose the
** endianness, but that would be FIVE ARGUMENTS... Norminette, the bane of my
** existence. :p
*/

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
