/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/07/28 16:28:18 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <CoreGraphics/CGDisplayConfiguration.h> //need this to retrieve resolution
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

#define	GREEN "\033[0;32m"
#define MAGENTA "\033[1;35m"
#define RED "\033[22;31m"
#define YELLOW "\x1b[33m"
#define RESET "\033[0m"

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
	unsigned char	pathsprfail : 1;
	unsigned char	walltexsizefail : 1;
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
	unsigned char	toomanyplayers[3];
	unsigned char	getnextlinefail : 1;
	unsigned char	mapchecked : 1;
  unsigned int  premaplines;
	}					error_t;

typedef     struct spriteData_s
{
  double posX;
  double posY;
  char   spriteType;
  unsigned int *texture;
  struct spriteData_s *next;
}                   spriteData_t;

typedef     struct  configData_s
{
  t_list *Map;
  spriteData_t *spriteList;
  int mapW;
  int mapH;
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
    double  *newDirXY;
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
  clock_t       time;
  clock_t       oldTime;
  clock_t       frameTime;
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
void			freeSprtList(spriteData_t **alst);
spriteData_t	*spriteIter(int listMember);
void			freeList(t_list **alst);
char			mapList(int x, int y);
char			*mapListDir(int x, int y);
t_list			*mapListMem(int y);
void			cls();
void			ft_sortSprites(int *spriteOrder);
int				ft_stop(int key, void *param);
int				ft_rayCaster(int key, void *param);
int				ft_keyPress(int key, void *param);
int				ft_keyRelease(int key, void *param);
void			initialize(void);
void			initializeKeys(void);
int				getres(const char *line, unsigned int linenum);
int				getno(const char *line, unsigned int linenum);
int				getso(const char *line, unsigned int linenum);
int				getwe(const char *line, unsigned int linenum);
int				getea(const char *line, unsigned int linenum);
int				getsprite(const char *line, unsigned int linenum);
int				getTexRes(int *texRes, char *xmpPath);
int				compTexRes(void);
unsigned int	create_trgb(int t, int r, int g, int b);
int				getfcolor(const char *line, unsigned int linenum);
int				getccolor(const char *line, unsigned int linenum);
void			spriteCounter(double x, double y, char c);
int				isMap(char *line);
int				cubhandler(const char *ptr);
void			cubread(int *result, char **line, int fd);
void			setdisplayresolution(void);
void			printerrors(void);
void			printnotifications(void);
int				floodFill(void);
int				floodRight(int x, int y);
int				floodLeft(int x, int y);
void			unfloodMap(void);
int				makeMapList(int fd, char *firstLine);
void			makeClsImg(void);
void			makeTexImg(void);
int				main(int argc, char **argv);













double  ft_degtorad(double a);
double  ft_radtodeg(double a);
double  ft_round(double n, int prec);
int     ft_rotate_2D(double x, double y, double adeg, double prec, double **ptr);
int     getRes(const char *line);
void    cls(void);

#endif