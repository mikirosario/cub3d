/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/28 19:49:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/*
** For cub3d bonus I do a whole bunch of things I don't do in the basic
** version. To start with, let's remember this cardinal rule, from the project
** description:
** 
** "You are allowed to use other functions to complete the bonus part as long
** as their use is justified during your evaluation. You are also allowed to
** modify the expected scene file format to fit your needs. Be smart!"
** 
** With that, we invoke the following new libraries for the bonus part:
**
** <time.h>, for the frame counter. The MacOS core graphics library
** <CGDisplayConfiguration.h>, so we can retrieve the scaled display resolution
** for any Mac display elegantly. Whew! I feel better already! xD
*/

# include <time.h>
# include <CoreGraphics/CGDisplayConfiguration.h>
# include "cub3d.h"
# include "iamerror_bonus.h"

/*
** Raydir for leftmost ray (x = 0) and rightmost ray (x = w).
**
** The int p is the current y (vertical) position compared to the centre of the
** screen.
**
** The double posZ is the vertical position of the camera (midway up or down
** the screen);
**
** The double rowdistance is the horizontal distance from the camera to the
** floor or ceiling for a given row, with 0.5 * screenHeight being the midway
** point.
**
** The doubles floorstepx and floorstep y hold the real-world step vector to
** add for each x (parallel to camera plane).
**
** The doubles floorx and floory hold the real-world coordinates of the
** left-most column. It is updated as we step to the right.
*/

typedef struct	s_horizontalraydata
{
	double	raydirx0;
	double	raydiry0;
	double	raydirx1;
	double	raydiry1;
	int		p;
	double	posz;
	double	rowdistance;
	double	floorstepx;
	double	floorstepy;
	double	floorx;
	double	floory;
	int		cellx;
	int		celly;
	int		texx;
	int		texy;
	
}				t_xraydata;

t_imagedata	g_ceilingimg;
t_imagedata	g_floorimg;
t_imagedata	g_ceilingimg;
t_xraydata	g_xraydata;

/*
** Bonus
*/

void	countframes(time_t *timestart);
void	displaygraphicsmode(void);
void	cls(void);
void	cast_ceiling_floor(unsigned int *buf);
int		getftex(const char *line, unsigned int linenum);

#endif
