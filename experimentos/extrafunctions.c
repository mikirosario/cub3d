/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extrafunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 05:09:59 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/24 19:00:51 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PI 3.1415926535 

typedef	struct	s_line
{
	double	startx;
	double	starty;
	double	endx;
	double	endy;
}				t_line;

typedef struct	s_triangle
{
	double	hypotenuse;
	double	angletheta;
	double	adjacent;
	double	anglealpha;
	double	opposite;
	double	anglebeta;
}				t_triangle;


/*
** This function will draw lines of pixels to the buffer starting at the x, y
** position passed as arguments, from top to bottom row by row, excluding
** transparent colors. Note that on MAC this seems to be marked by making the
** A channel 00, and on Linux by making it FF. :p I don't know why that is.
**
** It's unprotected, so make sure your image will fit into your buffer. :p
**
** This function has a bug that for some reason causes the game to crash with
** images without transparency O_O. BUGGED; FIX BEFORE IMPLEMENTING.
*/

void			xput_to_buffer(int x, int y, unsigned int *buf, t_imagedata *img)
{
	int bx;
	int	tx;
	int	ty;

	ty = 0;
	while (ty < img->texh)
	{
		bx = x + (y * g_config.screenw);
		tx = ty * img->texw;
		while (tx < ty * img->texw + img->texw)
		{
			if (img->tex_ptr[tx] != 0xff000000)
				buf[bx] = img->tex_ptr[tx];
			bx++;
			tx++;
		}
		y++;
		ty++;
	}
}

/*
** Function to set a bit to 1.
*/

unsigned int	setbit(unsigned int byte, int bit)
{
	unsigned char	mask;

	mask = (unsigned char)1 << bit;
	return (mask | byte);
}

void	ft_hypotenuse(t_triangle *triangle)
{
	triangle->anglebeta = PI - triangle->angletheta - triangle->anglealpha;
	triangle->hypotenuse = (sin(triangle->anglealpha) * 0.5) / sin(triangle->anglebeta);
}

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