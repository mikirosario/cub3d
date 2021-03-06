/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/05 15:42:11 by miki             ###   ########.fr       */
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
# ifdef __APPLE__
#  include <CoreGraphics/CGDisplayConfiguration.h>
# endif
# include "cub3d.h"
# include "iamerror_bonus.h"
# include "printnotifications_bonus.h"
# include "music_bonus.h"
# define BONUSMAPCHRS " 0123456789/v*NnSsEeWw"

typedef	struct	s_line
{
	double	startx;
	double	starty;
	double	endx;
	double	endy;
}				t_line;

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

typedef struct	s_chisme
{
	t_imagedata	idle;
	t_imagedata	active;
	t_imagedata	*ptr[2];
}				t_chisme;

t_imagedata		g_ceilingimg;
t_imagedata		g_floorimg;
t_imagedata		g_doorrightimg;
t_imagedata		g_doorleftimg;
t_imagedata		g_sprt3img;
t_imagedata		g_sprt4img;
t_imagedata		g_sprt5img;
t_imagedata		g_sprt6img;
t_imagedata		g_sprt7img;
t_imagedata		g_sprt8img;
t_imagedata		g_sprt9img;
t_imagedata		g_potion;
t_imagedata		g_ruby;
t_imagedata		g_phrases;
t_imagedata		g_ending;
t_imagedata		g_portal;
t_imagedata		g_skybox;
t_lifebar		g_lifebar;
t_catsbane		g_catsbane;
t_chisme		g_chisme;
t_xraydata		g_xraydata;
t_line			g_door;

/*
** Bonus
*/

/*
** General Purpose
*/

int				ft_strcmp(const char *s1, const char *s2);
void			ft_copysprtlst(t_spritedata *copyto, t_spritedata *copyfrom);
void			ft_movesprttoback(t_spritedata *firstmem, t_spritedata *lstmem);
t_spritedata	*finddoor(int x, int y);

/*
** Draw
*/

void			drawtobuffer_bonus(unsigned int *buf, int pixel, \
				unsigned int xcolor);
void			yput_to_buffer(int x, int y, unsigned int *buf, \
				t_imagedata *img);

/*
** Timer
*/

double			msectime(void);
double			msec_diff(struct timeval *t0, struct timeval *t1);
void			reset_timer(struct timeval *t);

/*
** Game Config
*/

int				getftex(const char *line, unsigned int linenum, int *checked);
int				getctex(const char *line, unsigned int linenum, int *checked);
void			gettexfail(void);
int				sprarray(t_spritedata *list, t_spritedata ***array);
void			getanimationimgs(t_imagedata *simg);
void			getbonusteximg(void);
void			getbonussprites(void);
void			createhudimages(void);
int				makeportalanimation(t_imagedata *portal);
int				checkanimations(t_imagedata *simg);
void			animationtexerrors(t_imagedata *simg);
void			getbonusimgaddresses(t_raycasterdata *rdata);
void			loadui(void);
int				getanimationptrs(t_spritedata *sprt, t_imagedata *simg);
void			getalltexpointers(t_imagedata *img, int animations);
int				companimsizes(t_imagedata **simg);
int				doorcounter(unsigned int x, unsigned int y, char *c);
void			mapspecialdoors(void);
int				makephrases(t_imagedata *phrases);
int				makeending(t_imagedata *ending);
void			unfloodmap(char *flag);
int				raycaster_start(t_raycasterdata *rdata);

/*
** Raycaster
*/

int				raycaster_bonus(t_raycasterdata *rdata);
void			castwall(t_raycasterdata *rdata);
void			castdoors(t_raycasterdata *rdata);
void			cast_ceiling_floor(unsigned int *buf);
unsigned int	*choosetexture(t_raycasterdata *rdata);
int				hordoorhitcheck(void);
int				verdoorhitcheck(void);
void			castoneray(void);
int				drawskybox(int x, int pixel, t_raycasterdata *rdata);
int				teleporter(char *mapchr);

/*
** HUD
*/

int				usepotion(void);
void			spraycat(t_spritedata *sprite);
void			orentalk(int sprnum, double playerdistance);
void			marvintalk(int sprnum, double playerdistance);
void			displaygraphicsmode(void);
void			displayspeech(t_raycasterdata *rdata);
void			refreshpotions(unsigned int *buf);
void			refreshrubies(unsigned int *buf);
void			refreshchisme(unsigned int *buf, t_raycasterdata *rdata);
void			refreshcatsbane(unsigned int *buf, t_raycasterdata *rdata);

/*
** Animations
*/

void			animate(t_spritedata *sprite);
void			removesprite(t_spritedata *sprite);
void			activatedoor(t_raycasterdata *rdata);
void			countframes(time_t *timestart);
int				hordoorslide(void);
int				verdoorslide(void);
void			ending(t_raycasterdata *rdata);

/*
** Sound
*/

void			playtrack(char *track);
int				playsound(char *sound);
void			bossmusic(char sprite);

/*
** Mouse Flags
*/

int				mousepress(int button, int x, int y, void *param);
int				mouserelease(int button, int x, int y, void *param);
int				mousemove(int x, int y, void *param);

#endif
