/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/03/10 20:24:31 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cub3d.h"

  //pixel_put cls
/*  void cls()
{
    int x;
    int y;

    x = 0;
        while (x <= g_config.screenW) //clearscreen
        {
            y = g_config.screenH;
            while (y)
            {
                mlx_pixel_put(g_screenData.mlx_ptr, g_screenData.mlx_win, x, y--, 0x0);
            }
            x++;
        }
    mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, g_config.screenW / 2, 0, 0x0000ff00, "TEST");
}*/

void    del(void *freeThis)
{
    free(freeThis);
    freeThis = NULL;
}

void    freeList(t_list **alst)
{
    t_list *tmp;

    ft_lstiter(*alst, del);
    while (*alst)
    {
        tmp = (&(**alst))->next;
        free(*alst);
        *alst = tmp;
    }
}

char    mapList(int x, int y)
{
    t_list  *ptr;
    int     i;
(void)y;
    i = 0;
    ptr = g_config.Map;
    while (i++ < y)
        ptr = ptr->next;
    return (*((char *)(ptr->content + x)));
}

//image dump cls
void    cls()
{
   mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_clsImg.mlx_img, 0, 0);
}

void    ft_sortSprites()
{
    double  distance[numSprites];
    int     tmp;
    int     i;

//first get relative player-sprite distances == playerpos - spritepos. magia matemática.
i = 0;
while (i < numSprites)
{
    g_frameData.spriteOrder[i] = i;
    distance[i] = ((g_player.posX - g_sprite[i].x) * (g_player.posX - g_sprite[i].x) + (g_player.posY - g_sprite[i].y) * (g_player.posY - g_sprite[i].y));
    i++;
}
i = -1;
while (numSprites > 1 && ++i < numSprites - 1)
{
    if (distance[i] < distance[i + 1])
    {
        tmp = distance[i];
        distance[i] = distance[i + 1];
        distance[i + 1] = tmp;
        tmp = g_frameData.spriteOrder[i];
        g_frameData.spriteOrder[i] = g_frameData.spriteOrder[i + 1];
        g_frameData.spriteOrder[i + 1] = tmp;
        i = -1;
    }
}

}

