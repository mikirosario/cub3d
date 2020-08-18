/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasterPreNorm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:21:39 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/18 18:22:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int   ft_rayCaster(int key, void *param)
{
    int x;
    int ibuf;
    unsigned int *buf;
    unsigned int *texPtr;
    spriteData_t    *spritePtr;
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
	g_config.vMove = g_config.spriteH * g_config.vDiv;
    g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH);
    buf = (unsigned int *)mlx_get_data_addr(g_screenData.mlx_img_buffer, &g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
    if (stayOut == 'n')
    {
        nowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(nowallimg.mlx_img, &nowallimg.bpp, &nowallimg.size_line, &nowallimg.endian);
        sowallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(sowallimg.mlx_img, &sowallimg.bpp, &sowallimg.size_line, &sowallimg.endian);
        wewallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(wewallimg.mlx_img, &wewallimg.bpp, &wewallimg.size_line, &wewallimg.endian);
        eawallimg.tex_ptr = (unsigned int *)mlx_get_data_addr(eawallimg.mlx_img, &eawallimg.bpp, &eawallimg.size_line, &eawallimg.endian);

        if (g_config.spriteNum)
        {
            if (!(spriteOrder = (ft_calloc(g_config.spriteNum, sizeof(int)))))
                ft_stop(0x0, (void *)0);
        }
        if (!(zBuffer = (ft_calloc(g_config.screenW, sizeof(double)))))
            ft_stop(0x0, (void *)0);
        spritePtr = g_config.spriteList;
        while (spritePtr)
        {
            if (spritePtr->spriteType == '2') //asigna textura en función de sprite type
                spritePtr->texture = (unsigned int *)mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, &g_normiImg.size_line, &g_normiImg.endian);
            spritePtr = spritePtr->next;
        }
        
        /*while (tonti < g_config.spriteNum)
        {
            //g_config.spriteList->texture = (unsigned int *)mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, &g_normiImg.size_line, &g_normiImg.endian);
            g_sprite[tonti].texture = (unsigned int *)mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, &g_normiImg.size_line, &g_normiImg.endian);
            tonti++;
        }*/
        stayOut = 'y';
    }

    while (x < g_config.screenW)
    {
        //calculate ray position and direction
        g_player.cameraX = 2 * x / (double)g_config.screenW - 1;
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
            //check if ray has hit a wall
            //if (g_worldMap[g_rayData.mapX][g_rayData.mapY] > 0)
            if (maplist(g_rayData.mapX, g_rayData.mapY) == '1')
                g_rayData.hit = 1;
        }
        //calculate distance projected on camera direction
        if (g_rayData.side == 0)
            g_rayData.perpWallDist = (g_rayData.mapX - g_player.posX + (1 - g_rayData.stepX) / 2) / g_rayData.rayDirX;
        else
            g_rayData.perpWallDist = (g_rayData.mapY - g_player.posY + (1 - g_rayData.stepY) / 2) / g_rayData.rayDirY;
        //calculate height of line to draw on screen; multiplier controls wall height
        g_frameData.lineHeight = (int)(g_config.screenH * g_config.wallMultiplier / g_rayData.perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        g_frameData.drawStart = -(g_frameData.lineHeight) / 2 + g_config.screenH / 2;
        if (g_frameData.drawStart < 0)
            g_frameData.drawStart = 0;
        g_frameData.drawEnd = g_frameData.lineHeight / 2 + g_config.screenH / 2;
        if  (g_frameData.drawEnd >= g_config.screenH)
            g_frameData.drawEnd = g_config.screenH - 1;
        //draw pixels of stripe as vertical line
        ibuf = x;
        while (ibuf < (x + g_frameData.drawStart * g_config.screenW)) //paint ceiling
        {
            buf[ibuf] = g_frameData.oceilingColor;
            ibuf += g_config.screenW;
        }
        //choose texture
        //calculate value of wallX (x coordinate where wall was hit)
        if (g_rayData.side == 0)
            g_frameData.wallX = g_player.posY + g_rayData.perpWallDist * g_rayData.rayDirY;
        else
            g_frameData.wallX = g_player.posX + g_rayData.perpWallDist * g_rayData.rayDirX;
        g_frameData.wallX -= floor((g_frameData.wallX));
        
        //calculate x coordinate on the texture
        g_frameData.texX = (int)(g_frameData.wallX * (double)g_config.texW);
        if (g_rayData.side == 0 && g_rayData.rayDirX > 0)
            g_frameData.texX = (g_config.texW) - (g_frameData.texX) - 1;
        if (g_rayData.side == 1 && g_rayData.rayDirY < 0)
            g_frameData.texX = (g_config.texW) - (g_frameData.texX) - 1;
        
        //how much to increase texture coordinate per screen pixel
        g_frameData.step = 1.0 * g_config.texH / g_frameData.lineHeight;
        //starting texture coordinate
        g_frameData.texPos = (g_frameData.drawStart - g_config.screenH / 2 + g_frameData.lineHeight / 2) * g_frameData.step;
        
        while (ibuf < (x + g_frameData.drawEnd * g_config.screenW)) // paint texture wall
        {
             
            //select texture by square number (mode?)
            //cast texture coordinate with integer and mask with g_config.texH - 1 in case of overflow
            //texY gets rounded texPos; the less texPos changes, the longer for texY to increment; amount of texPos change depends on lineHeight and thus distance, times step
            /* g_frameData.texY = (int)(g_frameData.texPos) & (g_config.texH - 1);
            if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 1)
                texPtr = nowallimg.tex_ptr;
            else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 2)
                texPtr = sowallimg.texPpr;
            else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 3)
                texPtr = wewallimg.tex_ptr;
            else
                texPtr = eawallimg.tex_Ptr;
            //make color darker for y-sides
            buf[ibuf] = g_rayData.side == 1 ? (((texPtr[g_frameData.texX + g_frameData.texY * g_config.texW]) >> 1) & 8355711) : texPtr[g_frameData.texX + g_frameData.texY * g_config.texW];
            //increment texPos by step
            g_frameData.texPos += g_frameData.step;*/
            
            //select texture by square side (mode 0)
            if (g_keyData.m == 0 || g_keyData.m == 1)
            {
                //cast texture coordinate with integer and mask with g_config.texH - 1 in case of overflow
                //texY gets rounded texPos; the less texPos changes, the longer for texY to increment; amount of texPos change depends on lineHeight and thus distance, times step
                g_frameData.texY = (int)(g_frameData.texPos) & (g_config.texH - 1);
                if (g_rayData.side == 1 && g_rayData.stepY > 0) //west facing wall
                    texPtr = nowallimg.tex_ptr;
                else if (g_rayData.side == 1 && g_rayData.stepY < 0) //east facing wall
                    texPtr = sowallimg.tex_ptr;
                else if (g_rayData.side == 0 && g_rayData.stepX > 0) //south facing wall
                    texPtr = wewallimg.tex_ptr;
                else if (g_rayData.side == 0 && g_rayData.stepX < 0) //north facing wall
                    texPtr = eawallimg.tex_ptr;
                //make color darker for y-sides and paint walls
                if (g_keyData.m == 1)
                    buf[ibuf] = g_rayData.side == 1 ? (((texPtr[g_frameData.texX + g_frameData.texY * g_config.texW]) >> 1) & 8355711) : texPtr[g_frameData.texX + g_frameData.texY * g_config.texW];
                //just paint walls, no shading
                else
                    buf[ibuf] = texPtr[g_frameData.texX + g_frameData.texY * g_config.texW];
                //increment texPos by step
                g_frameData.texPos += g_frameData.step;
                ibuf += g_config.screenW;
            }

            //select color by square side (mode 1)
            else if (g_keyData.m == 2)
            //choose wall colour
            {
                //first reset color to black
                g_frameData.ocolor = 0;
                if (g_rayData.side == 1 && g_rayData.stepY > 0) //west facing wall
                    g_frameData.ocolor = 0x00ff0000; //red
                else if (g_rayData.side == 1 && g_rayData.stepY < 0) //east facing wall
                    g_frameData.ocolor = 0x0000ff00; //green
                else if (g_rayData.side == 0 && g_rayData.stepX > 0) //south facing wall
                    g_frameData.ocolor = 0x000000ff; //blue
                else if (g_rayData.side == 0 && g_rayData.stepX < 0) //north facing wall
                    g_frameData.ocolor = 0x00ffff00; //yellow
                //give x and y sides different brightnesses
                if (g_rayData.side == 1)
                    g_frameData.ocolor = g_frameData.ocolor >> 1;
                while (ibuf < (x + g_frameData.drawEnd * g_config.screenW)) //paint walls
                {
                    buf[ibuf] = g_frameData.ocolor;
                    ibuf += g_config.screenW;
                }
            }
        }
        while (ibuf < (x + (g_config.screenH - 1) * g_config.screenW)) //paint floor
        {
                buf[ibuf] = g_frameData.ofloorColor;
            ibuf += g_config.screenW;
        }
        //set zBuffer for sprite casting
        zBuffer[x] = g_rayData.perpWallDist; //perpendicular distances to walls from camera
        x++;
    }
    //Sprite Casting
    //sort sprites from far to close, creating a sorting mask at g_frameData spriteOrder, if there are sprites
    if (g_config.spriteNum)
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
    while (i < g_config.spriteNum)
    {
        //translate sprite position to relative to camera, taking most distant sprite first with order mask
        //spriteX = g_sprite[g_frameData.spriteOrder[i]].posX - g_player.posX;
        //spriteX = g_sprite[spriteOrder[i]].posX - g_player.posX;
        spriteX = (spriteiter(spriteOrder[i]))->posX - g_player.posX;
        //spriteY = g_sprite[g_frameData.spriteOrder[i]].posY - g_player.posY;
        //spriteY = g_sprite[spriteOrder[i]].posY - g_player.posY;
        spriteY = (spriteiter(spriteOrder[i]))->posY - g_player.posY;
        //transform sprite with the inverse camera matrix O_O
        invDet = 1.0 / (g_player.planeX * g_player.dirY - g_player.dirX * g_player.planeY); //required for correct matrix multiplication porque Lode lo dice
        transformX = invDet * (g_player.dirY * spriteX - g_player.dirX * spriteY);
        transformY = invDet * (-g_player.planeY * spriteX + g_player.planeX * spriteY); //screen depth, 3D zBuffer
        spriteScreenX = (int)((g_config.screenW / 2) * (1 + transformX / transformY));

        vMoveScreen = g_config.vMove == 0 ? 0 : (int)(g_config.vMove / transformY);
        //calculate height of the sprite on screen
        //división entre 0????
        spriteHeight = abs((int)(g_config.screenH / (transformY))) / g_config.vDiv; //using transformY instead of the real distance prevents fisheye
        //calculate the lowest and highest pixel to fill in the current stripe
        spriteDrawStartY = (-spriteHeight / 2 + g_config.screenH / 2 + vMoveScreen);
        if (spriteDrawStartY < 0)
            spriteDrawStartY = 0;
        spriteDrawEndY = spriteHeight / 2 + g_config.screenH / 2 + vMoveScreen;
        if (spriteDrawEndY >= g_config.screenH)
            spriteDrawEndY = g_config.screenH - 1;
        
        //calculate width of sprite
        spriteWidth = abs((int)(g_config.screenH / (transformY))) / g_config.uDiv;
        spriteDrawStartX = (-spriteWidth / 2 + spriteScreenX);
        if (spriteDrawStartX < 0)
            spriteDrawStartX = 0;
        spriteDrawEndX = spriteWidth / 2 + spriteScreenX;
        if (spriteDrawEndX >= g_config.screenW)
            spriteDrawEndX = g_config.screenW - 1;
        
        //paint sprite to buffer vertical line by vertical line
        stripe = spriteDrawStartX;
        while (stripe < spriteDrawEndX)
        {
            spriteTexX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * g_config.spriteW / spriteWidth) / 256;        
            //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            int y = spriteDrawStartY;
            int d;
            if (transformY > 0 && stripe > 0 && stripe < g_config.screenW && transformY < zBuffer[stripe])
            {
                while (y < spriteDrawEndY) //for every pixel of the current stripe
                {
                    d = (y - vMoveScreen) * 256 - g_config.screenH * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats =_=
                    spriteTexY = ((d * g_config.spriteH) / spriteHeight) / 256;
                    //g_frameData.ocolor = g_sprite[g_frameData.spriteOrder[i]].texture[g_config.spriteW * spriteTexY + spriteTexX]; //get current color from the texture
                    //g_frameData.ocolor = g_sprite[spriteOrder[i]].texture[g_config.spriteW * spriteTexY + spriteTexX]; //get current color from the texture
                    g_frameData.ocolor = (spriteiter(spriteOrder[i]))->texture[g_config.spriteW * spriteTexY + spriteTexX]; //get current color from the texture
                    if (g_frameData.ocolor != 0x0000ff00)
                        buf[stripe + (g_config.screenW * y)] = g_frameData.ocolor;
                    y++;
                }
            }
            stripe++;
        }
        i++;
    }
    //print image
    mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_screenData.mlx_img_buffer, 0, 0);
    //actualmente refresco mi buf creando y destruyéndolo cada frame, no sé si sería mas eficiente ponerlo a cero...
    mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
    g_screenData.mlx_img_buffer = NULL;

    //move forwards if no wall in front
    if (g_keyData.w)
    {
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "UP"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posX + g_player.dirX * g_player.moveSpeed)][(int)g_player.posY] == 0)
    if ((maplist((int)(g_player.posX + g_player.dirX * g_player.moveSpeed), (int)g_player.posY)) == '0')
        g_player.posX += g_player.dirX * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.dirY * g_player.moveSpeed)] == 0)
    if ((maplist((int)g_player.posX, (int)(g_player.posY + g_player.dirY * g_player.moveSpeed))) == '0')
        g_player.posY += g_player.dirY * g_player.moveSpeed;
    }
      //move backwards if no wall in front
    if (g_keyData.s)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        //if (g_worldMap[(int)(g_player.posX - g_player.dirX * g_player.moveSpeed)][(int)(g_player.posY)] == 0)
        if ((maplist((int)(g_player.posX - g_player.dirX * g_player.moveSpeed), (int)(g_player.posY)) == '0'))
            g_player.posX -= g_player.dirX * g_player.moveSpeed;
        //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.dirY * g_player.moveSpeed)] == 0)
        if ((maplist((int)g_player.posX, (int)(g_player.posY - g_player.dirY * g_player.moveSpeed))) == '0')
            g_player.posY -= g_player.dirY * g_player.moveSpeed;
    }
    //strafe left if no wall to left
    if (g_keyData.a)
    {
        ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
    if (maplist((int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
        g_player.posX += g_player.newDirXY[0] * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
    if (maplist((int)g_player.posX, (int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
        g_player.posY += g_player.newDirXY[1] * g_player.moveSpeed;
    }
    //strafe right if no wall to right
    if (g_keyData.d)
    {
        ft_rotate_2d(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
    if (maplist((int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
        g_player.posX -= g_player.newDirXY[0] * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
    if (maplist((int)g_player.posX, (int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
        g_player.posY -= g_player.newDirXY[1] * g_player.moveSpeed;
    }

        //clockwise rotation
    if (g_keyData.r)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2d(g_player.dirX, g_player.dirY, -3, 6, (double *)(&g_player.newDirXY));
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2d(g_player.planeX, g_player.planeY, -3, 6, (double *)(&g_player.newDirXY));
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
        ft_rotate_2d(g_player.dirX, g_player.dirY, 3, 6, (double *)(&g_player.newDirXY));
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2d(g_player.planeX, g_player.planeY, 3, 6, (double *)(&g_player.newDirXY));
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
        //printf("%d, ", fps);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 80, 0x0000ff00, ft_itoa(fps));
        printFPS = fps;
        seconds = 0;
        fps = 0;
    }
    else
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");       
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, g_config.screenH - 80, 0x0000ff00, ft_itoa(printFPS));       
    }
    
    //printf("%f, ", time_used);
    if (g_keyData.m == 0)
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 0 Grafx");
    else if (g_keyData.m == 1)
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 1 Grafx");
    else if (g_keyData.m == 2)
            mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "Mode 2 Grafx");
    return (0);
}