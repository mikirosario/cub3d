/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:17:25 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/11 15:27:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Degrees to radians. Returns 0 if argument is not a valid degree.
*/

double	ft_degtorad(double a)
{
	if (a >= -360 && a <= 360)
	{
		a = a * M_PI / 180.0;
		return (a);
	}
	return (0);
}

/*
** Radians to degrees. Returns 0 if argument is not a valid radian.
*/

double	ft_radtodeg(double a)
{
	if (a >= -6.28319 && a <= 6.28319)
	{
		a = a * 180.0 / M_PI;
		return (a);
	}
	return (0);
}

/*
** Rounds double n to prec decimal places towards nearest integer.
** If prec is given as 0 or less than 0, rounds to nearest whole number.
** If prec is given as greater than 15 (maximum decimal places in a
** double) it is reduced to 15.
*/

double	ft_round(double n, int prec)
{
	double	dec;

	dec = 10;
	if (prec <= 0)
		n = round(n * 1) / 1;
	else
	{
		if (prec > 15)
			prec = 15;
		while (--prec)
			dec *= 10;
		n = round(n * dec) / dec;
	}
	return (n);
}

/*
** Calculates new positions for x and y in 2D rotation matrix applying
** adeg degrees (these are converted to radians within the function).
** Positive degrees are clockwise rotation; negative degrees are
** counterclockwise rotation.
**
** Prec specifies the number of decimal points of precision desired,
** from 0 to 15. If prec is set below 0 it will default to 0; if set
** above 15 it will default to 15. If adeg is not a valid degree of
** rotation (between -360 and 360), it will be set to 0. Requires
** valid double pointer to two contiguous reserved memory spaces
** of the double type.
*/

int		ft_rotate_2d(double x, double y, double adeg, double prec, double *ptr)
{
	double	arad;

	if (!ptr)
		return (-1);
	if (!(adeg >= -360 && adeg <= 360))
		adeg = 0;
	if (prec < 0)
		prec = 0;
	else if (prec > 15)
		prec = 15;
	arad = ft_degtorad(adeg);
	(*(ptr + 0)) = ft_round((x * (cos(arad))) + (y * (sin(arad))), prec);
	(*(ptr + 1)) = ft_round((y * (cos(arad))) - (x * (sin(arad))), prec);
	return (0);
}
