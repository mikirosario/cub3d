/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/07 20:39:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

error_t g_iamerror = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,{0,0,0},0,0,{0,0,0},0,0,0,0,0,0,NULL};

/*
** This function is a generic, run-of-the-mill "free this memory and set the
** pointer to NULL" function that should really be in my libft by now. :p
*/

void    del(void *freeThis)
{
    free(freeThis);
    freeThis = NULL;
}

/*
** This is a little function I've found very useful. It finds the next number
** from thhe position in a string passed as an argument.

** If your pointer is pointing to a number in a string, it will go through the
** number until the end and then go through any non-numerical characters after
** the number until it finds the next number or a NULL. If you're pointing to a
** part of the string that isn't a number, it will of course ignore the first
** while and directly go to the second one to find the next number.

** If it finds another number, it returns a pointer to it, otherwise it returns
** a NULL pointer. Great line saver. ^_^
**
** This is going in my libft.
*/

char	*getnextnum(char *num)
{
	while (*num && ft_isdigit(*num))
		num++;
	while (*num && !(ft_isdigit(*num)))
		num++;
	return (*num ? num : NULL);
}

/*
** These functions will respectively create and put the g_clsImg.mlx_img image
** to window. It was originally meant to be clear screen function, until I
** realized I don't really need a clear screen function. I might find another
** use for it, though, so I'm leaving it here. ;)
**
** I might repurpose it for overlays or something in the bonus. :)
*/

void makeClsImg(void)
{
    g_clsImg.mlx_img = mlx_new_image(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH);
}

void    cls()
{
   mlx_put_image_to_window(g_screenData.mlx_ptr, g_screenData.mlx_win, g_clsImg.mlx_img, 0, 0);
}

void    ft_sortSprites(int *spriteOrder)
{
    double  distance[g_config.spriteNum];
    int     tmp;
    int     i;

//first get relative player-sprite distances == playerpos - spritepos. magia matemática.
i = 0;
while (i < g_config.spriteNum)
{
    //g_frameData.spriteOrder[i] = i;
    spriteOrder[i] = i;
    //distance[i] = ((g_player.posX - g_sprite[i].posX) * (g_player.posX - g_sprite[i].posX) + (g_player.posY - g_sprite[i].posY) * (g_player.posY - g_sprite[i].posY));
    distance[i] = ((g_player.posX - (spriteiter(i))->posX) * (g_player.posX - (spriteiter(i))->posX) + (g_player.posY - (spriteiter(i))->posY) * (g_player.posY - (spriteiter(i))->posY));
    i++;
}
i = -1;
while (g_config.spriteNum > 1 && ++i < g_config.spriteNum - 1)
{
    if (distance[i] < distance[i + 1])
    {
        tmp = distance[i];
        distance[i] = distance[i + 1];
        distance[i + 1] = tmp;
        //tmp = g_frameData.spriteOrder[i];
        tmp = spriteOrder[i];
        //g_frameData.spriteOrder[i] = g_frameData.spriteOrder[i + 1];
        spriteOrder[i] = spriteOrder[i + 1];
        //g_frameData.spriteOrder[i + 1] = tmp;
        spriteOrder[i + 1] = tmp;
        i = -1;
    }
}

}
//Mac FREEME FUNCTION
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
            mlx_destroy_image(g_screenData.mlx_ptr, g_normiImg.mlx_img); //Nota: Esta función libera la memoria ocupada por la imágen; no intentar liberarla desde freesprtlist o será doble-free. ;)
        if (g_config.Map)
            freelist(&g_config.Map);
        if (g_config.spriteList)
            freesprtlist(&g_config.spriteList);
        free(g_blueMetalImg.texPath);
        free(g_yellowMetalImg.texPath);
        free(g_greenMetalImg.texPath);
        free(g_pinkMetalImg.texPath);
        free(g_normiImg.texPath);
        //free(g_player.newDirXY);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

//Linux
/*int   ft_stop(int key, void *param)
  {
    (void)param;
    if (key == 0xff1b || key == 0)
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
  }*/

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
        g_blueMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_blueMetalImg.mlx_img, &g_blueMetalImg.bpp, &g_blueMetalImg.size_line, &g_blueMetalImg.endian);
        g_yellowMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_yellowMetalImg.mlx_img, &g_yellowMetalImg.bpp, &g_yellowMetalImg.size_line, &g_yellowMetalImg.endian);
        g_greenMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_greenMetalImg.mlx_img, &g_greenMetalImg.bpp, &g_greenMetalImg.size_line, &g_greenMetalImg.endian);
        g_pinkMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_pinkMetalImg.mlx_img, &g_pinkMetalImg.bpp, &g_pinkMetalImg.size_line, &g_pinkMetalImg.endian);

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
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
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
        ft_rotate_2D(g_player.dirX, g_player.dirY, 90, 6, (double *)(&g_player.newDirXY));
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
        ft_rotate_2D(g_player.dirX, g_player.dirY, -3, 6, (double *)(&g_player.newDirXY));
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, -3, 6, (double *)(&g_player.newDirXY));
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
        ft_rotate_2D(g_player.dirX, g_player.dirY, 3, 6, (double *)(&g_player.newDirXY));
        g_player.dirX = g_player.newDirXY[0];
        g_player.dirY = g_player.newDirXY[1];
        ft_rotate_2D(g_player.planeX, g_player.planeY, 3, 6, (double *)(&g_player.newDirXY));
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