int   ft_rayCaster(int key, void *param)
{
    int x;
    int ibuf;
    unsigned int *buf;
    unsigned int *texPtr;
    static time_t seconds = 0; //ILLEGAL!
    time_t endTime; //ILLEGAL! Mi fpscounter.. Sniff.
    static int fps = 0;
    static int printFPS = 0;
    static char stayOut = 'n';

    (void)param;
    (void)key;

    if (!seconds)
        seconds = time(NULL);
    x = 0;

    g_screenData.mlx_img_buffer = mlx_new_image(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH);
    buf = (unsigned int *)mlx_get_data_addr(g_screenData.mlx_img_buffer, &g_screenData.bpp, &g_screenData.size_line, &g_screenData.endian);
    if (stayOut == 'n')
    {
        int tonti = 0;
        g_blueMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_blueMetalImg.mlx_img, &g_blueMetalImg.bpp, &g_blueMetalImg.size_line, &g_blueMetalImg.endian);
        g_yellowMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_yellowMetalImg.mlx_img, &g_yellowMetalImg.bpp, &g_yellowMetalImg.size_line, &g_yellowMetalImg.endian);
        g_greenMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_greenMetalImg.mlx_img, &g_greenMetalImg.bpp, &g_greenMetalImg.size_line, &g_greenMetalImg.endian);
        g_pinkMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_pinkMetalImg.mlx_img, &g_pinkMetalImg.bpp, &g_pinkMetalImg.size_line, &g_pinkMetalImg.endian);
        while (tonti < numSprites)
        {
            g_sprite[tonti].texture = (unsigned int *)mlx_get_data_addr(g_normiImg.mlx_img, &g_normiImg.bpp, &g_normiImg.size_line, &g_normiImg.endian);
            tonti++;
        }
        stayOut = 'y';
    }
    cls();
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
            if (mapList(g_rayData.mapX, g_rayData.mapY) == '1')
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
                texPtr = g_blueMetalImg.tex_Ptr;
            else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 2)
                texPtr = g_yellowMetalImg.texPtr;
            else if (g_worldMap[g_rayData.mapX][g_rayData.mapY] == 3)
                texPtr = g_greenMetalImg.tex_Ptr;
            else
                texPtr = g_pinkMetalImg.tex_Ptr;
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
                    texPtr = g_blueMetalImg.tex_Ptr;
                else if (g_rayData.side == 1 && g_rayData.stepY < 0) //east facing wall
                    texPtr = g_yellowMetalImg.tex_Ptr;
                else if (g_rayData.side == 0 && g_rayData.stepX > 0) //south facing wall
                    texPtr = g_greenMetalImg.tex_Ptr;
                else if (g_rayData.side == 0 && g_rayData.stepX < 0) //north facing wall
                    texPtr = g_pinkMetalImg.tex_Ptr;
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
        g_frameData.zBuffer[x] = g_rayData.perpWallDist; //perpendicular distances to walls from camera
        x++;
    }
    //Sprite Casting
    //sort sprites from far to close, creating a sorting mask at g_frameData spriteOrder, if there are sprites
    if (numSprites)
        ft_sortSprites();
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
    while (i < numSprites)
    {
        //translate sprite position to relative to camera, taking most distant sprite first with order mask
        spriteX = g_sprite[g_frameData.spriteOrder[i]].x - g_player.posX;
        spriteY = g_sprite[g_frameData.spriteOrder[i]].y - g_player.posY;
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
            if (transformY > 0 && stripe > 0 && stripe < g_config.screenW && transformY < g_frameData.zBuffer[stripe])
            {
                while (y < spriteDrawEndY) //for every pixel of the current stripe
                {
                    d = (y - vMoveScreen) * 256 - g_config.screenH * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats =_=
                    spriteTexY = ((d * g_config.spriteH) / spriteHeight) / 256;
                    g_frameData.ocolor = g_sprite[g_frameData.spriteOrder[i]].texture[g_config.spriteW * spriteTexY + spriteTexX]; //get current color from the texture
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
    if ((mapList((int)(g_player.posX + g_player.dirX * g_player.moveSpeed), (int)g_player.posY)) == '0')
        g_player.posX += g_player.dirX * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.dirY * g_player.moveSpeed)] == 0)
    if ((mapList((int)g_player.posX, (int)(g_player.posY + g_player.dirY * g_player.moveSpeed))) == '0')
        g_player.posY += g_player.dirY * g_player.moveSpeed;
    }
      //move backwards if no wall in front
    if (g_keyData.s)
    {
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        //if (g_worldMap[(int)(g_player.posX - g_player.dirX * g_player.moveSpeed)][(int)(g_player.posY)] == 0)
        if ((mapList((int)(g_player.posX - g_player.dirX * g_player.moveSpeed), (int)(g_player.posY)) == '0'))
            g_player.posX -= g_player.dirX * g_player.moveSpeed;
        //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.dirY * g_player.moveSpeed)] == 0)
        if ((mapList((int)g_player.posX, (int)(g_player.posY - g_player.dirY * g_player.moveSpeed))) == '0')
            g_player.posY -= g_player.dirY * g_player.moveSpeed;
    }
    //strafe right if no wall to right
    if (g_keyData.d)
        {
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, &g_player.newDirXY);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
    if (mapList((int)(g_player.posX + g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
        g_player.posX += g_player.newDirXY[0] * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
    if (mapList((int)g_player.posX, (int)(g_player.posY + g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
        g_player.posY += g_player.newDirXY[1] * g_player.moveSpeed;
    }
    //strafe left if no wall to left
    if (g_keyData.a)
    {
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, &g_player.newDirXY);
        mlx_string_put(g_screenData.mlx_ptr, g_screenData.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed)][(int)g_player.posY] == 0)
    if (mapList((int)(g_player.posX - g_player.newDirXY[0] * g_player.moveSpeed), (int)g_player.posY) == '0')
        g_player.posX -= g_player.newDirXY[0] * g_player.moveSpeed;
    //if (g_worldMap[(int)g_player.posX][(int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)] == 0)
    if (mapList((int)g_player.posX, (int)(g_player.posY - g_player.newDirXY[1] * g_player.moveSpeed)) == '0')
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
    
  int   ft_stop(int key, void *param)
  {
    (void)param;
    if (key == 0x35 || key == 0x00)
    {
        mlx_destroy_window(g_screenData.mlx_ptr, g_screenData.mlx_win);
        mlx_destroy_image(g_screenData.mlx_ptr, g_clsImg.mlx_img);
        if (g_screenData.mlx_img_buffer)
            mlx_destroy_image(g_screenData.mlx_ptr, g_screenData.mlx_img_buffer);
        if (g_blueMetalImg.mlx_img)
            mlx_destroy_image(g_screenData.mlx_ptr, g_blueMetalImg.mlx_img);
        if (g_normiImg.mlx_img)
            mlx_destroy_image(g_screenData.mlx_ptr, g_normiImg.mlx_img);
        if (g_config.Map)
            freeList(&g_config.Map);
        free(g_blueMetalImg.texPath);
        free(g_yellowMetalImg.texPath);
        free(g_greenMetalImg.texPath);
        free(g_pinkMetalImg.texPath);
        free(g_config.spriteTexPath);
        free(g_player.newDirXY);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

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
    if (key == 0x2E)
    {
        if (g_keyData.m == 2)
            g_keyData.m = 0;
        else
        
            g_keyData.m += 1;
    }
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

/*
** Initial variable values.
*/
void initialize(void)
{
    //CGDirectDisplayID disID; BONUS
    g_player.posX = 22;
    g_player.posY = 12;
    g_player.dirX = -1;
    g_player.dirY = 0;
    g_player.planeX = 0;
    g_player.planeY = 0.66;
    g_player.rotSpeed = 0.1;
    g_player.moveSpeed = 0.25;
    g_frameData.time = 0;
    g_frameData.oldTime = 0;
    g_frameData.ofloorColor = 0x00669999;
    g_frameData.oceilingColor = 0x0066004b;
    //disID = CGMainDisplayID(); BONUS
    //g_config.screenW = CGDisplayPixelsWide(disID); BONUS
    //((g_config.screenH = CGDisplayPixelsHigh(disID); BONUS
    g_config.screenW = 2560;
    g_config.screenH = 1440;
    g_config.texW = 64;
    g_config.texH = 64;
    g_config.spriteW = 64;
    g_config.spriteH = 64;
    g_config.wallMultiplier = 1;
    g_config.uDiv = 1;
    g_config.vDiv = 1;
    g_config.vMove = (double)g_config.spriteH;
    printf("Maximum Resolution: %d, %d\n", g_config.screenW, g_config.screenH);
}

void    initializeKeys(void)
{
    g_keyData.w = 0;
    g_keyData.a = 0;
    g_keyData.s = 0;
    g_keyData.d = 0;
    g_keyData.r = 0;
    g_keyData.l = 0;
    g_keyData.m = 1;
}
//move when global variable definitions removed from cub3d.h (g_worldMap y g_sprite)
/*
** Checks first two integers after the 'R' or 'r' specifier in the line passed
** as an argument. If they are valid (between 240 pixels and specified maximum
** display resolution), they will be copied to display file. Otherwise, the
** default display resolution will be used. If either or both specified
** resolutions are invalid, an INVALID RESOLUTION (-1) error will be thrown.
** If the provided line pointer is NULL, the function will terminate and
** default resolution values will be used.
**
** Integers must be separated from each other by any non-numeric character.
*/
int     getRes(const char *line)
{
    const char  *charPtr;
    int         resCount;
    int         res;

    charPtr = line;
    resCount = 0;
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != 'R' && *charPtr != 'r') && *charPtr != '/' && (*charPtr != '*' && *(charPtr + 1) != '*'))
        charPtr++;
    while (*charPtr && *charPtr != '/' && *charPtr != 'F' && *charPtr != 'f' && \
    *charPtr != 'C' && *charPtr != 'c' && resCount < 3 && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr > 47 && *charPtr < 58)
        {
            resCount++;
            if (resCount == 1 && (res = ft_atoi(charPtr)) > 239 && res < g_config.screenW)
                g_config.screenW = res;
            else if (resCount == 2 && (res = ft_atoi(charPtr)) > 239 && res < g_config.screenH)
                g_config.screenH = res;
            else
                break ;
            while (*charPtr > 47 && *charPtr < 58)
                charPtr++;
        }
        else
            charPtr++;
    }
    if (*charPtr == 'F' || *charPtr == 'f' || *charPtr == 'C' || *charPtr == 'c')
        ft_putstr(badResSyn, ft_strlen(badResSyn));
    if (resCount == 2)
        printf("\nResolution Retrieved: %d, %d\n", g_config.screenW, g_config.screenH);
    return (resCount == 2 ? 1 : -1);
}

int     getNO(const char *line)
{
    const char  *charPtr;
    char        *path;
    int         i;

    charPtr = line;
    
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr == 'N' || *charPtr == 'n')
        {
            if (*(charPtr + 1) == 'O' || *(charPtr + 1) == 'o')
            {
                charPtr += 2;
                while (*charPtr && *charPtr != '/')
                    charPtr++;
                if (*charPtr == '/' && *(charPtr - 1) == '.')
                    charPtr--;
                if (*charPtr)
                {
                    i = 0;
                    while (charPtr[i] && ft_isprint(charPtr[i]))
                        i++;
                    path = ft_calloc(i + 1, 1);
                    ft_memcpy(path, charPtr, i + 1);
                    g_blueMetalImg.texPath = strdup(path);
                    printf("Quantum Path Info N Wall: \n%s\n", path);
                    return (1);
                }
            }
        }
        charPtr++;
    }
    return (-1);
}

