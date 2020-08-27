/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/27 17:43:17 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** This library is absolutely necessary to retrieve the display resolution
** from our Macs, but we are banned from using it. Shame! Shame! Let this
** serve as an eternal reminder of the indignity...
** #include <CoreGraphics/CGDisplayConfiguration.h>
*/

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <string.h>
# include "./libft/libft.h"
# include "iamerror.h"
# include "printnotifications.h"
# include <fcntl.h>
# include <unistd.h>

# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define MAGENTA "\033[1;35m"
# define RED "\033[22;31m"
# define YELLOW "\x1b[33m"
# define RESET "\033[0m"
# define MAPMEMCAP 200000

/*
** This is the error flag struct. Aside from flags, it holds some data about
** which line in the cub file certain errors appeared in or which paths were
** inaccessible.
*/

typedef	struct	s_error
{
	unsigned char	toomanyargs : 1;
	unsigned char	cubfilenotfound : 1;
	unsigned char	weirdfd : 1;
	unsigned char	couldnotclose : 1;
	unsigned char	mallocfail : 1;
	unsigned char	getresfail : 1;
	unsigned int	badressyn;
	unsigned int	badressize;
	unsigned char	getnofail : 1;
	unsigned int	badnosyn;
	unsigned char	getsofail : 1;
	unsigned int	badsosyn;
	unsigned char	getwefail : 1;
	unsigned int	badwesyn;
	unsigned char	geteafail : 1;
	unsigned int	badeasyn;
	unsigned char	getsprfail : 1;
	unsigned int	badsprsyn;
	unsigned char	texpathfail : 1;
	char			*texsizefail;
	unsigned char	walltexsizedif : 1;
	unsigned char	sprtexsizefail : 1;
	unsigned char	fcolorinvalid : 1;
	unsigned int	badfcolorsyn;
	unsigned char	ccolorinvalid : 1;
	unsigned int	badccolorsyn;
	unsigned char	fcoloroutofrange : 1;
	unsigned char	ccoloroutofrange : 1;
	unsigned char	nomapfound : 1;
	unsigned int	outofbounds[3];
	unsigned char	badmap3line : 1;
	unsigned char	noplayer : 1;
	unsigned int	toomanyplayers[3];
	unsigned char	getnextlinefail : 1;
	unsigned char	mapchecked : 1;
	unsigned int	premaplines;
	unsigned int	mapsweeps;
	char			*couldnotopenxpm;
	unsigned char	maptoobig : 1;
	unsigned int	memusage;
}				t_error;

/*
** This struct holds data about a sprite. It can be linked with others of its
** type in a list, although it is faster to create a pointer array to access
** all members directly. The pos variables indicate position. Spritetype holds
** the char found on the map that indicated the sprite's starting position, for
** example, '2'. By slightly modifying the map parser this can be used to store
** potentially more sprite types, and assign a unique texture for each one.
** Each sprite is associated with a texture address. For the basic cub3d it is
** always the same texture.
*/

typedef struct	s_spritedata
{
	double				posx;
	double				posy;
	char				spritetype;
	unsigned int		*texture;
	struct s_spritedata	*next;
}				t_spritedata;

/*
** This struct holds a series of parameters related to sprites that are used
** in the sprite drawing function wthin the graphics engine.
*/

typedef	struct	s_spriteparams
{
	double	transformy;
	double	transformx;
	double	invdet;
	int		vmovescreen;
	int		scrnx;
	int		scrny;
	int		texx;
	int		texy;
	int		d;
}				t_spriteparams;

/*
** This struct holds game configuration data. Most of it is gathered from the
** .cub file.
*/

typedef struct	s_configdata
{
	t_list			*maplist;
	char			**map;
	t_spritedata	*spritelist;
	unsigned int	maph;
	int				screenw;
	int				screenh;
	int				nativedisplayw;
	int				nativedisplayh;
	int				texw;
	int				texh;
	int				spritew;
	int				spriteh;
	int				spritenum;
	int				frgb[3];
	int				crgb[3];
	int				wallmultiplier;
	int				udiv;
	int				vdiv;
	int				vmove;
	double			*zbuffer;
	int				*spriteorder;
	char			*spritetexpath;
	char			screenshot;
}				t_configdata;

/*
** This struct holds data about the screen, including data provided by the
** mlx screen init function and the address of the image buffer used by the
** raycaster to draw each frame.
*/

typedef struct	s_screendata
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img_buffer;
	int		bpp;
	int		size_line;
	int		endian;
}				t_screendata;

/*
** This struct holds data about the player, such as position (pos), orientation
** (dir), or camera position (plane). Rotspeed is used by Lode's method for
** rotation, so since I use my own method for rotation I don't use that
** variable, but I'm leaving it in so it can be switched to the Lode method
** in case I ever decide to.
*/

typedef struct	s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	newdirxy[2];
	double	planex;
	double	planey;
	double	camerax;
	double	movespeed;
	double	rotspeed;
}				t_player;

/*
** This struct holds data about each ray cast by the player, such as position
** (map), orientation (raydir), distance to sides in each axis, whether a wall
** was hit, etc.
*/

