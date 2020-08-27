/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:24:11 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//#include <CoreGraphics/CGDisplayConfiguration.h> BONUS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <string.h>
#include "libft.h"
#include "iamerror.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h> //BONUS

#define MAGENTA "[1;35m"
#define RED "\033[22;31m"
#define YELLOW "\x1b[33m"
#define RESET "\033[0m"

//#define mapWidth        24
//#define mapHeight       24
/*#define screenWidth     2560 //640
#define screenHeight    1440 //480
#define screenXCenter   320
#define screenYCenter   240
#define texWidth        64
#define texHeight       64
#define numSprites      2*/
/*#define normiTexWidth   128
#define normiTexHeight  164
#define wallMultiplier  1 //modifies apparent wall height
#define uDiv            1
#define vDiv            1 //raise to 
#define vMove           (double)normiTexHeight //raise to lower sprite*/

/*
** posx and posy determine position. dirX and dirY determine direction.
** planeX and planeY determine camera plane. Ratio between direction
** length and camera plane determines FOV. Direction musst always be
** perpendicullar to camera plane. Time stores current frame time;
** oldTime stores last frame time.
*/

/*int g_worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

typedef     struct spriteData_s
{
  double posx;
  double posy;
  char   spritetype;
  unsigned int *texture;
  struct spriteData_s *next;
}                   t_spritedata;

typedef     struct  configData_s
{
  t_list *Map;
  t_spritedata *spritelist;
  int mapW;
  int mapH;
  int screenW;
  int screenH;
  int texW;
  int texH;
  int spriteW;
  int spriteH;
  int spriteNum;
  int wallMultiplier;
  int uDiv;
  int vDiv;
  int vMove;
  char *spriteTexPath;
  //int wallMultiplier;
  //int uDiv;
  //int vDiv;
  //int vMove;
}           t_configdata;

typedef     struct  screenData_s
{
  void      *mlx_ptr;
  void      *mlx_win;
  void      *mlx_img_buffer;
  int       bpp;
  int       size_line;
  int       endian;
}           t_screendata;

typedef		struct bmpdata_s
{
	char			filetype[2];
	unsigned int	filesize;
	unsigned int	reserved[2];
	unsigned int	pixeloffset;
	unsigned int	headersize;
	int				imagewidth;
	int				imageheight;
	unsigned int	planes : 16;
	unsigned int	bpp : 16;
	unsigned int	compression;
	unsigned int	imagesize;
	int				xpixelspermeter;
	int				ypixelspermeter;
	unsigned int	totalcolors;
	unsigned int	importantcolors;
}			bmpdata_t;


typedef     struct  player_s
{
    double  posx;
    double  posy;
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
}                   t_player;

typedef     struct  world_s
{
    int     x;
    int     y;
    int     stepX;
    int     stepY;
}                   t_world;

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

}                   t_raydata;

//Habrá que localizar arrays en Raycaster para dinamizar screenHeight/screenWidth
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
  //unsigned int  buffer[screenHeight][screenWidth]; //y coordinate first because it works per scanline
  //double        zBuffer[screenWidth]; //1D ZBuffer
  //int           spriteOrder[numSprites]; //traspasado a RayCaster
}                  t_framedata;

typedef     struct imageData_s
{
  void          *mlx_img;
  int           bpp;
  int           size_line;
  int           endian;
  unsigned int  *tex_Ptr;
  char          *texPath;
}                  t_imagedata;

typedef     struct keyData_s
{
  char  w;
  char  a;
  char  s;
  char  d;
  char  r;
  char  l;
  char  m;
}                   t_keydata;

t_configdata g_config;
t_player g_player;
t_world g_world;
t_raydata g_raydata;
t_screendata g_screendata;
t_framedata  g_framedata;
t_imagedata g_blueMetalImg;
t_imagedata g_yellowMetalImg;
t_imagedata g_greenMetalImg;
t_imagedata g_pinkMetalImg;
t_imagedata g_clsimg;
t_imagedata g_ceilingimg;
t_imagedata g_floorimg;
t_imagedata g_sprt2img;
t_keydata g_keydata;
/*t_spritedata  g_sprite[numSprites] = {
  {10.5, 14.5, 0},
  {6.5, 12.5, 0},
};*/

double  ft_degtorad(double a);
double  ft_radtodeg(double a);
double  ft_round(double n, int prec);
int     ft_rotate_2D(double x, double y, double adeg, double prec, double **ptr);
int     getres(const char *line);
void    cls(void);

#endif