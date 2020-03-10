/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:25:06 by mrosario          #+#    #+#             */
/*   Updated: 2020/03/10 20:19:48 by mrosario         ###   ########.fr       */
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

#define mapWidth        24
#define mapHeight       24
#define screenWidth     2560 //640
#define screenHeight    1440 //480
#define screenXCenter   320
#define screenYCenter   240
#define texWidth        64
#define texHeight       64
#define numSprites      2
/*#define normiTexWidth   128
#define normiTexHeight  164
#define wallMultiplier  1 //modifies apparent wall height
#define uDiv            1
#define vDiv            1 //raise to 
#define vMove           (double)normiTexHeight //raise to lower sprite*/

/*
** posX and posY determine position. dirX and dirY determine direction.
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

typedef     struct  configData_s
{
  t_list *Map;
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

//Habrá que localizar este struct en Raycaster para dinamizar screenHeight/screenWidth
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
  unsigned int  buffer[screenHeight][screenWidth]; //y coordinate first because it works per scanline
  double        zBuffer[screenWidth]; //1D ZBuffer
  int           spriteOrder[numSprites];
  double        spriteDistance[numSprites];
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

typedef     struct spriteData_s
{
  double x;
  double y;
  unsigned int *texture;
}                   spriteData_t;

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
spriteData_t  g_sprite[numSprites] = {
  {10.5, 14.5, 0},
  {6.5, 12.5, 0},
};

double  ft_degtorad(double a);
double  ft_radtodeg(double a);
double  ft_round(double n, int prec);
int     ft_rotate_2D(double x, double y, double adeg, double prec, double **ptr);
int     getRes(const char *line);
void    cls(void);

#endif