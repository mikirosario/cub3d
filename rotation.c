/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:17:25 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/06 16:03:34 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
** Degrees to radians. Returns 0 if argument is not a valid degree.
*/
double ft_degtorad(double a)
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
double ft_radtodeg(double a)
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
double ft_round(double n, int prec)
{
    double dec = 10;

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
    return(n);
    
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
int ft_rotate_2D(double x, double y, double adeg, double prec, double *ptr)
{
    double arad;
    
    if (!ptr)
        return (-1);
    if (!(adeg >= -360 && adeg <= 360))
        adeg = 0;
    if (prec < 0)
        prec = 0;
    else if (prec > 15)
        prec = 15;
    arad = ft_degtorad(adeg);
    //o ptr[0][0], ptr[0][1]
    (*(ptr + 0)) = ft_round((x*(cos(arad))) + (y*(sin(arad))), prec);
    (*(ptr + 1)) = ft_round((y*(cos(arad))) - (x*(sin(arad))), prec);
    return (0);
}

/*int main(void)
{
    //Hacer función de rotación de matriz
    
    double x = 1;
    double y = 1;
    double adeg = -8;
    double a = 0.785398;
    double x2;
    double y2;
    double r = 1;
    double res;
    double *xyNew;

    xyNew = malloc(2 * sizeof(double));
    
    ___________
    printf("%f Degrees = Radian %f\n", adeg, ft_degtorad(adeg));
    printf("%f Radians = Degrees %f\n", a, ft_radtodeg(a));
    res = (r*(cos(0)*cos(a)));
    //negativos?
    res = ft_degtorad(adeg);
    res = ft_round(res, 6);
    printf("%f\n", res);
    x2 = ft_round((x*(cos(a))) - (y*(sin(a))), 6);
    y2 = ft_round((y*(cos(a))) + (x*(sin(a))), 6);
    ___________
    
    ft_rotate_2D(x, y, adeg, 15, &xyNew);
    printf("%.15f, %.15f", xyNew[0], xyNew[1]);
    free(xyNew);

    return(0);
}*/
