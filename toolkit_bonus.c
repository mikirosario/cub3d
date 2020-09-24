/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:37:36 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/24 19:01:37 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Draws lines vertically to the buffer column by column.
*/

void			yput_to_buffer(int x, int y, unsigned int *buf, \
t_imagedata *img)
{
	int bx;
	int	tx;
	int	ty;

	tx = 0;
	while (tx < img->texw)
	{
		bx = x + y * g_config.screenw;
		ty = tx;
		while (ty < tx + img->texh * img->texw)
		{
			if (img->tex_ptr[ty] != 0xff000000)
				buf[bx] = img->tex_ptr[ty];
			bx += g_config.screenw;
			ty += img->texw;
		}
		x++;
		tx++;
	}
}

/*
** Simple function to tell you whether a given bit is set in a byte. Another
** libft candidate. ;) Bit 0 is the rightmost bit. Returns 1 if bit is set,
** otherwise returns 0.
*/

int				isbitset(unsigned int byte, int bit)
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