int     getSO(const char *line)
{
    const char  *charPtr;
    char        *path;
    int         i;

    charPtr = line;
    
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr == 'S' || *charPtr == 's')
        {
            if (*(charPtr + 1) == 'O' || *(charPtr + 1) == 'o')
            {
                charPtr += 2;
                while (*charPtr && *charPtr != '/')
                    charPtr++;
                if (*charPtr == '/' && *(charPtr - 1) == '.')
                    charPtr--;
                if (*charPtr)
                {
                    i = 0;
                    while (charPtr[i] && ft_isprint(charPtr[i]))
                        i++;
                    path = ft_calloc(i + 1, 1);
                    ft_memcpy(path, charPtr, i + 1);
                    g_yellowMetalImg.texPath = strdup(path);
                    printf("Quantum Path Info S Wall: \n%s\n", path);
                    return (1);
                }
            }
        }
        charPtr++;
    }
    return (-1);
}

int     getWE(const char *line)
{
    const char  *charPtr;
    char        *path;
    int         i;

    charPtr = line;
    
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr == 'W' || *charPtr == 'w')
        {
            if (*(charPtr + 1) == 'E' || *(charPtr + 1) == 'e')
            {
                charPtr += 2;
                while (*charPtr && *charPtr != '/')
                    charPtr++;
                if (*charPtr == '/' && *(charPtr - 1) == '.')
                    charPtr--;
                if (*charPtr)
                {
                    i = 0;
                    while (charPtr[i] && ft_isprint(charPtr[i]))
                        i++;
                    path = ft_calloc(i + 1, 1);
                    ft_memcpy(path, charPtr, i + 1);
                    g_greenMetalImg.texPath = strdup(path);
                    printf("Quantum Path Info W Wall: \n%s\n", path);
                    return (1);
                }
            }
        }
        charPtr++;
    }
    return (-1);
}

