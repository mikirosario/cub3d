/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dLode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:15:30 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cub3d.h"
  #include <time.h>

  //pixel_put cls
  /*void cls()
{
    int x;
    int y;

    x = 0;
        while (x <= screenWidth) //clearscreen
        {
            y = screenHeight;
            while (y)
            {
                mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, y--, 0x0);
            }
            x++;
        }
}*/

//image dump cls
void    cls(void)
{
    mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_clsimg.mlx_img, 0, 0);
}

int   ft_rayCaster(int key, void *param)
{
    (void)param;
    (void)key;
    int x;
    int w;
    int i;
    int ibuf;
    char *buf;

    x = 0;
    w = 0;
    buf = mlx_get_data_addr(g_screendata.mlx_img_buffer, &g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian);
    cls();
    while (x < screenWidth)
    {
        //calculate ray position and direction
        g_player.camerax = 2 * x / (double)screenWidth - 1;
        g_raydata.raydirx = g_player.dirx + g_player.planex * g_player.camerax;
        g_raydata.raydiry = g_player.diry + g_player.planey * g_player.camerax;
        //which box of the map we're in
        g_raydata.mapx = (int)g_player.posx;
        g_raydata.mapy = (int)g_player.posy;
        //length of ray from one x or y-side to the next x or y-side
        if (g_raydata.raydiry == 0)
            g_raydata.deltadistx = 0;
        else if (g_raydata.raydirx == 0)
            g_raydata.deltadistx = 1;
        else
            g_raydata.deltadistx = fabs(1 / g_raydata.raydirx);
        if (g_raydata.raydirx == 0)
            g_raydata.deltadisty = 0;
        else if (g_raydata.raydiry == 0)
            g_raydata.deltadisty = 1;
        else
            g_raydata.deltadisty = fabs(1 / g_raydata.raydiry);
        //wall hit?
        g_raydata.hit = 0;
        //calculate step and initial sideDist
        if (g_raydata.raydirx < 0)
        {
            g_raydata.stepx = -1;
            g_raydata.sidedistx = (g_player.posx - g_raydata.mapx) * g_raydata.deltadistx;
        }
        else
        {
            g_raydata.stepx = 1;
            g_raydata.sidedistx = (g_raydata.mapx + 1.0 - g_player.posx) * g_raydata.deltadistx;
        }
        if (g_raydata.raydiry < 0)
        {
            g_raydata.stepy = -1;
            g_raydata.sidedisty = (g_player.posy - g_raydata.mapy) * g_raydata.deltadisty;
        }
        else
        {
            g_raydata.stepy = 1;
            g_raydata.sidedisty = (g_raydata.mapy + 1.0 - g_player.posy) * g_raydata.deltadisty;
        }
        //perform DDA
        while (g_raydata.hit == 0)
        {
            //jump to next map square in x-direction OR in y-direction
            if (g_raydata.sidedistx < g_raydata.sidedisty)
            {
                g_raydata.sidedistx += g_raydata.deltadistx;
                g_raydata.mapx += g_raydata.stepx;
                g_raydata.side = 0;
            }
            else
            {
                g_raydata.sidedisty += g_raydata.deltadisty;
                g_raydata.mapy += g_raydata.stepy;
                g_raydata.side = 1;
            }
            //check of ray has hit a wall
            if (g_worldMap[g_raydata.mapx][g_raydata.mapy] > 0)
                g_raydata.hit = 1;
        }
        //calculate distance projected on camera direction
        if (g_raydata.side == 0)
            g_raydata.perpwalldist = (g_raydata.mapx - g_player.posx + (1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
        else
            g_raydata.perpwalldist = (g_raydata.mapy - g_player.posy + (1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
        //calculate height of line to draw on screen
        g_framedata.lineheight = (int)(screenHeight / g_raydata.perpwalldist);
        //calculate lowest and highest pixel to fill in current stripe
        g_framedata.drawstart = -(g_framedata.lineheight) / 2 + screenHeight / 2;
        if (g_framedata.drawstart < 0)
            g_framedata.drawstart = 0;
        g_framedata.drawend = g_framedata.lineheight / 2 + screenHeight / 2;
        if  (g_framedata.drawend >= screenHeight)
            g_framedata.drawend = screenHeight - 1;
        //choose wall colour
        i = 0;
        g_framedata.xcolor = 0x0;
        if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 1)
            g_framedata.xcolor = 0x00ff0000; //red
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 2)
            g_framedata.xcolor = 0x0000ff00; //green
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 3)
            g_framedata.xcolor = 0x000000ff; //blue
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 4)
            g_framedata.xcolor = 0x00ffffff; //white
        else
            g_framedata.xcolor = 0x00ffff00; //yellow
        //give x and y sides different brightnesses
        if (g_raydata.side == 1)
        {
            if (g_framedata.xcolor)
                g_framedata.xcolor = (g_framedata.xcolor & 0xfefefe) >> 1;
        }
        //draw pixels of stripe as vertical line
        ibuf = g_framedata.drawstart;
        while (ibuf < g_framedata.drawend)
            mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, ibuf++, g_framedata.xcolor);
        x++;
        w += 4;
    }
    return (0);
}
    
  int   ft_stop(int key, void *param)
  {
    (void)param;
    if (key == 0x35 || key == 0x00)
    {
        mlx_destroy_window(g_screendata.mlx_ptr, g_screendata.mlx_win);
        mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
        mlx_destroy_image(g_screendata.mlx_ptr, g_clsimg.mlx_img);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

  int   ft_playerMovement(int key, void *param)
{
    (void)param;
    g_player.movespeed = 1;
    g_player.rotspeed = 0.1;
    double *newDirXY;

    if (key == 0x35)
        ft_stop(key, (void *)0);
    newDirXY = malloc(2 * sizeof(double));
    //move forwards if no wall in front
    if (key == 0xD)
    {
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    if (g_worldMap[(int)(g_player.posx + g_player.dirx * g_player.movespeed)][(int)g_player.posy] == 0)
        g_player.posx += g_player.dirx * g_player.movespeed;
    if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.diry * g_player.movespeed)] == 0)
        g_player.posy += g_player.diry * g_player.movespeed;
    }
      //move backwards if no wall in front
    if (key == 0x1)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        if (g_worldMap[(int)(g_player.posx - g_player.dirx * g_player.movespeed)][(int)(g_player.posy)] == 0)
            g_player.posx -= g_player.dirx * g_player.movespeed;
        if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.diry * g_player.movespeed)] == 0)
            g_player.posy -= g_player.diry * g_player.movespeed;
    }
        //clockwise rotation
    if (key == 0x7C)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
        //mi método
        /*ft_rotate_2D(g_player.dirx, g_player.diry, -5, 6, &newDirXY);
        g_player.dirx = newDirXY[0];
        g_player.diry = newDirXY[1];
        ft_rotate_2D(g_player.planex, g_player.planey, -5, 6, &newDirXY);
        g_player.planex = newDirXY[0];
        g_player.planey = newDirXY[1];*/
    
        //método Lode
        g_player.oldDirX = g_player.dirx;
        g_player.dirx = g_player.dirx * cos(-g_player.rotspeed) - g_player.diry * sin(-g_player.rotspeed);
        g_player.diry = g_player.oldDirX * sin(-g_player.rotspeed) + g_player.diry * cos(-g_player.rotspeed);
        g_player.oldPlaneX = g_player.planex;
        g_player.planex = g_player.planex * cos(-g_player.rotspeed) - g_player.planey * sin(-g_player.rotspeed);
        g_player.planey = g_player.oldPlaneX * sin(-g_player.rotspeed) + g_player.planey * cos(-g_player.rotspeed);
    }
    //anticlockwise rotation
    if (key == 0x7B)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
        //mi método
        /*ft_rotate_2D(g_player.dirx, g_player.diry, 5, 6, &newDirXY);
        g_player.dirx = newDirXY[0];
        g_player.diry = newDirXY[1];
        ft_rotate_2D(g_player.planex, g_player.planey, 5, 6, &newDirXY);
        g_player.planex = newDirXY[0];
        g_player.planey = newDirXY[1];*/
    
        //método Lode
        g_player.oldDirX = g_player.dirx;
        g_player.dirx = g_player.dirx * cos(g_player.rotspeed) - g_player.diry * sin(g_player.rotspeed);
        g_player.diry = g_player.oldDirX * sin(g_player.rotspeed) + g_player.diry * cos(g_player.rotspeed);
        g_player.oldPlaneX = g_player.planex;
        g_player.planex = g_player.planex * cos(g_player.rotspeed) - g_player.planey * sin(g_player.rotspeed);
        g_player.planey = g_player.oldPlaneX * sin(g_player.rotspeed) + g_player.planey * cos(g_player.rotspeed);
    }
    free(newDirXY);
      return (0);
}

int   main(void/*int argc, char **argv*/)
  {
      g_player.posx = 22;
      g_player.posy = 12;
      g_player.dirx = -1;
      g_player.diry = 0;
      g_player.planex = 0;
      g_player.planey = 0.66;
      g_framedata.time = 0;
      g_framedata.oldTime = 0;

//Create screen
    if ((g_screendata.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, screenWidth, screenHeight);
    g_clsimg.mlx_img = mlx_new_image(g_screendata.mlx_ptr, screenWidth, screenHeight);
    mlx_hook(g_screendata.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screendata.mlx_win, 2, 0, ft_playerMovement, (void*)0);
    mlx_loop_hook(g_screendata.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screendata.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  