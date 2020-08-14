/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/14 20:07:21 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <CoreGraphics/CGDisplayConfiguration.h> //need this to retrieve resolution
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <string.h>
#include "./libft/libft.h"
#include "iamerror.h"
#include "printnotifications.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h> //BONUS

#define	BLUE "\033[1;34m"
#define	GREEN "\033[0;32m"
#define MAGENTA "\033[1;35m"
#define RED "\033[22;31m"
#define YELLOW "\x1b[33m"
#define RESET "\033[0m"
#define MAPMEMCAP 1440000

/*
** posX and posY determine position. dirX and dirY determine direction.
** planeX and planeY determine camera plane. Ratio between direction
** length and camera plane determines FOV. Direction musst always be
** perpendicullar to camera plane. Time stores current frame time;
** oldTime stores last frame time.
*/
typedef		struct error_s
{
	unsigned char	cubfilenotfound : 1;
	unsigned char	weirdfd : 1;
	unsigned char	couldnotclose : 1;
	unsigned char	mallocfail : 1;
	unsigned char	getresfail : 1;
	unsigned int	badresSyn;
	unsigned int	badresSize;
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
	unsigned char	nomapfound : 1;
	unsigned int	outofbounds[3];
	unsigned char	badmap3line : 1;
	unsigned char	noplayer : 1;
	unsigned int	toomanyplayers[3];
	unsigned char	getnextlinefail : 1;
	unsigned char	mapchecked : 1;
  	unsigned int 	premaplines;
	unsigned int	mapsweeps;
	char			*couldnotopenxpm;
	unsigned char	maptoobig : 1;
	unsigned int	memusage;
}				error_t;

typedef     struct spriteData_s
{
  double posX;
  double posY;
  char   spriteType;
  unsigned int *texture;
  struct spriteData_s *next;
}                   spriteData_t;

typedef	struct	spriteparams_s
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
}				spriteparams_t;

typedef     struct  configData_s
{
  t_list *Map;
  spriteData_t *spriteList;
  unsigned int mapW;
  unsigned int mapH;
  int screenW;
  int screenH;
  int texW;
  int texH;
  int spriteW;
  int spriteH;
  int spriteNum;
  int frgb[3];
  int crgb[3];
  int wallMultiplier; //modifies apparent wall height
  int uDiv; //no recuerdo qué hacía
  int vDiv; //no recuerdo qué hacía
  int vMove; //raise to lower sprite
  double *zbuffer;
  int *spriteorder;
  char *spriteTexPath;
}           configData_t;

typedef     struct  screenData_s
{
  void      *mlx_ptr;
  void      *mlx_win;
  void      *mlx_img_buffer;
  int       bpp;
  int       size_line;
  int       endian;
}           screenData_t;

typedef     struct  player_s
{
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  oldDirX;
    double  oldDirY;
    double  newDirXY[2];
    double  planeX;
    double  planeY;
    double  oldPlaneX;
    double  cameraX;
    double  moveSpeed;
    double  rotSpeed;
}                   player_t;

typedef     struct  world_s
{
    int     x;
    int     y;
    int     stepX;
    int     stepY;
}                   world_t;

typedef     struct  rayData_s
{
  double    rayDirX;
  double    rayDirY;
  int       mapX;
  int       mapY;
  double    sideDistX;
  double    sideDistY;
  double    deltaDistX;
  double    deltaDistY;
  double    perpWallDist;
  int       stepX;
  int       stepY;
  int       hit;
  int       side; //NS or EW wall hit?

}                   rayData_t;

typedef     struct frameData_s
{
  //clock_t       time;
  //clock_t       oldTime;
  //clock_t       frameTime;
  int           lineHeight;
  int           drawStart;
  int           drawEnd;
  unsigned char           color[4];
  unsigned char           ceilingColor[4];
  unsigned char           floorColor[4];
  unsigned int           oceilingColor;
  unsigned int           ocolor;
  int           ofloorColor;
  double        wallX; //where exactly wall was hit
  int           texX; //texture X coordinate;
  int           texY; //texture Y coordinate;
  double        step;
  double        texPos;
  double		spriteX;
  double		spriteY;
  double		transformX;
  double		transformY;
  int			spriteDrawStartX;
  int			spriteDrawEndX;
  int			spriteDrawStartY;
  int			spriteDrawEndY;
  int			spriteHeight;
  int			spriteWidth;
  int			spriteScreenX;
}                  frameData_t;

typedef     struct imageData_s
{
  void          *mlx_img;
  int           bpp;
  int           size_line;
  int           endian;
  unsigned int  *tex_Ptr;
  char          *texPath;
}                  imageData_t;

typedef     struct keyData_s
{
  char  w;
  char  a;
  char  s;
  char  d;
  char  r;
  char  l;
  char  m;
}                   keyData_t;

configData_t g_config;
player_t g_player;
world_t g_world;
rayData_t g_rayData;
screenData_t g_screenData;
frameData_t  g_frameData;
imageData_t g_blueMetalImg;
imageData_t g_yellowMetalImg;
imageData_t g_greenMetalImg;
imageData_t g_pinkMetalImg;
imageData_t g_clsImg;
imageData_t g_ceilingImg;
imageData_t g_floorImg;
imageData_t g_normiImg;
keyData_t g_keyData;

void			del(void *freeThis);
spriteData_t	*ft_sprtlstnew(void const *content);
spriteData_t	*ft_sprtlstlast(spriteData_t *lst);
void			ft_sprtlstadd_back(spriteData_t **alst, spriteData_t *new);
void			freesprtlist(spriteData_t **alst);
spriteData_t	*spriteiter(int listmember);
void			freelist(t_list **alst);
char			maplist(unsigned int x, unsigned int y);
char			*maplistdir(unsigned int x, unsigned int y);
t_list			*maplistmem(unsigned int y);
void			cls();
void			ft_sortSprites(int *spriteOrder);
int				ft_stop(int key, void *param);
int				ft_rayCaster(int key, void *param);
int				ft_raycaster(int key, void *param);
int				ft_keyPress(int key, void *param);
int				ft_keyRelease(int key, void *param);
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
void			printmap(void);
void			printmapbytes(void);
void			printsprites();
void			printerrors(void);
void			printnotifications(void);
char			toomanyplayers(unsigned int x, unsigned y, char foundplayer);
int				recorderrorlocation(unsigned int *errorarray, unsigned int x, unsigned int y, int returnvalue);
void			geterrorlocation(unsigned int *errorarray, unsigned int *x, unsigned int *y);
void			localizedmaperrors(void);
void			generalmaperrors(void);
void			texpatherrors(void);
void			texreaderror(void);
int				texerrorconditions(void);
int				floodfill(void);
void			unfloodmap(char *flag);
int				makemaplist(int fd, char *firstline);
void			makeClsImg(void);
int				maketeximg(void);
void			freeme(void);
int				main(int argc, char **argv);





//Raycaster

void	castray(int x);
void	calculateframeline(void);
void	drawframeline(int x, unsigned int *buf);
void	castsprites(unsigned int *buf);
void	readmovementkeys(void);







double  ft_degtorad(double a);
double  ft_radtodeg(double a);
double  ft_round(double n, int prec);
int     ft_rotate_2d(double x, double y, double adeg, double prec, double *ptr);
int     getRes(const char *line);
void    cls(void);
char	*getnextnum(char *num);

#endif