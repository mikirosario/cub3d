/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dLodeTex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/02/24 05:14:43 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cub3d.h"
  #include <time.h>

  //pixel_put cls
/*  void cls()
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
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
}*/

//image dump cls
void    cls()
{
    mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_clsImg.mlx_img, 0, 0);
    /*mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 300, 0x0000ff00, ft_itoa(printFPS));       */
}

int   ft_rayCaster(int key, void *param)
{
    (void)param;
    (void)key;
    int x;
    int w;
    int i;
    int ibuf;
    static time_t seconds = 0;
    time_t endTime;
    static int fps = 0;
    static int printFPS = 0;
    unsigned char *buf;
    unsigned char *brickTex;
    g_player.moveSpeed = 0.25;
    g_player.rotSpeed = 0.1;

    if (!seconds)
        seconds = time(NULL);
    x = 0;
    w = 0;
    g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, screenWidth, screenHeight);
    buf = (unsigned char *)mlx_get_data_addr(g_screenData.mlx_img_buffer, &g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
    brickTex = (unsigned char *)mlx_get_data_addr(g_brickImg.mlx_img, &g_brickImg.bpp, &g_screenData.size_line, &g_screenData.endian);
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
        //calculate height of line to draw on screen; multiplier controls wall height
        g_frameData.lineHeight = (int)(screenHeight * 2 / g_rayData.perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        g_frameData.drawStart = -(g_frameData.lineHeight) / 2 + screenHeight / 2;
        if (g_frameData.drawStart < 0)
            g_frameData.drawStart = 0;
        g_frameData.drawEnd = g_frameData.lineHeight / 2 + screenHeight / 2;
        if  (g_frameData.drawEnd >= screenHeight)
            g_frameData.drawEnd = screenHeight - 1;
        //choose wall colour
        /*i = 0;
        //first reset color to black
        while (i < 4)
            g_frameData.color[i++] = 0;
        i = 0;
        if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 1)
            g_frameData.color[2] = 255; //red
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 2)
            g_frameData.color[1] = 255; //green
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 3)
            g_frameData.color[0] = 255; //blue
        else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 4)
        {
            i = 0;
            while (i < 3)
                g_frameData.color[i++] = 255; //white
        }
        else
        {
            i = 0;
            while (i < 2)
            g_frameData.color[i++] = 255; //yellow
        }
        //give x and y sides different brightnesses
        if (g_rayData.side == 1)
        {
            i = 0;
            while (i < 3)
            {
                if (g_frameData.color[i])
                {
                    g_frameData.color[i] = g_frameData.color[i] >> 1;
                }
                i++;
            }
        }*/
        //draw pixels of stripe as vertical line
        ibuf = w;
        //printf("%d%d%d%d, ", g_frameData.color[0], g_frameData.color[1], g_frameData.color[2], g_frameData.color[3]);
        while (ibuf < (w + 4 * screenWidth * g_frameData.drawStart)) //paint ceiling
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_frameData.ceilingColor[i];
                i++;   
            }
            ibuf += screenWidth * 4;
        }
        
        //choose texture
        //calculate value of wallX (x coordinate where wall was hit)
        if (g_rayData.side == 0)
            g_frameData.wallX = g_player.posY + g_rayData.perpWallDist * g_rayData.rayDirY;
        else
            g_frameData.wallX = g_player.posX + g_rayData.perpWallDist * g_rayData.rayDirX;
        g_frameData.wallX -= floor((g_frameData.wallX));
        
        //calculate x coordinate on the texture
        g_frameData.texX = (int)(g_frameData.wallX * (double)64.0/*texWidth*/);
        if (g_rayData.side == 0 && g_rayData.rayDirX > 0)
            g_frameData.texX = (64/*texWidth*/) - (g_frameData.texX) - 1;
        if (g_rayData.side == 1 && g_rayData.rayDirY < 0)
            g_frameData.texX = (64/*texWidth*/) - (g_frameData.texX) - 1;
        
        //how much to increase texture coordinate per screen pixel
        g_frameData.step = 1.0 * 64/*texHeight*/ / g_frameData.lineHeight;
        //starting texture coordinate
        g_frameData.texPos = (g_frameData.drawStart - screenHeight / 2 + g_frameData.lineHeight / 2) * g_frameData.step;
        
        while (ibuf < (w + 4 * screenWidth * g_frameData.drawEnd)) // paint texture wall
        {
             //cast texture coordinate with integer and mask with texHeight - 1 in case of overflow
             g_frameData.texY = (int)(g_frameData.texPos) & (64 - 1/*texHeight*/);
           
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = brickTex[(g_frameData.texX * 4) + 4 * 64 * g_frameData.texY + i];
                i++;
            }
               /*if (fps == 60)
                {
                //printf("(TexX: %d, TexY %d) ", g_frameData.texX, g_frameData.texY);
                }*/
            /*i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_frameData.color[i];
                i++;
            }*/
            g_frameData.texPos += g_frameData.step;
            ibuf += screenWidth * 4;
        }
        //make color darker for y-sides

       /* while (ibuf < (w + 4 * screenWidth * g_frameData.drawEnd)) //paint wall
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_frameData.color[i];
                i++;
            }
            ibuf += screenWidth * 4;
        }*/


        while (ibuf < (w + 4 * screenWidth * screenHeight)) //paint floor
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_frameData.floorColor[i];
                i++;
            }
            ibuf += screenWidth * 4;
        }
        x++;
        w += 4;
    }
    //print image
    mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_screenData.mlx_img_buffer, 0, 0);
    //destroy image
    mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
    g_screenData.mlx_img_buffer = NULL;

    //move forwards if no wall in front
    if (g_keyData.w)
    {
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    if (g_worldMap[(int)(g_player.posX + g_player.dirX * g_player.moveSpeed)][(int)g_player.posY] == 0)
        g_player.posX += g_player.dirX * g_player.moveSpeed;
    if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.dirY * g_player.moveSpeed)] == 0)
        g_player.posY += g_player.dirY * g_player.moveSpeed;
    }
      //move backwards if no wall in front
    if (g_keyData.s)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        if (g_worldMap[(int)(g_player.posX - g_player.dirX * g_player.moveSpeed)][(int)(g_player.posY)] == 0)
            g_player.posX -= g_player.dirX * g_player.moveSpeed;
        if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.dirY * g_player.moveSpeed)] == 0)
            g_player.posY -= g_player.dirY * g_player.moveSpeed;
    }
    //strafe right if no wall to right
    if (g_keyData.d)
        {
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, &g_player.newDirXY);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    if (g_worldMap[(int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
        g_player.posX += g_player.newDirXY[0] * g_player.moveSpeed;
    if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
        g_player.posY += g_player.newDirXY[1] * g_player.moveSpeed;
    }
    //strafe left if no wall to left
    if (g_keyData.a)
    {
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, &g_player.newDirXY);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    if (g_worldMap[(int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
        g_player.posX -= g_player.newDirXY[0] * g_player.moveSpeed;
    if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
        g_player.posY -= g_player.newDirXY[1] * g_player.moveSpeed;
    }

        //clockwise rotation
    if (g_keyData.r)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2D(g_player.dirX, g_player.dirY, 3, 6, &g_player.newDirXY);
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, 3, 6, &g_player.newDirXY);
        g_player.planeX = g_player.newDirXY[0];
        g_player.planeY = g_player.newDirXY[1];
    
        //método Lode
        /*g_player.oldDirX = g_player.dirX;
        g_player.dirX = g_player.dirX * cos(-g_player.rotSpeed) - g_player.dirY * sin(-g_player.rotSpeed);
        g_player.dirY = g_player.oldDirX * sin(-g_player.rotSpeed) + g_player.dirY * cos(-g_player.rotSpeed);
        g_player.oldPlaneX = g_player.planeX;
        g_player.planeX = g_player.planeX * cos(-g_player.rotSpeed) - g_player.planeY * sin(-g_player.rotSpeed);
        g_player.planeY = g_player.oldPlaneX * sin(-g_player.rotSpeed) + g_player.planeY * cos(-g_player.rotSpeed);*/
    }
    //anticlockwise rotation
    if (g_keyData.l)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "COUNTERCLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2D(g_player.dirX, g_player.dirY, -3, 6, &g_player.newDirXY);
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, -3, 6, &g_player.newDirXY);
        g_player.planeX = g_player.newDirXY[0];
        g_player.planeY = g_player.newDirXY[1];
        
        //método Lode
        /*g_player.oldDirX = g_player.dirX;
        g_player.dirX = g_player.dirX * cos(g_player.rotSpeed) - g_player.dirY * sin(g_player.rotSpeed);
        g_player.dirY = g_player.oldDirX * sin(g_player.rotSpeed) + g_player.dirY * cos(g_player.rotSpeed);
        g_player.oldPlaneX = g_player.planeX;
        g_player.planeX = g_player.planeX * cos(g_player.rotSpeed) - g_player.planeY * sin(g_player.rotSpeed);
        g_player.planeY = g_player.oldPlaneX * sin(g_player.rotSpeed) + g_player.planeY * cos(g_player.rotSpeed);*/
    }
  
    //framecounter
    fps++;
    if ((endTime = time(NULL) != seconds))
    {
        printf("%d, ", fps);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 300, 0x0000ff00, ft_itoa(fps));
        printFPS = fps;
        seconds = 0;
        fps = 0;
    }
    else
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 300, 0x0000ff00, ft_itoa(printFPS));       
    }
    
    //printf("%f, ", time_used);
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
    return (0);
}
    
  int   ft_stop(int key, void *param)
  {
    (void)param;
    if (key == 0x35 || key == 0x00)
    {
        mlx_destroy_window(g_screenData.mlx_ptr, g_screenData.mlx_win);
        mlx_destroy_image(g_screenData.mlx_ptr, g_clsImg.mlx_img);
        if (g_screenData.mlx_img_buffer)
            mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
        free(g_player.newDirXY);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

/*int     ft_start(int key, void *param)
{
    (void)param;
    if(key == 0x24)
    {
        ft_rayCaster();
        return (0);
    }
    return (-1);
}*/

int ft_keyPress(int key, void *param)
{
    (void)param;
    if (key == 0x35)
        ft_stop(key, (void *)0);
    //move forwards if no wall in front
    if (key == 0xD)
        g_keyData.w = 1;
    //move backwards if no wall in front
    if (key == 0x1)
        g_keyData.s = 1;
    //strafe right if no wall to right
    if (key == 0x2)
        g_keyData.d = 1;
    //strafe left if no wall to left
    if (key == 0x0)
        g_keyData.a = 1;
    //clockwise rotation
    if (key == 0x7C)
        g_keyData.r = 1;
    //anticlockwise rotation
    if (key == 0x7B)
        g_keyData.l = 1;
    return (0);
}

int ft_keyRelease(int key, void *param)
{
    (void)param;
    //move forwards if no wall in front
    if (key == 0xD)
        g_keyData.w = 0;
    //move backwards if no wall in front
    if (key == 0x1)
        g_keyData.s = 0;
    //strafe right if no wall to right
    if (key == 0x2)
        g_keyData.d = 0;
    //strafe left if no wall to left
    if (key == 0x0)
        g_keyData.a = 0;
    //clockwise rotation
    if (key == 0x7C)
        g_keyData.r = 0;
    //anticlockwise rotation
    if (key == 0x7B)
        g_keyData.l = 0;
    return (0);
}

void makeClsImg(void)
{
    int i;
    //int c;
    unsigned char *imgptr;

    g_clsImg.mlx_img = mlx_new_image(g_screenData.mlx_ptr, screenWidth, screenHeight);
    imgptr = (unsigned char *)mlx_get_data_addr(g_clsImg.mlx_img, &g_clsImg.bpp, &g_clsImg.size_line, &g_clsImg.endian);
    g_frameData.floorColor[0] = 153;
    g_frameData.floorColor[1] = 153;
    g_frameData.floorColor[2] = 102;
    g_frameData.floorColor[3] = 0;
    i = 0;
    /*while (i < screenWidth * screenHeight * 4)
    {
        c = 0;
        while (c < 4)
        {
            imgptr[i++] = g_frameData.backgroundColor[c++];
        }
    }*/
}

void    makeBrickImg(void)
{
    int texSize;

    texSize = 64;
    g_brickImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, "redBrick.XPM", &texSize, &texSize);
}

void initialize(void)
{
    g_player.posX = 22;
    g_player.posY = 12;
    g_player.dirX = -1;
    g_player.dirY = 0;
    g_player.planeX = 0;
    g_player.planeY = 0.66;
    g_frameData.time = 0;
    g_frameData.oldTime = 0;
    g_frameData.floorColor[0] = 153;
    g_frameData.floorColor[1] = 153;
    g_frameData.floorColor[2] = 102;
    g_frameData.floorColor[3] = 0;
    g_frameData.ceilingColor[0] = 75;
    g_frameData.ceilingColor[1] = 0;
    g_frameData.ceilingColor[2] = 102;
    g_frameData.ceilingColor[3] = 0;
}

  int   main(void/*int argc, char **argv*/)
  {
      g_player.newDirXY = malloc(2 * sizeof(double));
      


//Create screen
    if ((g_screenData.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screenData.mlx_win = mlx_new_window(g_screenData.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    initialize();
    makeClsImg();
    makeBrickImg();
    mlx_do_key_autorepeatoff(g_screenData.mlx_ptr);
    mlx_hook(g_screenData.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screenData.mlx_win, 2, 0, ft_keyPress, (void*)0);
    mlx_hook(g_screenData.mlx_win, 3, 0, ft_keyRelease, (void *)0);
    //mlx_key_hook(g_screenData.mlx_win, ft_start, (void*)0);
    //mlx_hook(g_screenData.mlx_win, 2, 0, ft_start, (void*)0);
    //while (g_stop)
    //{

    mlx_loop_hook(g_screenData.mlx_ptr, ft_rayCaster, (void *)0);    
    //}
    mlx_loop(g_screenData.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  