//Mac
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
//Mac
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

//Linux
/*int ft_keyPress(int key, void *param)
{
    (void)param;
    if (key == 0xff1b)
        ft_stop(key, (void *)0);
    //move forwards if no wall in front
    if (key == 0x77)
        g_keyData.w = 1;
    //move backwards if no wall in front
    if (key == 0x73)
        g_keyData.s = 1;
    //strafe right if no wall to right
    if (key == 0x64)
        g_keyData.d = 1;
    //strafe left if no wall to left
    if (key == 0x61)
        g_keyData.a = 1;
    //clockwise rotation
    if (key == 0xff53)
        g_keyData.r = 1;
    //anticlockwise rotation
    if (key == 0xff51)
        g_keyData.l = 1;
    if (key == 0x6d)
    {
        if (g_keyData.m == 2)
            g_keyData.m = 0;
        else
        
            g_keyData.m += 1;
    }
    return (0);
}
//Linux
int ft_keyRelease(int key, void *param)
{
    (void)param;
    //move forwards if no wall in front
    if (key == 0x77)
        g_keyData.w = 0;
    //move backwards if no wall in front
    if (key == 0x73)
        g_keyData.s = 0;
    //strafe right if no wall to right
    if (key == 0x64)
        g_keyData.d = 0;
    //strafe left if no wall to left
    if (key == 0x61)
        g_keyData.a = 0;
    //clockwise rotation
    if (key == 0xff53)
        g_keyData.r = 0;
    //anticlockwise rotation
    if (key == 0xff51)
        g_keyData.l = 0;
    return (0);
}*/



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

//meter que todos los muros deban tener el mismo texsize


//Habrá que hacerlo más pequeño o partirlo:p


unsigned int     create_trgb(int t, int r, int g, int b)
{
    return(t << 24 | r << 16 | g << 8 | b);
}



//Mac
int   main(int argc, char **argv)
  {
      int 	success;

	  (void)argc;
      initialize();
	  success = cubhandler(argv[1]);
      //printf("\n%s", argv[1]);

//Create screen
   //if (getMap fails, do not start)
   
   
   if (success)
   {
	if (!(g_screenData.mlx_ptr = mlx_init()))
		success = 0;
	if (!(g_screenData.mlx_win = mlx_new_window(g_screenData.mlx_ptr, g_config.screenW, g_config.screenH, "Norminator 3D")))
		success = 0;
   }
   if (success)
   {
	makeClsImg();
	success = maketeximg();
   }
   	printnotifications();
	printerrors();
	if (!success)
	  	return (EXIT_FAILURE);
	printf("\nSizeOf error_s: %zu\n", sizeof(g_iamerror));
	printf("\nValor: %d\n", g_iamerror.getresfail);
    mlx_do_key_autorepeatoff(g_screenData.mlx_ptr);
    mlx_hook(g_screenData.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screenData.mlx_win, 2, 0, ft_keyPress, (void*)0);
    mlx_hook(g_screenData.mlx_win, 3, 0, ft_keyRelease, (void *)0);
    mlx_loop_hook(g_screenData.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screenData.mlx_ptr);
    return(EXIT_SUCCESS);
  }


//Linux
/*  int   main(int argc, char **argv)
  {
      int 	r;

	  (void)argc;
      initialize();
      initializeKeys();
	  r = cubhandler(argv[1]);
	  printnotifications();
	  printerrors();
	  if (!r)
	  	return (EXIT_FAILURE);
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
	printf("\nSizeOf error_s: %zu\n", sizeof(g_iamerror));
	printf("\nValor: %d\n", g_iamerror.getresfail);
    mlx_do_key_autorepeatoff(g_screenData.mlx_ptr);
    mlx_hook(g_screenData.mlx_win, 17, 1L << 17, ft_stop, (void*)0);
    mlx_hook(g_screenData.mlx_win, 2, 1L << 0, ft_keyPress, (void*)0);
    mlx_hook(g_screenData.mlx_win, 3, 1L << 1, ft_keyRelease, (void *)0);
    mlx_loop_hook(g_screenData.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screenData.mlx_ptr);
    return(EXIT_SUCCESS);
  }*/

  