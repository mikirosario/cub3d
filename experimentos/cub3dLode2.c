/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dLode2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:21:10 by mrosario         ###   ########.fr       */
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
                mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, y--, 0x0);
            }
            x++;
        }
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
}*/

//image dump cls
void    cls()
{
    mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_clsimg.mlx_img, 0, 0);
    /*mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 300, 0x0000ff00, ft_itoa(printFPS));       */
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
    g_player.movespeed = 0.25;
    g_player.rotspeed = 0.1;

    if (!seconds)
        seconds = time(NULL);
    x = 0;
    w = 0;
    g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, screenWidth, screenHeight);
    buf = (unsigned char *)mlx_get_data_addr(g_screendata.mlx_img_buffer, &g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian);
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
        //calculate height of line to draw on screen; multiplier controls wall height
        g_framedata.lineheight = (int)(screenHeight * 2 / g_raydata.perpwalldist);
        //calculate lowest and highest pixel to fill in current stripe
        g_framedata.drawstart = -(g_framedata.lineheight) / 2 + screenHeight / 2;
        if (g_framedata.drawstart < 0)
            g_framedata.drawstart = 0;
        g_framedata.drawend = g_framedata.lineheight / 2 + screenHeight / 2;
        if  (g_framedata.drawend >= screenHeight)
            g_framedata.drawend = screenHeight - 1;
        //choose wall colour
        i = 0;
        //first reset color to black
        while (i < 4)
            g_framedata.color[i++] = 0;
        i = 0;
        if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 1)
            g_framedata.color[2] = 255; //red
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 2)
            g_framedata.color[1] = 255; //green
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 3)
            g_framedata.color[0] = 255; //blue
        else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 4)
        {
            i = 0;
            while (i < 3)
                g_framedata.color[i++] = 255; //white
        }
        else
        {
            i = 0;
            while (i < 2)
            g_framedata.color[i++] = 255; //yellow
        }
        //give x and y sides different brightnesses
        if (g_raydata.side == 1)
        {
            i = 0;
            while (i < 3)
            {
                if (g_framedata.color[i])
                {
                    g_framedata.color[i] = g_framedata.color[i] >> 1;
                }
                i++;
            }
        }
        //draw pixels of stripe as vertical line
        ibuf = w;
        //printf("%d%d%d%d, ", g_framedata.color[0], g_framedata.color[1], g_framedata.color[2], g_framedata.color[3]);
        while (ibuf < (w + 4 * screenWidth * g_framedata.drawstart)) //paint ceiling
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_framedata.ceilingcolor[i];
                i++;   
            }
            ibuf += screenWidth * 4;
        }
        while (ibuf < (w + 4 * screenWidth * g_framedata.drawend)) //paint wall
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_framedata.color[i];
                i++;
            }
            ibuf += screenWidth * 4;
        }
        while (ibuf < (w + 4 * screenWidth * screenHeight)) //paint floor
        {
            i = 0;
            while (i < 4)
            {
                buf[ibuf + i] = g_framedata.floorcolor[i];
                i++;
            }
            ibuf += screenWidth * 4;
        }
        x++;
        w += 4;
    }
    //print image
    mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_screendata.mlx_img_buffer, 0, 0);
    //destroy image
    mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
    g_screendata.mlx_img_buffer = NULL;

    //move forwards if no wall in front
    if (g_keydata.w)
    {
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    if (g_worldMap[(int)(g_player.posx + g_player.dirx * g_player.movespeed)][(int)g_player.posy] == 0)
        g_player.posx += g_player.dirx * g_player.movespeed;
    if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.diry * g_player.movespeed)] == 0)
        g_player.posy += g_player.diry * g_player.movespeed;
    }
      //move backwards if no wall in front
    if (g_keydata.s)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        if (g_worldMap[(int)(g_player.posx - g_player.dirx * g_player.movespeed)][(int)(g_player.posy)] == 0)
            g_player.posx -= g_player.dirx * g_player.movespeed;
        if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.diry * g_player.movespeed)] == 0)
            g_player.posy -= g_player.diry * g_player.movespeed;
    }
    //strafe right if no wall to right
    if (g_keydata.d)
        {
        ft_rotate_2D(g_player.dirx, g_player.diry, 90, 6, &g_player.newdirxy);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    if (g_worldMap[(int)(g_player.posx + g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
        g_player.posx += g_player.newdirxy[0] * g_player.movespeed;
    if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.newdirxy[1] * g_player.movespeed)] == 0)
        g_player.posy += g_player.newdirxy[1] * g_player.movespeed;
    }
    //strafe left if no wall to left
    if (g_keydata.a)
    {
        ft_rotate_2D(g_player.dirx, g_player.diry, 90, 6, &g_player.newdirxy);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    if (g_worldMap[(int)(g_player.posx - g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
        g_player.posx -= g_player.newdirxy[0] * g_player.movespeed;
    if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.newdirxy[1] * g_player.movespeed)] == 0)
        g_player.posy -= g_player.newdirxy[1] * g_player.movespeed;
    }

        //clockwise rotation
    if (g_keydata.r)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2D(g_player.dirx, g_player.diry, 3, 6, &g_player.newdirxy);
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2D(g_player.planex, g_player.planey, 3, 6, &g_player.newdirxy);
        g_player.planex = g_player.newdirxy[0];
        g_player.planey = g_player.newdirxy[1];
    
        //método Lode
        /*g_player.oldDirX = g_player.dirx;
        g_player.dirx = g_player.dirx * cos(-g_player.rotspeed) - g_player.diry * sin(-g_player.rotspeed);
        g_player.diry = g_player.oldDirX * sin(-g_player.rotspeed) + g_player.diry * cos(-g_player.rotspeed);
        g_player.oldPlaneX = g_player.planex;
        g_player.planex = g_player.planex * cos(-g_player.rotspeed) - g_player.planey * sin(-g_player.rotspeed);
        g_player.planey = g_player.oldPlaneX * sin(-g_player.rotspeed) + g_player.planey * cos(-g_player.rotspeed);*/
    }
    //anticlockwise rotation
    if (g_keydata.l)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "COUNTERCLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2D(g_player.dirx, g_player.diry, -3, 6, &g_player.newdirxy);
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2D(g_player.planex, g_player.planey, -3, 6, &g_player.newdirxy);
        g_player.planex = g_player.newdirxy[0];
        g_player.planey = g_player.newdirxy[1];
        
        //método Lode
        /*g_player.oldDirX = g_player.dirx;
        g_player.dirx = g_player.dirx * cos(g_player.rotspeed) - g_player.diry * sin(g_player.rotspeed);
        g_player.diry = g_player.oldDirX * sin(g_player.rotspeed) + g_player.diry * cos(g_player.rotspeed);
        g_player.oldPlaneX = g_player.planex;
        g_player.planex = g_player.planex * cos(g_player.rotspeed) - g_player.planey * sin(g_player.rotspeed);
        g_player.planey = g_player.oldPlaneX * sin(g_player.rotspeed) + g_player.planey * cos(g_player.rotspeed);*/
    }
  
    //framecounter
    fps++;
    if ((endTime = time(NULL) != seconds))
    {
        printf("%d, ", fps);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 300, 0x0000ff00, ft_itoa(fps));
        printFPS = fps;
        seconds = 0;
        fps = 0;
    }
    else
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 280, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 300, 0x0000ff00, ft_itoa(printFPS));       
    }
    
    //printf("%f, ", time_used);
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, screenWidth / 2, 0, 0x0000ff00, "TEST");
    return (0);
}
    
  int   ft_stop(int key, void *param)
  {
    (void)param;
    if (key == 0x35 || key == 0x00)
    {
        mlx_destroy_window(g_screendata.mlx_ptr, g_screendata.mlx_win);
        mlx_destroy_image(g_screendata.mlx_ptr, g_clsimg.mlx_img);
        if (g_screendata.mlx_img_buffer)
            mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
        free(g_player.newdirxy);
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
        g_keydata.w = 1;
    //move backwards if no wall in front
    if (key == 0x1)
        g_keydata.s = 1;
    //strafe right if no wall to right
    if (key == 0x2)
        g_keydata.d = 1;
    //strafe left if no wall to left
    if (key == 0x0)
        g_keydata.a = 1;
    //clockwise rotation
    if (key == 0x7C)
        g_keydata.r = 1;
    //anticlockwise rotation
    if (key == 0x7B)
        g_keydata.l = 1;
    return (0);
}

int ft_keyRelease(int key, void *param)
{
    (void)param;
    //move forwards if no wall in front
    if (key == 0xD)
        g_keydata.w = 0;
    //move backwards if no wall in front
    if (key == 0x1)
        g_keydata.s = 0;
    //strafe right if no wall to right
    if (key == 0x2)
        g_keydata.d = 0;
    //strafe left if no wall to left
    if (key == 0x0)
        g_keydata.a = 0;
    //clockwise rotation
    if (key == 0x7C)
        g_keydata.r = 0;
    //anticlockwise rotation
    if (key == 0x7B)
        g_keydata.l = 0;
    return (0);
}

void makeclsimg(void)
{
    int i;
    //int c;
    unsigned char *imgptr;

    g_clsimg.mlx_img = mlx_new_image(g_screendata.mlx_ptr, screenWidth, screenHeight);
    imgptr = (unsigned char *)mlx_get_data_addr(g_clsimg.mlx_img, &g_clsimg.bpp, &g_clsimg.size_line, &g_clsimg.endian);
    g_framedata.floorcolor[0] = 153;
    g_framedata.floorcolor[1] = 153;
    g_framedata.floorcolor[2] = 102;
    g_framedata.floorcolor[3] = 0;
    i = 0;
    /*while (i < screenWidth * screenHeight * 4)
    {
        c = 0;
        while (c < 4)
        {
            imgptr[i++] = g_framedata.backgroundColor[c++];
        }
    }*/
}


void initialize(void)
{
    g_player.posx = 22;
    g_player.posy = 12;
    g_player.dirx = -1;
    g_player.diry = 0;
    g_player.planex = 0;
    g_player.planey = 0.66;
    g_framedata.time = 0;
    g_framedata.oldTime = 0;
    g_framedata.floorcolor[0] = 153;
    g_framedata.floorcolor[1] = 153;
    g_framedata.floorcolor[2] = 102;
    g_framedata.floorcolor[3] = 0;
    g_framedata.ceilingcolor[0] = 75;
    g_framedata.ceilingcolor[1] = 0;
    g_framedata.ceilingcolor[2] = 102;
    g_framedata.ceilingcolor[3] = 0;
}

  int   main(void/*int argc, char **argv*/)
  {
      g_player.newdirxy = malloc(2 * sizeof(double));
      


//Create screen
    if ((g_screendata.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    initialize();
    makeclsimg();
    mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
    mlx_hook(g_screendata.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screendata.mlx_win, 2, 0, ft_keyPress, (void*)0);
    mlx_hook(g_screendata.mlx_win, 3, 0, ft_keyRelease, (void *)0);
    //mlx_key_hook(g_screendata.mlx_win, ft_start, (void*)0);
    //mlx_hook(g_screendata.mlx_win, 2, 0, ft_start, (void*)0);
    //while (g_stop)
    //{

    mlx_loop_hook(g_screendata.mlx_ptr, ft_rayCaster, (void *)0);    
    //}
    mlx_loop(g_screendata.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  