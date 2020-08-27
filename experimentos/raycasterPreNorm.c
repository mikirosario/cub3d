/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasterPreNorm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:21:39 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:19:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int   ft_rayCaster(int key, void *param)
{
    int x;
    int ibuf;
    unsigned int *buf;
    unsigned int *texPtr;
    t_spritedata    *spritePtr;
    static time_t seconds = 0; //ILLEGAL!
    time_t endTime; //ILLEGAL! Mi fpscounter.. Sniff.
    static int fps = 0;
    static int printFPS = 0;
    static char stayOut = 'n';
    static int *spriteOrder; //cómo le hago free? :( se hace al llegar a final de programa?)
    static double *zBuffer;

    (void)param;
    (void)key;

    if (!seconds)
        seconds = time(NULL);
    x = 0;
	g_config.vmove = g_config.spriteh * g_config.vdiv;
    g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, g_config.screenw, g_config.screenh);
    buf = (unsigned int *)mlx_get_data_addr(g_screendata.mlx_img_buffer, &g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian);
    if (stayOut == 'n')
    {
        g_nowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_nowallimg.mlx_img, &g_nowallimg.bpp, &g_nowallimg.size_line, &g_nowallimg.endian);
        g_sowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_sowallimg.mlx_img, &g_sowallimg.bpp, &g_sowallimg.size_line, &g_sowallimg.endian);
        g_wewallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_wewallimg.mlx_img, &g_wewallimg.bpp, &g_wewallimg.size_line, &g_wewallimg.endian);
        g_eawallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(g_eawallimg.mlx_img, &g_eawallimg.bpp, &g_eawallimg.size_line, &g_eawallimg.endian);

        if (g_config.spritenum)
        {
            if (!(spriteOrder = (ft_calloc(g_config.spritenum, sizeof(int)))))
                ft_stop(0x0, (void *)0);
        }
        if (!(zBuffer = (ft_calloc(g_config.screenw, sizeof(double)))))
            ft_stop(0x0, (void *)0);
        spritePtr = g_config.spritelist;
        while (spritePtr)
        {
            if (spritePtr->spritetype == '2') //asigna textura en función de sprite type
                spritePtr->texture = (unsigned int *)mlx_get_data_addr(g_sprt2img.mlx_img, &g_sprt2img.bpp, &g_sprt2img.size_line, &g_sprt2img.endian);
            spritePtr = spritePtr->next;
        }
        
        /*while (tonti < g_config.spritenum)
        {
            //g_config.spritelist->texture = (unsigned int *)mlx_get_data_addr(g_sprt2img.mlx_img, &g_sprt2img.bpp, &g_sprt2img.size_line, &g_sprt2img.endian);
            g_sprite[tonti].texture = (unsigned int *)mlx_get_data_addr(g_sprt2img.mlx_img, &g_sprt2img.bpp, &g_sprt2img.size_line, &g_sprt2img.endian);
            tonti++;
        }*/
        stayOut = 'y';
    }

    while (x < g_config.screenw)
    {
        //calculate ray position and direction
        g_player.camerax = 2 * x / (double)g_config.screenw - 1;
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
            //check if ray has hit a wall
            //if (g_worldMap[g_raydata.mapx][g_raydata.mapy] > 0)
            if (maplist(g_raydata.mapx, g_raydata.mapy) == '1')
                g_raydata.hit = 1;
        }
        //calculate distance projected on camera direction
        if (g_raydata.side == 0)
            g_raydata.perpwalldist = (g_raydata.mapx - g_player.posx + (1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
        else
            g_raydata.perpwalldist = (g_raydata.mapy - g_player.posy + (1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
        //calculate height of line to draw on screen; multiplier controls wall height
        g_framedata.lineheight = (int)(g_config.screenh * g_config.wallmultiplier / g_raydata.perpwalldist);
        //calculate lowest and highest pixel to fill in current stripe
        g_framedata.drawstart = -(g_framedata.lineheight) / 2 + g_config.screenh / 2;
        if (g_framedata.drawstart < 0)
            g_framedata.drawstart = 0;
        g_framedata.drawend = g_framedata.lineheight / 2 + g_config.screenh / 2;
        if  (g_framedata.drawend >= g_config.screenh)
            g_framedata.drawend = g_config.screenh - 1;
        //draw pixels of stripe as vertical line
        ibuf = x;
        while (ibuf < (x + g_framedata.drawstart * g_config.screenw)) //paint ceiling
        {
            buf[ibuf] = g_framedata.xceilingcolor;
            ibuf += g_config.screenw;
        }
        //choose texture
        //calculate value of wallX (x coordinate where wall was hit)
        if (g_raydata.side == 0)
            g_framedata.wallx = g_player.posy + g_raydata.perpwalldist * g_raydata.raydiry;
        else
            g_framedata.wallx = g_player.posx + g_raydata.perpwalldist * g_raydata.raydirx;
        g_framedata.wallx -= floor((g_framedata.wallx));
        
        //calculate x coordinate on the texture
        g_framedata.texx = (int)(g_framedata.wallx * (double)g_config.texw);
        if (g_raydata.side == 0 && g_raydata.raydirx > 0)
            g_framedata.texx = (g_config.texw) - (g_framedata.texx) - 1;
        if (g_raydata.side == 1 && g_raydata.raydiry < 0)
            g_framedata.texx = (g_config.texw) - (g_framedata.texx) - 1;
        
        //how much to increase texture coordinate per screen pixel
        g_framedata.step = 1.0 * g_config.texh / g_framedata.lineheight;
        //starting texture coordinate
        g_framedata.texpos = (g_framedata.drawstart - g_config.screenh / 2 + g_framedata.lineheight / 2) * g_framedata.step;
        
        while (ibuf < (x + g_framedata.drawend * g_config.screenw)) // paint texture wall
        {
             
            //select texture by square number (mode?)
            //cast texture coordinate with integer and mask with g_config.texh - 1 in case of overflow
            //texY gets rounded texPos; the less texPos changes, the longer for texY to increment; amount of texPos change depends on lineHeight and thus distance, times step
            /* g_framedata.texy = (int)(g_framedata.texpos) & (g_config.texh - 1);
            if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 1)
                texPtr = g_nowallimg.tex_ptr;
            else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 2)
                texPtr = g_sowallimg.texPpr;
            else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 3)
                texPtr = g_wewallimg.tex_ptr;
            else
                texPtr = g_eawallimg.tex_Ptr;
            //make color darker for y-sides
            buf[ibuf] = g_raydata.side == 1 ? (((texPtr[g_framedata.texx + g_framedata.texy * g_config.texw]) >> 1) & 8355711) : texPtr[g_framedata.texx + g_framedata.texy * g_config.texw];
            //increment texPos by step
            g_framedata.texpos += g_framedata.step;*/
            
            //select texture by square side (mode 0)
            if (g_keydata.m == 0 || g_keydata.m == 1)
            {
                //cast texture coordinate with integer and mask with g_config.texh - 1 in case of overflow
                //texY gets rounded texPos; the less texPos changes, the longer for texY to increment; amount of texPos change depends on lineHeight and thus distance, times step
                g_framedata.texy = (int)(g_framedata.texpos) & (g_config.texh - 1);
                if (g_raydata.side == 1 && g_raydata.stepy > 0) //west facing wall
                    texPtr = g_nowallimg.tex_ptr;
                else if (g_raydata.side == 1 && g_raydata.stepy < 0) //east facing wall
                    texPtr = g_sowallimg.tex_ptr;
                else if (g_raydata.side == 0 && g_raydata.stepx > 0) //south facing wall
                    texPtr = g_wewallimg.tex_ptr;
                else if (g_raydata.side == 0 && g_raydata.stepx < 0) //north facing wall
                    texPtr = g_eawallimg.tex_ptr;
                //make color darker for y-sides and paint walls
                if (g_keydata.m == 1)
                    buf[ibuf] = g_raydata.side == 1 ? (((texPtr[g_framedata.texx + g_framedata.texy * g_config.texw]) >> 1) & 8355711) : texPtr[g_framedata.texx + g_framedata.texy * g_config.texw];
                //just paint walls, no shading
                else
                    buf[ibuf] = texPtr[g_framedata.texx + g_framedata.texy * g_config.texw];
                //increment texPos by step
                g_framedata.texpos += g_framedata.step;
                ibuf += g_config.screenw;
            }

            //select color by square side (mode 1)
            else if (g_keydata.m == 2)
            //choose wall colour
            {
                //first reset color to black
                g_framedata.xcolor = 0;
                if (g_raydata.side == 1 && g_raydata.stepy > 0) //west facing wall
                    g_framedata.xcolor = 0x00ff0000; //red
                else if (g_raydata.side == 1 && g_raydata.stepy < 0) //east facing wall
                    g_framedata.xcolor = 0x0000ff00; //green
                else if (g_raydata.side == 0 && g_raydata.stepx > 0) //south facing wall
                    g_framedata.xcolor = 0x000000ff; //blue
                else if (g_raydata.side == 0 && g_raydata.stepx < 0) //north facing wall
                    g_framedata.xcolor = 0x00ffff00; //yellow
                //give x and y sides different brightnesses
                if (g_raydata.side == 1)
                    g_framedata.xcolor = g_framedata.xcolor >> 1;
                while (ibuf < (x + g_framedata.drawend * g_config.screenw)) //paint walls
                {
                    buf[ibuf] = g_framedata.xcolor;
                    ibuf += g_config.screenw;
                }
            }
        }
        while (ibuf < (x + (g_config.screenh - 1) * g_config.screenw)) //paint floor
        {
                buf[ibuf] = g_framedata.xfloorcolor;
            ibuf += g_config.screenw;
        }
        //set zBuffer for sprite casting
        zBuffer[x] = g_raydata.perpwalldist; //perpendicular distances to walls from camera
        x++;
    }
    //Sprite Casting
    //sort sprites from far to close, creating a sorting mask at g_framedata spriteOrder, if there are sprites
    if (g_config.spritenum)
        ft_sortSprites(spriteOrder);
    //having sorted sprites, project and draw them
    int     i;
    int     stripe;
    double  spriteX;
    double  spriteY;
    double  invDet;
    double  transformX;
    double  transformY;
    int     spriteScreenX;
    int     spriteHeight;
    int     spriteWidth;
    int     spriteDrawStartX;
    int     spriteDrawEndX;
    int     spriteDrawStartY;
    int     spriteDrawEndY;
    int     spriteTexX;
    int     spriteTexY;
    int     vMoveScreen;

    i = 0;
    while (i < g_config.spritenum)
    {
        //translate sprite position to relative to camera, taking most distant sprite first with order mask
        //spriteX = g_sprite[g_framedata.spriteOrder[i]].posx - g_player.posx;
        //spriteX = g_sprite[spriteOrder[i]].posx - g_player.posx;
        spriteX = (spriteiter(spriteOrder[i]))->posx - g_player.posx;
        //spriteY = g_sprite[g_framedata.spriteOrder[i]].posy - g_player.posy;
        //spriteY = g_sprite[spriteOrder[i]].posy - g_player.posy;
        spriteY = (spriteiter(spriteOrder[i]))->posy - g_player.posy;
        //transform sprite with the inverse camera matrix O_O
        invDet = 1.0 / (g_player.planex * g_player.diry - g_player.dirx * g_player.planey); //required for correct matrix multiplication porque Lode lo dice
        transformX = invDet * (g_player.diry * spriteX - g_player.dirx * spriteY);
        transformY = invDet * (-g_player.planey * spriteX + g_player.planex * spriteY); //screen depth, 3D zBuffer
        spriteScreenX = (int)((g_config.screenw / 2) * (1 + transformX / transformY));

        vMoveScreen = g_config.vmove == 0 ? 0 : (int)(g_config.vmove / transformY);
        //calculate height of the sprite on screen
        //división entre 0????
        spriteHeight = abs((int)(g_config.screenh / (transformY))) / g_config.vdiv; //using transformY instead of the real distance prevents fisheye
        //calculate the lowest and highest pixel to fill in the current stripe
        spriteDrawStartY = (-spriteHeight / 2 + g_config.screenh / 2 + vMoveScreen);
        if (spriteDrawStartY < 0)
            spriteDrawStartY = 0;
        spriteDrawEndY = spriteHeight / 2 + g_config.screenh / 2 + vMoveScreen;
        if (spriteDrawEndY >= g_config.screenh)
            spriteDrawEndY = g_config.screenh - 1;
        
        //calculate width of sprite
        spriteWidth = abs((int)(g_config.screenh / (transformY))) / g_config.udiv;
        spriteDrawStartX = (-spriteWidth / 2 + spriteScreenX);
        if (spriteDrawStartX < 0)
            spriteDrawStartX = 0;
        spriteDrawEndX = spriteWidth / 2 + spriteScreenX;
        if (spriteDrawEndX >= g_config.screenw)
            spriteDrawEndX = g_config.screenw - 1;
        
        //paint sprite to buffer vertical line by vertical line
        stripe = spriteDrawStartX;
        while (stripe < spriteDrawEndX)
        {
            spriteTexX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * g_config.spritew / spriteWidth) / 256;        
            //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            int y = spriteDrawStartY;
            int d;
            if (transformY > 0 && stripe > 0 && stripe < g_config.screenw && transformY < zBuffer[stripe])
            {
                while (y < spriteDrawEndY) //for every pixel of the current stripe
                {
                    d = (y - vMoveScreen) * 256 - g_config.screenh * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats =_=
                    spriteTexY = ((d * g_config.spriteh) / spriteHeight) / 256;
                    //g_framedata.xcolor = g_sprite[g_framedata.spriteOrder[i]].texture[g_config.spritew * spriteTexY + spriteTexX]; //get current color from the texture
                    //g_framedata.xcolor = g_sprite[spriteOrder[i]].texture[g_config.spritew * spriteTexY + spriteTexX]; //get current color from the texture
                    g_framedata.xcolor = (spriteiter(spriteOrder[i]))->texture[g_config.spritew * spriteTexY + spriteTexX]; //get current color from the texture
                    if (g_framedata.xcolor != 0x0000ff00)
                        buf[stripe + (g_config.screenw * y)] = g_framedata.xcolor;
                    y++;
                }
            }
            stripe++;
        }
        i++;
    }
    //print image
    mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_screendata.mlx_img_buffer, 0, 0);
    //actualmente refresco mi buf creando y destruyéndolo cada frame, no sé si sería mas eficiente ponerlo a cero...
    mlx_destroy_image(g_screendata.mlx_ptr, g_screendata.mlx_img_buffer);
    g_screendata.mlx_img_buffer = NULL;

    //move forwards if no wall in front
    if (g_keydata.w)
    {
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posx + g_player.dirx * g_player.movespeed)][(int)g_player.posy] == 0)
    if ((maplist((int)(g_player.posx + g_player.dirx * g_player.movespeed), (int)g_player.posy)) == '0')
        g_player.posx += g_player.dirx * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.diry * g_player.movespeed)] == 0)
    if ((maplist((int)g_player.posx, (int)(g_player.posy + g_player.diry * g_player.movespeed))) == '0')
        g_player.posy += g_player.diry * g_player.movespeed;
    }
      //move backwards if no wall in front
    if (g_keydata.s)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        //if (g_worldMap[(int)(g_player.posx - g_player.dirx * g_player.movespeed)][(int)(g_player.posy)] == 0)
        if ((maplist((int)(g_player.posx - g_player.dirx * g_player.movespeed), (int)(g_player.posy)) == '0'))
            g_player.posx -= g_player.dirx * g_player.movespeed;
        //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.diry * g_player.movespeed)] == 0)
        if ((maplist((int)g_player.posx, (int)(g_player.posy - g_player.diry * g_player.movespeed))) == '0')
            g_player.posy -= g_player.diry * g_player.movespeed;
    }
    //strafe left if no wall to left
    if (g_keydata.a)
    {
        ft_rotate_2d(g_player.dirx, g_player.diry, 90, 6, (double *)(&g_player.newdirxy));
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posx + g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
    if (maplist((int)(g_player.posx + g_player.newdirxy[0] * g_player.movespeed), (int)g_player.posy) == '0')
        g_player.posx += g_player.newdirxy[0] * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.newdirxy[1] * g_player.movespeed)] == 0)
    if (maplist((int)g_player.posx, (int)(g_player.posy + g_player.newdirxy[1] * g_player.movespeed)) == '0')
        g_player.posy += g_player.newdirxy[1] * g_player.movespeed;
    }
    //strafe right if no wall to right
    if (g_keydata.d)
    {
        ft_rotate_2d(g_player.dirx, g_player.diry, 90, 6, (double *)(&g_player.newdirxy));
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posx - g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
    if (maplist((int)(g_player.posx - g_player.newdirxy[0] * g_player.movespeed), (int)g_player.posy) == '0')
        g_player.posx -= g_player.newdirxy[0] * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.newdirxy[1] * g_player.movespeed)] == 0)
    if (maplist((int)g_player.posx, (int)(g_player.posy - g_player.newdirxy[1] * g_player.movespeed)) == '0')
        g_player.posy -= g_player.newdirxy[1] * g_player.movespeed;
    }

        //clockwise rotation
    if (g_keydata.r)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2d(g_player.dirx, g_player.diry, -3, 6, (double *)(&g_player.newdirxy));
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2d(g_player.planex, g_player.planey, -3, 6, (double *)(&g_player.newdirxy));
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
        ft_rotate_2d(g_player.dirx, g_player.diry, 3, 6, (double *)(&g_player.newdirxy));
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2d(g_player.planex, g_player.planey, 3, 6, (double *)(&g_player.newdirxy));
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
        //printf("%d, ", fps);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, g_config.screenh - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, g_config.screenh - 80, 0x0000ff00, ft_itoa(fps));
        printFPS = fps;
        seconds = 0;
        fps = 0;
    }
    else
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, g_config.screenh - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, g_config.screenh - 80, 0x0000ff00, ft_itoa(printFPS));       
    }
    
    //printf("%f, ", time_used);
    if (g_keydata.m == 0)
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, g_config.screenw / 2, 0, 0x0000ff00, "Mode 0 Grafx");
    else if (g_keydata.m == 1)
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, g_config.screenw / 2, 0, 0x0000ff00, "Mode 1 Grafx");
    else if (g_keydata.m == 2)
            mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, g_config.screenw / 2, 0, 0x0000ff00, "Mode 2 Grafx");
    return (0);
}