int     getEA(const char *line)
{
    const char  *charPtr;
    char        *path;
    int         i;

    charPtr = line;
    
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr == 'E' || *charPtr == 'e')
        {
            if (*(charPtr + 1) == 'A' || *(charPtr + 1) == 'a')
            {
                charPtr += 2;
                while (*charPtr && *charPtr != '/')
                    charPtr++;
                if (*charPtr == '/' && *(charPtr - 1) == '.')
                    charPtr--;
                if (*charPtr)
                {
                    i = 0;
                    while (charPtr[i] && ft_isprint(charPtr[i]))
                        i++;
                    path = ft_calloc(i + 1, 1);
                    ft_memcpy(path, charPtr, i + 1);
                    g_pinkMetalImg.texPath = strdup(path);
                    printf("Quantum Path Info E Wall: \n%s\n", path);
                    return (1);
                }
            }
        }
        charPtr++;
    }
    return (-1);
}

int     getSprite(const char *line)
{
    const char  *charPtr;
    char        *path;
    int         i;

    charPtr = line;
    
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if ((*charPtr == 'S' || *charPtr == 's') && *(charPtr + 1) != 'O' && *(charPtr + 1) != 'o')
        {
            charPtr++;
            while (*charPtr && *charPtr != '/')
                charPtr++;
            if (*charPtr == '/' && *(charPtr - 1) == '.')
                charPtr--;
            if (*charPtr)
            {
                i = 0;
                while (charPtr[i] && ft_isprint(charPtr[i]))
                    i++;
                path = ft_calloc(i + 1, 1);
                ft_memcpy(path, charPtr, i + 1);
                g_config.spriteTexPath = strdup(path);
                printf("Quantum Path Info Sprite: \n%s\n", path);
                return (1);
            }
        }
        charPtr++;
    }
    return (-1);
}
//Cómo escribir esto con *line? A estas alturas y todavía no domino sintaxis de punteros :_(
//meter que todos los muros deban tener el mismo texsize
int     getTexRes(int *texRes, char *xmpPath)
{
    int     fd;
    char    *subline;
    char    **line;
    int     i;
    int     resCount;

    line = &subline;
    fd = open(xmpPath, O_RDONLY, S_IRUSR);
    resCount = 0;
    i = 0;
    if (fd >= 0 && fd < 3)
        ft_putstr(weirdFD, ft_strlen(weirdFD));
    else if (fd >= 3)
    {
        while (resCount < 1 && (ft_get_next_line(fd, line)) > 0)
        {
            i = 0;
            while (subline[i] != '"' && subline[i])
                i++;
            while (resCount < 2 && subline[i])
            {
                while (!(ft_isdigit(subline[i]) && subline[i]))
                    i++;
                if (resCount == 0)
                    texRes[0] = (ft_atoi(&subline[i]));
                else
                    texRes[1] = (ft_atoi(&subline[i]));
                while (ft_isdigit(subline[i]) && subline[i])
                    i++;
                resCount++;
            }
            free(*line);
            *line = NULL;
        }
    }
    //printf("\nTex Sizes: %d, %d", texRes[0], texRes[1]);
    close(fd);
    return (resCount == 2 ? 1 : -1);
}
/*
** Compares initially retrieved wall texture resolution with all
** subsequent wall texture resolutions. If any of them are
** different, program aborts.
*/
//Habrá que hacerlo más pequeño o partirlo:p
int     compTexRes(void)
{
    int     fd[3];
    int     results[6];
    char    *subline;
    char    **line;
    int     i;
    int     j;
    int     resCount;

    line = &subline;
    fd[0] = open(g_yellowMetalImg.texPath, O_RDONLY, S_IRUSR);
    fd[1] = open(g_greenMetalImg.texPath, O_RDONLY, S_IRUSR);
    fd[2] = open(g_pinkMetalImg.texPath, O_RDONLY, S_IRUSR);
    i = 0;
    j = 0;
    while (j < 3 && fd[j] >= 3 && (ft_get_next_line(fd[j], line)) > 0)
    {
        i = 0;
        while (subline[i] != '"' && subline[i])
            i++;
        resCount = 0;
        while (resCount < 2 && subline[i])
        {
            while (!(ft_isdigit(subline[i]) && subline[i]))
                i++;
            results[j * 2 + resCount]= (ft_atoi(&subline[i]));
            if (resCount)
                j++;
            else
                while (ft_isdigit(subline[i]) && subline[i])
                    i++;
            resCount++;
        }
        free(*line);
        *line = NULL;
    }
    j = 0;
    while (j < 3)
        close(fd[j++]);
    i = 0;
    while (i < 6)
        {
            if (results[i] != g_config.texW || results[i + 1] != g_config.texH)
            {
                ft_putstr(wallTexSizeDif, ft_strlen(wallTexSizeDif));
                ft_stop(0x35, (void*)0);
            }
            i += 2;
        }
    //printf("\nALL CLEAR!\n");
    return (1);
}

