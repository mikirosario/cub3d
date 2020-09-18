/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/18 19:36:42 by mrosario         ###   ########.fr       */
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
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
#ifdef __APPLE__
# include <CoreGraphics/CGDisplayConfiguration.h>
#endif
# include "cub3d.h"
# include "iamerror_bonus.h"
# include "printnotifications_bonus.h"

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

/*
** This is for playing around with ray data within a map square without
** affecting the ray data used by the renderer, in order to do calculations to
** determine the ray's trajectory *within* a square (rather than its
** square-to-square path, as dda normally does in this raycaster) to resolve the
** special interactions created by doors. :) It would not need to exist if not
** for Norminette. :p Note that even mapx is actually a double here. Like I
** said, it's intra-square data. ;)
*/

typedef struct	s_localraydata
{
	double	mapx;
	double	mapy;
	double	perpwalldist;
	double	wallx;
	double	raydirx;
	double	raydiry;
	double	xintersect;
	double	yintersect;
}				t_localraydata;

typedef struct	s_lifebar
{
	t_imagedata	fullheart;
	t_imagedata	halfheart;
	t_imagedata	emptyheart;
	t_imagedata	*ptr[3];
}				t_lifebar;

typedef struct	s_catsbane
{
	t_imagedata	idle;
	t_imagedata	attack;
	t_imagedata	*ptr[2];
}				t_catsbane;


typedef struct	s_door
{
	//t_raydata	raydata;
	//double		doorend;
	//char		*posmap;
}				t_door;

t_imagedata		g_ceilingimg;
t_imagedata		g_floorimg;
t_imagedata		g_doorrightimg;
t_imagedata 	g_doorleftimg;
t_imagedata		g_sprt3img;
t_imagedata		g_sprt4img;
t_imagedata		g_sprt5img;
t_imagedata		g_sprt6img;
t_imagedata		g_sprt7img;
t_imagedata		g_sprt8img;
t_imagedata		g_sprt9img;
t_imagedata		g_potion;
t_lifebar		g_lifebar;
t_catsbane		g_catsbane;
t_xraydata		g_xraydata;
t_line			g_door;

/*
** Bonus
*/

void	countframes(time_t *timestart);
void	displaygraphicsmode(void);
void	cls(void);
void	cast_ceiling_floor(unsigned int *buf);
int		getftex(const char *line, unsigned int linenum);
int		getctex(const char *line, unsigned int linenum);
void	gettexfail(void);
int		sprarray(t_spritedata *list, t_spritedata ***array);
int		raycaster_start(t_raycasterdata *rdata);
int		raycaster_bonus(t_raycasterdata *rdata);
void	getanimationimgs(t_imagedata *simg);
int		checkanimations(t_imagedata *simg);
void	animationtexerrors(t_imagedata *simg);
int		getanimationptrs(t_spritedata *sprt, t_imagedata *simg);
int		companimsizes(t_imagedata **simg);
void	ft_copysprtlst(t_spritedata *copyto, t_spritedata *copyfrom);
void	ft_movesprttoback(t_spritedata *firstmem, t_spritedata *lstmem);
int		usepotion(void);
void	animate(t_spritedata *sprite);
void	removesprite(t_spritedata *sprite);
void	animate(t_spritedata *sprite);
int		doorcounter(unsigned int x, unsigned int y, char *c);
int		findintersection(t_line *linea, t_line *lineb, double *xresult, double *yresult);
void	ft_hypotenuse(t_triangle *triangle);
void	activatedoor(t_raycasterdata *rdata);
int		hordoorhitcheck(void);
int		verdoorhitcheck(void);
int		hordoorslide(void);
int		verdoorslide(void);
void	castoneray(int x);
double	msectime(void);
double	msec_diff(struct timeval *t0, struct timeval *t1);
void	reset_timer(struct timeval *t);
void	spraycat(t_spritedata *sprite);
void	sighandler(pid_t signum);

#endif
