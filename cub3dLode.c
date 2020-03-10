/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dLode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/02/21 16:02:25 by mrosario         ###   ########.fr       */
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
                mlx_pixel_put(g_screenData.mlx_ptr, g_screenData.mlx_win, x, y--, 0x0);
            }
            x++;
        }
}*/

//image dump cls
void    cls(void)
{
    mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_clsImg.mlx_img, 0, 0);
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
    buf = mlx_get_data_addr(g_screenData.mlx_img_buffer, &g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
    cls();
    while (x < screenWidth)
    {
        //calculate ray position and direction
        g_player.cameraX = 2 * x / (double)screenWidth - 1;
        g_rayData.rayDirX = g_player.dirX + g_player.planeX * g_player.cameraX;
        g_rayData.rayDirY = g_player.dirY + g_player.planeY * g_player.cameraX;
        //which box of the map we're in
        g_rayData.mapX = (int)g_player.posX;
        g_rayData.mapY = (int)g_player.posY;
        //length of ray from one x or y-side to the next x or y-side
        if (g_rayData.rayDirY == 0)
            g_rayData.deltaDistX = 0;
        else if (g_rayData.rayDirX == 0)
            g_rayData.deltaDistX = 1;
        else
            g_rayData.deltaDistX = fabs(1 / g_rayData.rayDirX);
        if (g_rayData.rayDirX == 0)
            g_rayData.deltaDistY = 0;
        else if (g_rayData.rayDirY == 0)
            g_rayData.deltaDistY = 1;
        else
            g_rayData.deltaDistY = fabs(1 / g_rayData.rayDirY);
        //wall hit?
        g_rayData.hit = 0;
        //calculate step and initial sideDist
        if (g_rayData.rayDirX < 0)
        {
            g_rayData.stepX = -1;
            g_rayData.sideDistX = (g_player.posX - g_rayData.mapX) * g_rayData.deltaDistX;
        }
        else
        {
            g_rayData.stepX = 1;
            g_rayData.sideDistX = (g_rayData.mapX + 1.0 - g_player.posX) * g_rayData.deltaDistX;
        }
        if (g_rayData.rayDirY < 0)
        {
            g_rayData.stepY = -1;
            g_rayData.sideDistY = (g_player.posY - g_rayData.mapY) * g_rayData.deltaDistY;
        }
        else
        {
            g_rayData.stepY = 1;
            g_rayData.sideDistY = (g_rayData.mapY + 1.0 - g_player.posY) * g_rayData.deltaDistY;
        }
        //perform DDA
        while (g_rayData.hit == 0)
        {
            //jump to next map square in x-direction OR in y-direction
            if (g_rayData.sideDistX < g_rayData.sideDistY)
            {
                g_rayData.sideDistX += g_rayData.deltaDistX;
                g_rayData.mapX += g_rayData.stepX;
                g_rayData.side = 0;
            }
            else
            {
                g_rayData.sideDistY += g_rayData.deltaDistY;
                g_rayData.mapY += g_rayData.stepY;
                g_rayData.side = 1;
            }
            //check of ray has hit a wall
            if (g_worldMap[g_rayData.mapX][g_rayData.mapY] > 0)
                g_rayData.hit = 1;
        }
        //calculate distance projected on camera direction
        if (g_rayData.side == 0)
            g_rayData.perpWallDist = (g_rayData.mapX - g_player.posX + (1 - g_rayData.stepX) / 2) / g_rayData.rayDirX;
        else
            g_rayData.perpWallDist = (g_rayData.mapY - g_player.posY + (1 - g_rayData.stepY) / 2) / g_rayData.rayDirY;
        //calculate height of line to draw on screen
        g_frameData.lineHeight = (int)(screenHeight / g_rayData.perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        g_frameData.drawStart = -(g_frameData.lineHeight) / 2 + screenHeight / 2;
        if (g_frameData.drawStart < 0)
            g_frameData.drawStart = 0;
        g_frameData.drawEnd = g_frameData.lineHeight / 2 + screenHeight / 2;
        if  (g_frameData.drawEnd >= screenHeight)
            g_frameData.drawEnd = screenHeight - 1;
        //choose wall colour
        i = 0;
        g_frameData.ocolor = 0x0;
        if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 1)
            g_frameData.ocolor = 0x00ff0000; //red
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 2)
            g_frameData.ocolor = 0x0000ff00; //green
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 3)
            g_frameData.ocolor = 0x000000ff; //blue
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 4)
            g_frameData.ocolor = 0x00ffffff; //white
        else
            g_frameData.ocolor = 0x00ffff00; //yellow
        //give x and y sides different brightnesses
        if (g_rayData.side == 1)
        {
            if (g_frameData.ocolor)
                g_frameData.ocolor = (g_frameData.ocolor & 0xfefefe) >> 1;
        }
        //draw pixels of stripe as vertical line
        ibuf = g_frameData.drawStart;
        while (ibuf < g_frameData.drawEnd)
            mlx_pixel_put(g_screenData.mlx_ptr, g_screenData.mlx_win, x, ibuf++, g_frameData.ocolor);
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
        mlx_destroy_window(g_screenData.mlx_ptr, g_screenData.mlx_win);
        mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
        mlx_destroy_image(g_screenData.mlx_ptr, g_clsImg.mlx_img);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

  int   ft_playerMovement(int key, void *param)
{
    (void)param;
    g_player.moveSpeed = 1;
    g_player.rotSpeed = 0.1;
    double *newDirXY;

    if (key == 0x35)
        ft_stop(key, (void *)0);
    newDirXY = malloc(2 * sizeof(double));
    //move forwards if no wall in front
    if (key == 0xD)
    {
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    if (g_worldMap[(int)(g_player.posX + g_player.dirX * g_player.moveSpeed)][(int)g_player.posY] == 0)
        g_player.posX += g_player.dirX * g_player.moveSpeed;
    if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.dirY * g_player.moveSpeed)] == 0)
        g_player.posY += g_player.dirY * g_player.moveSpeed;
    }
      //move backwards if no wall in front
    if (key == 0x1)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        if (g_worldMap[(int)(g_player.posX - g_player.dirX * g_player.moveSpeed)][(int)(g_player.posY)] == 0)
            g_player.posX -= g_player.dirX * g_player.moveSpeed;
        if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.dirY * g_player.moveSpeed)] == 0)
            g_player.posY -= g_player.dirY * g_player.moveSpeed;
    }
        //clockwise rotation
    if (key == 0x7C)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
        //mi método
        /*ft_rotate_2D(g_player.dirX, g_player.dirY, -5, 6, &newDirXY);
        g_player.dirX = newDirXY[0];
        g_player.dirY = newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, -5, 6, &newDirXY);
        g_player.planeX = newDirXY[0];
        g_player.planeY = newDirXY[1];*/
    
        //método Lode
        g_player.oldDirX = g_player.dirX;
        g_player.dirX = g_player.dirX * cos(-g_player.rotSpeed) - g_player.dirY * sin(-g_player.rotSpeed);
        g_player.dirY = g_player.oldDirX * sin(-g_player.rotSpeed) + g_player.dirY * cos(-g_player.rotSpeed);
        g_player.oldPlaneX = g_player.planeX;
        g_player.planeX = g_player.planeX * cos(-g_player.rotSpeed) - g_player.planeY * sin(-g_player.rotSpeed);
        g_player.planeY = g_player.oldPlaneX * sin(-g_player.rotSpeed) + g_player.planeY * cos(-g_player.rotSpeed);
    }
    //anticlockwise rotation
    if (key == 0x7B)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
        //mi método
        /*ft_rotate_2D(g_player.dirX, g_player.dirY, 5, 6, &newDirXY);
        g_player.dirX = newDirXY[0];
        g_player.dirY = newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, 5, 6, &newDirXY);
        g_player.planeX = newDirXY[0];
        g_player.planeY = newDirXY[1];*/
    
        //método Lode
        g_player.oldDirX = g_player.dirX;
        g_player.dirX = g_player.dirX * cos(g_player.rotSpeed) - g_player.dirY * sin(g_player.rotSpeed);
        g_player.dirY = g_player.oldDirX * sin(g_player.rotSpeed) + g_player.dirY * cos(g_player.rotSpeed);
        g_player.oldPlaneX = g_player.planeX;
        g_player.planeX = g_player.planeX * cos(g_player.rotSpeed) - g_player.planeY * sin(g_player.rotSpeed);
        g_player.planeY = g_player.oldPlaneX * sin(g_player.rotSpeed) + g_player.planeY * cos(g_player.rotSpeed);
    }
    free(newDirXY);
      return (0);
}

int   main(void/*int argc, char **argv*/)
  {
      g_player.posX = 22;
      g_player.posY = 12;
      g_player.dirX = -1;
      g_player.dirY = 0;
      g_player.planeX = 0;
      g_player.planeY = 0.66;
      g_frameData.time = 0;
      g_frameData.oldTime = 0;

//Create screen
    if ((g_screenData.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screenData.mlx_win = mlx_new_window(g_screenData.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, screenWidth, screenHeight);
    g_clsImg.mlx_img = mlx_new_image(g_screenData.mlx_ptr, screenWidth, screenHeight);
    mlx_hook(g_screenData.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screenData.mlx_win, 2, 0, ft_playerMovement, (void*)0);
    mlx_loop_hook(g_screenData.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screenData.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  