unsigned int     create_trgb(int t, int r, int g, int b)
{
    return(t << 24 | r << 16 | g << 8 | b);
}

int     getFColor(const char *line)
{
    const char  *charPtr;
    int         resCount;
    int         res[3];
    unsigned int    xcolor;

    charPtr = line;
    resCount = 0;
    if (!line)
        return (-2);
    while ((*charPtr && (*charPtr != 'F' && *charPtr != 'f')) && *charPtr != '/' && (*charPtr != '*' && *(charPtr + 1) != '*'))
        charPtr++;
    while (*charPtr && *charPtr != '/' && resCount < 3 && *charPtr != 'R' && \
    *charPtr != 'r' && *charPtr != 'C' && *charPtr != 'c' && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr > 47 && *charPtr < 58)
        {
            res[resCount] = ft_atoi(charPtr);
            resCount++;
            while (*charPtr > 47 && *charPtr < 58)
                charPtr++;
        }
        else
            charPtr++;
    }
    if (*charPtr == 'R' || *charPtr == 'r' || *charPtr == 'C' || *charPtr == 'c')
        ft_putstr(badFColorSyn, ft_strlen(badFColorSyn));
    if (resCount == 3)
    {
        xcolor = create_trgb(0, res[0], res[1], res[2]);
        printf("\nColor: %d, %d, %d\n", res[0], res[1], res[2]);
        printf("\nColor Convertido: %x", g_frameData.ofloorColor);
        g_frameData.ofloorColor = xcolor;
        printf("\nColor Convertido: %x", g_frameData.ofloorColor);
    }
    return (resCount == 3 ? 1 : -1);
}

