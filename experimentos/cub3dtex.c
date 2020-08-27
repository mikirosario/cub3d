/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dtex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:15:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cub3d.h"

  /*g_player.posx = 0;
  g_player.posy = -1;
  g_player.dirx = 0;
  g_player.diry = 1;*/
 
  void cls()
{
    int x;
    int y;

    x = 0;
        while (x <= 640) //clearscreen
        {
            y = 480;
            while (y)
            {
                mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, y--, 0x0);
            }
            x++;
        }
}

void    sky_put()
{
    int x;
    int y;

    x = 0;
    while (x <= 640)
    {
        y = 480;
        while (y)
        {
            mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, y--, 0x00DBFFFF);
        }
        x++;
    }
}

  int   imagedump(int key, void *param)
  {
    int x;
    int y;

    x = 0;
    y = 0;
    (void)param;
    (void)key;
    sky_put();
    while (x < 418)
    {
        y = 0;
        while (y < screenHeight)
        {
            mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_brickImg.mlx_img, x, y);
            y += 418;
        }
        x += 418;
    }
    return (0);
  }

  int   imagepaint(int key, void *param)
  {
    (void)key;
    (void)param;
    static int x = 0;
    //int y = 0;
    int i;
    int c;
    int o;
    static int t = 0;
    //int xpos = 0;
    int pos;
    int ibuf;
    char *buf;
    char *img;

    buf = mlx_get_data_addr(g_screendata.mlx_img_buffer, &g_brickImg.bpp, &g_brickImg.size_line, &g_brickImg.endian);
    img = mlx_get_data_addr(g_brickImg.mlx_img, &g_brickImg.bpp, &g_brickImg.size_line, &g_brickImg.endian);

    ibuf = 0;
    c = 0;
    o = 0;
    
    pos = x;
    while (c++ <= screenHeight)
    {
        i = 0;
        while (i < 4)
            buf[ibuf++] = img[pos + i++];
    if (o++ == 417)
    {
        pos = x;
        o = 0;
    }
    else
        pos += (418 * 4);
    }
    if (x > 1671)
        x = 0;
    else
        x += 4;
    if (t > 640)
    {
        t = 0;
        x = 0;
    }
    mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_screendata.mlx_img_buffer, t++, 0);
    //mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);

    /*while (x < 418)
    {
        xpos = 4 * x;
        ibuf = 0;
        y = 0;
        while (y <= 418)
        {
            ypos = (xpos + 4) * (418 * 4) * y;
            i = 0;
            while (i < 4)
            {
                buf[ibuf++] = img[ypos + i++];
            }
            y++;
        }
        mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, buf, 0, 0);
        mlx_destroy_image(g_screendata.mlx_ptr, buf);
        x++;
    }*/
        
    return (0);
  }
  
  int   stop(int key, void *param)
  {
    (void)param;
    if (key == 0x35 || key == 0x00)
    {
        mlx_destroy_image(g_screendata.mlx_ptr, g_brickImg.mlx_img);
        mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
        mlx_destroy_window(g_screendata.mlx_ptr, g_screendata.mlx_win);
        exit(0);
    }
    return (0);
  }

  int   loadTextures(void)
  {
    int textureSize = 418;
    g_brickImg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, "redbrick.XPM", &textureSize, &textureSize);
    
  }
  
  int   main(void)
  {
    if ((g_screendata.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, 640, 480, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    //Create Texture Buffer
    g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, 1, screenHeight);
    mlx_hook(g_screendata.mlx_win, 2, 0, stop, (void *)0);
    mlx_hook(g_screendata.mlx_win, 17, 0, stop, (void *)0);
    mlx_loop_hook(g_screendata.mlx_ptr, imagepaint, (void *)0);
    mlx_loop(g_screendata.mlx_ptr); 
    return (EXIT_SUCCESS);
  }
  