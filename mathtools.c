/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathtools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 05:09:59 by mikiencolor       #+#    #+#             */
/*   Updated: 2020/09/21 05:11:01 by mikiencolor      ###   ########.fr       */
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