int     getCColor(const char *line)
{
    const char  *charPtr;
    int         resCount;
    int         res[3];
    unsigned int    xcolor;

    charPtr = line;
    resCount = 0;
    if (!line)
        return (-2);
    while ((*charPtr && (*charPtr != 'C' && *charPtr != 'c')) && *charPtr != '/' && (*charPtr != '*' && *(charPtr + 1) != '*'))
        charPtr++;
    while (*charPtr && *charPtr != '/' && resCount < 3 && *charPtr != 'R' && \
    *charPtr != 'r' && *charPtr != 'F' && *charPtr != 'f' && (*charPtr != '*' && *(charPtr + 1) != '*'))
    {
        if (*charPtr > 47 && *charPtr < 58)
        {
            res[resCount] = ft_atoi(charPtr);
            resCount++;
            while (*charPtr > 47 && *charPtr < 58)
                charPtr++;
        }
        else
            charPtr++;
    }
    if (*charPtr == 'R' || *charPtr == 'r' || *charPtr == 'F' || *charPtr == 'f')
        ft_putstr(badFColorSyn, ft_strlen(badFColorSyn));
    if (resCount == 3)
    {
        xcolor = create_trgb(0, res[0], res[1], res[2]);
        printf("\nColor: %d, %d, %d\n", res[0], res[1], res[2]);
        printf("\nColor Convertido: %x", g_frameData.oceilingColor);
        g_frameData.oceilingColor = xcolor;
        printf("\nColor Convertido: %x", g_frameData.oceilingColor);
    }
    return (resCount == 3 ? 1 : -1);
}

//NUEVO PLAN Primero copia a array bidimensional, después analiza
// Cada eje de letras contiguas debe empezar y terminar en 1... así
// de fácil... y difícil