typedef struct	s_raydata
{
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}				t_raydata;

/*
** This struct holds data needed to construct a frame, such as where a line
** begins and ends, where a sprite begins and ends, what color to draw each
** pixel, etc. When I stored my colors in four-byte arrays instead of in
** unsigned ints, I used the color arrays. Now I convert to hexadecimal and
** use unsigned ints, but I've left the color arrays in place in case I want
** to work with some older models I wrote that deal with each color value
** separately. In any case, they aren't used in this version.
*/

typedef struct	s_framedata
{
	int				lineheight;
	int				drawstart;
	int				drawend;
	unsigned char	color[4];
	unsigned char	ceilingcolor[4];
	unsigned char	floorcolor[4];
	unsigned int	xceilingcolor;
	unsigned int	xcolor;
	unsigned int	xfloorcolor;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
	double			spritex;
	double			spritey;
	int				spritedrawstartx;
	int				spritedrawendx;
	int				spritedrawstarty;
	int				spritedrawendy;
	int				spriteheight;
	int				spritewidth;
	int				spritescreenx;
}				t_framedata;

/*
** This holds data for each image I use with the mlx library, including
** sprites and textures.
*/

typedef struct	s_imagedata
{
	void			*mlx_img;
	int				bpp;
	int				size_line;
	int				endian;
	unsigned int	*tex_ptr;
	char			*texpath;
}				t_imagedata;

/*
** This holds all the key flags.
*/

typedef struct	s_keydata
{
	char	w : 1;
	char	a : 1;
	char	s : 1;
	char	d : 1;
	char	r : 1;
	char	l : 1;
	char	m;
}				t_keydata;

t_configdata	g_config;
t_player		g_player;
t_raydata		g_raydata;
t_screendata	g_screendata;
t_framedata		g_framedata;
t_imagedata		g_sowallimg;
t_imagedata		g_nowallimg;
t_imagedata		g_wewallimg;
t_imagedata		g_eawallimg;
t_imagedata		g_sprt2img;
t_keydata		g_keydata;

/*
** General Purpose
*/

void			del(void *freethis);
char			*getnextnum(char *num);
void			freeme(void);
int				ft_stop(int key, void *param);

/*
** Command Line Notifications
*/

void			printmap(void);
void			printmapbytes(void);
void			printsprites();
void			printerrors(void);
void			printnotifications(void);

/*
** Error Handling
*/

void			generalmaperrors(void);
void			localizedmaperrors(void);
char			toomanyplayers(unsigned int x, unsigned y, char foundplayer);
int				recorderrorlocation(unsigned int *errorarray, unsigned int x, \
unsigned int y, int returnvalue);
void			geterrorlocation(unsigned int *errorarray, unsigned int *x, \
unsigned int *y);
void			texpatherrors(void);
void			texreaderror(void);
int				texerrorconditions(void);

/*
** Linked List Functions
*/

t_spritedata	*ft_sprtlstnew(void const *content);
t_spritedata	*ft_sprtlstlast(t_spritedata *lst);
void			ft_sprtlstadd_back(t_spritedata **alst, t_spritedata *new);
void			freesprtlist(t_spritedata **alst);
t_spritedata	*spriteiter(int listmember);
void			freelist(t_list **alst);
char			maplist(unsigned int x, unsigned int y);
char			*maplistdir(unsigned int x, unsigned int y);
t_list			*maplistmem(unsigned int y);

/*
** Game Config
*/

void			initialize(void);
int				getres(const char *line, unsigned int linenum);
int				getno(const char *line, unsigned int linenum);
int				getso(const char *line, unsigned int linenum);
int				getwe(const char *line, unsigned int linenum);
int				getea(const char *line, unsigned int linenum);
int				getsprite(const char *line, unsigned int linenum);
unsigned int	create_trgb(int t, int r, int g, int b);
int				getfcolor(const char *line, unsigned int linenum);
int				getccolor(const char *line, unsigned int linenum);
void			spritecounter(double x, double y, char c);
int				ismap(char *line);
int				cubhandler(const char *ptr);
void			cubread(int *result, char **line, int fd, int linenum);
void			setdisplayresolution(void);
int				floodfill(void);
void			unfloodmap(char *flag);
int				makemaplist(int fd, char *firstline);
int				maketeximg(void);
int				maparray(void);

/*
** Raycaster
*/

int				raycaster(int key, void *param);
void			castray(int x);
void			calculateframeline(void);
void			drawframeline(int x, unsigned int *buf);
void			sortsprites(int *spriteorder);
void			castsprites(unsigned int *buf);
int				keypress(int key, void *param);
int				keyrelease(int key, void *param);
void			readmovementkeys(void);
void			graphicsmodes(void);

/*
** Screenshot
*/

int				screenshot(unsigned int *buf);
void			bmperror(int error);

/*
** Rotation
*/

double			ft_degtorad(double a);
double			ft_radtodeg(double a);
double			ft_round(double n, int prec);
int				ft_rotate_2d(double x, double y, double adeg, double *ptr);

/*
** Bonus
*/

void			countframes(time_t *timestart);
void			cls(void);

#endif