int     getMapArray(int fd)
{
    int     i;
    int     y;
    char    stayOut;
    char    *mapchrs;
    char    *line;
    t_list  *listPtr;
    char    *tmp;
    t_list  *currentLine = NULL;

    y = 0;
    mapchrs = " 012NnSsWwSs";
    stayOut = 0;
    while (!stayOut)
    {
        if (!(ft_get_next_line(fd, &line))) // me chiva la última línea... bieeen.
            stayOut = 1;
        i = 0;
        if (!y) //primera línea de todas solo puede contener _ y 1.
        {
            while (line[i] == '1' || line[i] == ' ')
                i++;
            if (line[i])
                return (-1);
            else
            {
                tmp = ft_strdup(line);
                listPtr = ft_lstnew((char *)tmp);
                g_config.Map = listPtr;
            }
        }
        else 
        {  
            while ((line[i] && ft_strchr(mapchrs, line[i]))) //al principio de la cadena, si mapchrs, salta espacios hasta primer char no espacio
                i++;
            if (line[i]) //líneas siguientes solo pueden contener cualquier char de mapchrs
            {
                freeList(&g_config.Map); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                return (-1);
            }
            else
            {
                tmp = ft_strdup(line);
                listPtr = ft_lstnew((char *)tmp);
                ft_lstadd_back(&g_config.Map, listPtr);
            }
        }
        if (y == 3)
            currentLine = g_config.Map; //siempre a 3 líneas del final
        else if (y > 3)
            currentLine = currentLine->next;
        y++;
    }
    currentLine = g_config.Map;
    while (currentLine)
    {
        printf("\n # %s", currentLine->content);
        currentLine = currentLine->next;
    }
    //freeList(&g_config.Map);
    if (y < 3) //mapa debe tener al menos tres líneas para ser valido
        return (-1);
    return (1);
}

/*
** The result array saves results of each map parsing function. 1 simply
** means successful; negative numbers correspond to error messages.
*/
void    getMap(const char *ptr)
{
    int     fd;
    int     fdtest;
    char    *subline;
    char    **line;
    int     result[9];
    int     i;

    line = &subline;
    fd = open(ptr, O_RDONLY, S_IRUSR);
    fdtest = open("testmap.cub", O_RDONLY, S_IRUSR);
    i = 0;
    while (i < 8)
        result[i++] = 0;
    result[8] = 1;
    if (fd < 0)
        ft_putstr(cubFileNotFound, ft_strlen(cubFileNotFound));
    else if (fd >= 0 && fd < 3)
        ft_putstr(weirdFD, ft_strlen(weirdFD));
    else
    {
        while ((ft_get_next_line(fd, line)) > 0) //mi get_next envía algo malloceado a EOF?
        {
            if (result[0] < 1)
                result[0] = getRes(*line);
            if (result[1] < 1)
                result[1] = getNO(*line);
            if (result[2] < 1)
                result[2] = getSO(*line);
            if (result[3] < 1)
                result[3] = getWE(*line);
            if (result[4] < 1)
                result[4] = getEA(*line);
            if (result[5] < 1)
                result[5] = getSprite(*line);
            if (result[6] < 1)
                result[6] = getFColor(*line);
            if (result[7] < 1)
                result[7] = getCColor(*line);
            free (*line);
            *line = NULL;
        }
        
        if (result[0] == -1)
            ft_putstr(getResFail, ft_strlen(getResFail));
        if (result[1] == -1)
            ft_putstr(getNOFail, ft_strlen(getNOFail));
        if (result[2] == -1)
            ft_putstr(getSOFail, ft_strlen(getSOFail));
        if (result[3] == -1)
            ft_putstr(getWEFail, ft_strlen(getWEFail));
        if (result[4] == -1)
            ft_putstr(getEAFail, ft_strlen(getEAFail));
        if (result[5] == -1)
            ft_putstr(getSprFail, ft_strlen(getSprFail));
        if (result[6] == -1)
            ft_putstr(FColorInvalid, ft_strlen(FColorInvalid));
        if (result[7] == -1)
            ft_putstr(CColorInvalid, ft_strlen(CColorInvalid));
        while (--i && result[8])
            if (result[i] != 1)
                result[8] = 0; //If any retrieval fails
        //if (result[8])
            //result[8] = getMapArray(fd); //copy map Array - first step
        getMapArray(fdtest);


        printf("\nResolution: %d, %d", g_config.screenW, g_config.screenH);
        printf("\nNO Result: %d", result[1]);
        char c = mapList(1, 1);
       printf("\nHABEERRRRR %c", c);
    }
                  //  printf("%d\n%d\n", g_config.screenW, g_config.screenH);
    //printf("FD: %d", fd);
    if (close(fd) < 0)
        ft_putstr(couldNotClose, ft_strlen(couldNotClose));
    close(fdtest);
    return ;
}

void makeClsImg(void)
{
    g_clsImg.mlx_img = mlx_new_image(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH);
}

void    makeTexImg(void)
{
    int *wallSize;
    int *sprSize;
    
    int normiWidth;
    int normiHeight;

    if (!(wallSize = malloc(2 * sizeof(int))) | (!(sprSize = malloc(2 * sizeof(int)))))
        ft_putstr(mallocFail, ft_strlen(mallocFail));
    else
    {   
        normiWidth = 128;
        normiHeight = 164;
        g_blueMetalImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, g_blueMetalImg.texPath, &g_config.texW, &g_config.texH);
        g_yellowMetalImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, g_yellowMetalImg.texPath, &g_config.texW, &g_config.texH);
        g_greenMetalImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, g_greenMetalImg.texPath, &g_config.texW, &g_config.texH);
        g_pinkMetalImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, g_pinkMetalImg.texPath, &g_config.texW, &g_config.texH);
        g_normiImg.mlx_img = mlx_xpm_file_to_image(g_screenData.mlx_ptr, g_config.spriteTexPath, &g_config.spriteW, &g_config.spriteH);
        if (!g_blueMetalImg.mlx_img || !g_yellowMetalImg.mlx_img || !g_greenMetalImg.mlx_img || !g_pinkMetalImg.mlx_img || !g_normiImg.mlx_img)
        {
            if (!g_blueMetalImg.mlx_img)
                ft_putstr(pathNOFail, ft_strlen(pathNOFail));
            if (!g_yellowMetalImg.mlx_img)
                ft_putstr(pathSOFail, ft_strlen(pathSOFail));
            if (!g_greenMetalImg.mlx_img)
                ft_putstr(pathWEFail, ft_strlen(pathWEFail));
            if (!g_pinkMetalImg.mlx_img)
                ft_putstr(pathEAFail, ft_strlen(pathEAFail));
            if (!g_normiImg.mlx_img)
                ft_putstr(pathSprFail, ft_strlen(pathSprFail));
            exit(EXIT_FAILURE);
        }
        if ((getTexRes(wallSize, g_blueMetalImg.texPath)) < 0)
            ft_putstr(wallTexSizeFail, ft_strlen(wallTexSizeFail));
        else
        {
            g_config.texW = wallSize[0];
            g_config.texH = wallSize[1];
        }
        compTexRes();
        if ((getTexRes(sprSize, g_config.spriteTexPath)) < 0)
            ft_putstr(sprTexSizeFail, ft_strlen(sprTexSizeFail));
        else
        {
            g_config.spriteW = sprSize[0];
            g_config.spriteH = sprSize[1];
        }
        
        printf("\nRetrieved Tex Sizes: %d, %d\n", g_config.spriteW, g_config.spriteH);
        
    }
    if (wallSize)
        free(wallSize);
    if (sprSize)
        free(sprSize);
}

  int   main(int argc, char **argv)
  {
      (void)argc;
      initialize();
      initializeKeys();
      getMap(argv[1]);
      //printf("\n%s", argv[1]);
      g_player.newDirXY = malloc(2 * sizeof(double));
//Create screen
   //if (getMap fails, do not start)
   
   
   
    if (!(g_screenData.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(g_screenData.mlx_win = mlx_new_window(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH, "Norminator 3D")))
        return (EXIT_FAILURE);
    makeClsImg();
    makeTexImg();
    mlx_do_key_autorepeatoff(g_screenData.mlx_ptr);
    mlx_hook(g_screenData.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screenData.mlx_win, 2, 0, ft_keyPress, (void*)0);
    mlx_hook(g_screenData.mlx_win, 3, 0, ft_keyRelease, (void *)0);
    mlx_loop_hook(g_screenData.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screenData.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  