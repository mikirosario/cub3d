/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:24:11 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cub3d.h"

  //pixel_put cls
/*  void cls()
{
    int x;
    int y;

    x = 0;
        while (x <= g_config.screenw) //clearscreen
        {
            y = g_config.screenh;
            while (y)
            {
                mlx_pixel_put(g_screendata.mlx_ptr, g_screendata.mlx_win, x, y--, 0x0);
            }
            x++;
        }
    mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, g_config.screenw / 2, 0, 0x0000ff00, "TEST");
}*/

t_spritedata	*ft_sprtlstnew(void const *content)
{
	t_spritedata *tmp;

	tmp = malloc(sizeof(t_spritedata));
	if (tmp)
	{
		tmp->posx = 0;
        tmp->posy = 0;
        if (content)
            tmp->texture = (void *)content;
        else
            tmp->texture = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

t_spritedata	*ft_sprtlstlast(t_spritedata *lst)
{
	t_spritedata	*tmp;

	tmp = lst;
	if (!lst)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_sprtlstadd_back(t_spritedata **alst, t_spritedata *new)
{
	if (!new)
		return ;
	if (alst && *alst)
	{
		new->next = (ft_sprtlstlast(*alst))->next;
		(ft_sprtlstlast(*alst))->next = new;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}

void    del(void *freeThis)
{
    free(freeThis);
    freeThis = NULL;
}

void    freeSprtList(t_spritedata **alst)
{
    t_spritedata *tmp;

    while (*alst)
    {
        tmp = (&(**alst))->next;
        free(*alst);
        *alst = tmp;
    }
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

t_spritedata    *spriteIter(int listMember)
{
    t_spritedata    *ptr;
    int             i;

    i = 0;
    ptr = g_config.spritelist;
    while (i++ < listMember)
        ptr = ptr->next;
    return (ptr);
}

char    mapList(int x, int y)
{
    t_list  *ptr;
    int     i;
(void)y;
    i = 0;
    ptr = g_config.maplist;
    while (i++ < y)
        ptr = ptr->next;
    return (*((char *)(ptr->content + x)));
}
//Como mapList, pero devuelve dirección de char
char    *mapListDir(int x, int y)
{
    t_list  *ptr;
    int     i;
(void)y;
    i = 0;
    ptr = g_config.maplist;
    while (ptr && i++ < y)
        ptr = ptr->next;
    if (!ptr)
        return (0);
    return (((char *)(ptr->content + x)));
}

//Como mapList, pero devuelve dirección del miembro asociado a y (línea)
t_list  *mapListMem(int y)
{
    t_list  *ptr;
    int     i;

    i = 0;
    ptr = g_config.maplist;
    while (ptr && i++ < y)
        ptr = ptr->next;
    if (!ptr)
        return (0);
    return (ptr);
}

//image dump cls
void    cls()
{
   mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, g_clsimg.mlx_img, 0, 0);
}

void    ft_sortSprites(int *spriteOrder)
{
    double  distance[g_config.spritenum];
    int     tmp;
    int     i;

//first get relative player-sprite distances == playerpos - spritepos. magia matemática.
i = 0;
while (i < g_config.spritenum)
{
    //g_framedata.spriteOrder[i] = i;
    spriteOrder[i] = i;
    //distance[i] = ((g_player.posx - g_sprite[i].posx) * (g_player.posx - g_sprite[i].posx) + (g_player.posy - g_sprite[i].posy) * (g_player.posy - g_sprite[i].posy));
    distance[i] = ((g_player.posx - (spriteIter(i))->posx) * (g_player.posx - (spriteIter(i))->posx) + (g_player.posy - (spriteIter(i))->posy) * (g_player.posy - (spriteIter(i))->posy));
    i++;
}
i = -1;
while (g_config.spritenum > 1 && ++i < g_config.spritenum - 1)
{
    if (distance[i] < distance[i + 1])
    {
        tmp = distance[i];
        distance[i] = distance[i + 1];
        distance[i + 1] = tmp;
        //tmp = g_framedata.spriteOrder[i];
        tmp = spriteOrder[i];
        //g_framedata.spriteOrder[i] = g_framedata.spriteOrder[i + 1];
        spriteOrder[i] = spriteOrder[i + 1];
        //g_framedata.spriteOrder[i + 1] = tmp;
        spriteOrder[i + 1] = tmp;
        i = -1;
    }
}

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
        if (g_blueMetalImg.mlx_img)
            mlx_destroy_image(g_screendata.mlx_ptr, g_blueMetalImg.mlx_img);
        if (g_sprt2img.mlx_img)
            mlx_destroy_image(g_screendata.mlx_ptr, g_sprt2img.mlx_img); //Nota: Esta función libera la memoria ocupada por la imágen; no intentar liberarla desde freeSprtlist o será doble-free. ;)
        if (g_config.maplist)
            freeList(&g_config.maplist);
        if (g_config.spritelist)
            freeSprtList(&g_config.spritelist);
        free(g_blueMetalImg.texPath);
        free(g_yellowMetalImg.texPath);
        free(g_greenMetalImg.texPath);
        free(g_pinkMetalImg.texPath);
        free(g_config.spritetexpath);
        free(g_player.newdirxy);
        exit(EXIT_SUCCESS);
    }
    return (0);
  }

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

    g_screendata.mlx_img_buffer = mlx_new_image(g_screendata.mlx_ptr, g_config.screenw, g_config.screenh);
    buf = (unsigned int *)mlx_get_data_addr(g_screendata.mlx_img_buffer, &g_screendata.bpp, &g_screendata.size_line, &g_screendata.endian);
    if (stayOut == 'n')
    {
        int tonti = 0;
        g_blueMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_blueMetalImg.mlx_img, &g_blueMetalImg.bpp, &g_blueMetalImg.size_line, &g_blueMetalImg.endian);
        g_yellowMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_yellowMetalImg.mlx_img, &g_yellowMetalImg.bpp, &g_yellowMetalImg.size_line, &g_yellowMetalImg.endian);
        g_greenMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_greenMetalImg.mlx_img, &g_greenMetalImg.bpp, &g_greenMetalImg.size_line, &g_greenMetalImg.endian);
        g_pinkMetalImg.tex_Ptr = (unsigned int *)mlx_get_data_addr(g_pinkMetalImg.mlx_img, &g_pinkMetalImg.bpp, &g_pinkMetalImg.size_line, &g_pinkMetalImg.endian);

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
    cls();
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
            if (mapList(g_raydata.mapx, g_raydata.mapy) == '1')
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
                texPtr = g_blueMetalImg.tex_Ptr;
            else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 2)
                texPtr = g_yellowMetalImg.texPtr;
            else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 3)
                texPtr = g_greenMetalImg.tex_Ptr;
            else
                texPtr = g_pinkMetalImg.tex_Ptr;
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
                    texPtr = g_blueMetalImg.tex_Ptr;
                else if (g_raydata.side == 1 && g_raydata.stepy < 0) //east facing wall
                    texPtr = g_yellowMetalImg.tex_Ptr;
                else if (g_raydata.side == 0 && g_raydata.stepx > 0) //south facing wall
                    texPtr = g_greenMetalImg.tex_Ptr;
                else if (g_raydata.side == 0 && g_raydata.stepx < 0) //north facing wall
                    texPtr = g_pinkMetalImg.tex_Ptr;
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
        spriteX = (spriteIter(spriteOrder[i]))->posx - g_player.posx;
        //spriteY = g_sprite[g_framedata.spriteOrder[i]].posy - g_player.posy;
        //spriteY = g_sprite[spriteOrder[i]].posy - g_player.posy;
        spriteY = (spriteIter(spriteOrder[i]))->posy - g_player.posy;
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
                    g_framedata.xcolor = (spriteIter(spriteOrder[i]))->texture[g_config.spritew * spriteTexY + spriteTexX]; //get current color from the texture
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
    if ((mapList((int)(g_player.posx + g_player.dirx * g_player.movespeed), (int)g_player.posy)) == '0')
        g_player.posx += g_player.dirx * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.diry * g_player.movespeed)] == 0)
    if ((mapList((int)g_player.posx, (int)(g_player.posy + g_player.diry * g_player.movespeed))) == '0')
        g_player.posy += g_player.diry * g_player.movespeed;
    }
      //move backwards if no wall in front
    if (g_keydata.s)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "DOWN"); //CHIVATO
        //if (g_worldMap[(int)(g_player.posx - g_player.dirx * g_player.movespeed)][(int)(g_player.posy)] == 0)
        if ((mapList((int)(g_player.posx - g_player.dirx * g_player.movespeed), (int)(g_player.posy)) == '0'))
            g_player.posx -= g_player.dirx * g_player.movespeed;
        //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.diry * g_player.movespeed)] == 0)
        if ((mapList((int)g_player.posx, (int)(g_player.posy - g_player.diry * g_player.movespeed))) == '0')
            g_player.posy -= g_player.diry * g_player.movespeed;
    }
    //strafe left if no wall to left
    if (g_keydata.a)
    {
        ft_rotate_2D(g_player.dirx, g_player.diry, 90, 6, &g_player.newdirxy);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "RIGHT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posx + g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
    if (mapList((int)(g_player.posx + g_player.newdirxy[0] * g_player.movespeed), (int)g_player.posy) == '0')
        g_player.posx += g_player.newdirxy[0] * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy + g_player.newdirxy[1] * g_player.movespeed)] == 0)
    if (mapList((int)g_player.posx, (int)(g_player.posy + g_player.newdirxy[1] * g_player.movespeed)) == '0')
        g_player.posy += g_player.newdirxy[1] * g_player.movespeed;
    }
    //strafe right if no wall to right
    if (g_keydata.d)
    {
        ft_rotate_2D(g_player.dirx, g_player.diry, 90, 6, &g_player.newdirxy);
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "LEFT"); //CHIVATO
    //if (g_worldMap[(int)(g_player.posx - g_player.newdirxy[0] * g_player.movespeed)][(int)g_player.posy] == 0)
    if (mapList((int)(g_player.posx - g_player.newdirxy[0] * g_player.movespeed), (int)g_player.posy) == '0')
        g_player.posx -= g_player.newdirxy[0] * g_player.movespeed;
    //if (g_worldMap[(int)g_player.posx][(int)(g_player.posy - g_player.newdirxy[1] * g_player.movespeed)] == 0)
    if (mapList((int)g_player.posx, (int)(g_player.posy - g_player.newdirxy[1] * g_player.movespeed)) == '0')
        g_player.posy -= g_player.newdirxy[1] * g_player.movespeed;
    }

        //clockwise rotation
    if (g_keydata.r)
    {
        mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, 0, 0, 0xFF00000, "CLOCKWISE"); //CHIVATO

        //mi método
        ft_rotate_2D(g_player.dirx, g_player.diry, -3, 6, &g_player.newdirxy);
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2D(g_player.planex, g_player.planey, -3, 6, &g_player.newdirxy);
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
        ft_rotate_2D(g_player.dirx, g_player.diry, 3, 6, &g_player.newdirxy);
        g_player.dirx = g_player.newdirxy[0];
        g_player.diry = g_player.newdirxy[1];
        ft_rotate_2D(g_player.planex, g_player.planey, 3, 6, &g_player.newdirxy);
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
    if (key == 0x2E)
    {
        if (g_keydata.m == 2)
            g_keydata.m = 0;
        else
        
            g_keydata.m += 1;
    }
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

/*
** Initial variable values.
*/
void initialize(void)
{
    //CGDirectDisplayID disID; BONUS
    g_player.posx = 0;
    g_player.posy = 0;
    g_player.dirx = 0;
    g_player.diry = 0;
    g_player.planex = 0;
    g_player.planey = 0;
    g_player.rotspeed = 0.1;
    g_player.movespeed = 0.25;
    g_framedata.time = 0;
    g_framedata.oldTime = 0;
    g_framedata.xfloorcolor = 0x00669999;
    g_framedata.xceilingcolor = 0x0066004b;
    //disID = CGMainDisplayID(); BONUS
    //g_config.screenw = CGDisplayPixelsWide(disID); BONUS
    //((g_config.screenh = CGDisplayPixelsHigh(disID); BONUS
    g_config.spritenum = 0;
    g_config.spritelist = NULL;
    g_config.screenw = 2560;
    g_config.screenh = 1440;
    g_config.texw = 64;
    g_config.texh = 64;
    g_config.spritew = 64;
    g_config.spriteh = 64;
    g_config.wallmultiplier = 1;
    g_config.udiv = 1;
    g_config.vdiv = 1;
    g_config.vmove = (double)g_config.spriteh;
    printf("Maximum Resolution: %d, %d\n", g_config.screenw, g_config.screenh);
}

void    initializeKeys(void)
{
    g_keydata.w = 0;
    g_keydata.a = 0;
    g_keydata.s = 0;
    g_keydata.d = 0;
    g_keydata.r = 0;
    g_keydata.l = 0;
    g_keydata.m = 1;
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
int     getres(const char *line)
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
            if (resCount == 1 && (res = ft_atoi(charPtr)) > 239 && res < g_config.screenw)
                g_config.screenw = res;
            else if (resCount == 2 && (res = ft_atoi(charPtr)) > 239 && res < g_config.screenh)
                g_config.screenh = res;
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
        printf("\nResolution Retrieved: %d, %d\n", g_config.screenw, g_config.screenh);
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
                g_config.spritetexpath = strdup(path);
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
            if (results[i] != g_config.texw || results[i + 1] != g_config.texh)
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
        printf("\nColor Convertido: %x", g_framedata.xfloorcolor);
        g_framedata.xfloorcolor = xcolor;
        printf("\nColor Convertido: %x", g_framedata.xfloorcolor);
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
        printf("\nColor Convertido: %x", g_framedata.xceilingcolor);
        g_framedata.xceilingcolor = xcolor;
        printf("\nColor Convertido: %x", g_framedata.xceilingcolor);
    }
    return (resCount == 3 ? 1 : -1);
}

void    spriteCounter(double x, double y, char c)
{
static t_spritedata *lstPtr = NULL;

    g_config.spritenum++;

    if (!g_config.spritelist)
    {
        g_config.spritelist = ft_sprtlstnew((void *)0);
        lstPtr = g_config.spritelist;
    }
    else
    {
        ft_sprtlstadd_back(&g_config.spritelist, (ft_sprtlstnew((void *)0)));
        lstPtr = lstPtr->next;
    }
    lstPtr->posx = x;
    lstPtr->posy = y;
    if (c == '2') //aquí podemos asignar la textura en función del número en el mapa :)
        lstPtr->spritetype = '2';
}

//Floodfill algorithm

int     floodRight(int x, int y)
{
    t_list  *lstPtr;
    char    mapChar;

    while ((mapChar = mapList(++x, y)) != '1' && mapChar != 'T') //izq. a der. transitables contiguas; dado que NULL es a la vez condición de invalidez del mapa, salida del while y cierre de función, se gestiona dentro del while.
        {
            if (mapChar == '0' || mapChar == '2' || mapChar == 'A')
            {
                //mapChar == '2' ? spriteReg : mapChar; //no implementado: si es '2', registra sprite en spritelist con función spriteReg
                if ((lstPtr = mapListMem(y))->next && ((mapListMem(y + 1))->len) >= (size_t)x && (mapChar = mapList(x, y + 1)) && (mapChar == '0' || mapChar == '2')) //mira char de debajo, primero strlen para asegurarnos de que la fila abarca lo suficiente para evitar segfault...
                    (*(mapListDir(x, y + 1)) = 'A'); //marca como transitable provisional (pdte de comprobar sus verticales)
                else if (!lstPtr->next || mapChar == ' ' || !mapChar)
                    return (0);
                if (lstPtr != g_config.maplist && ((mapListMem(y - 1))->len) >= (size_t)x && (mapChar = mapList(x, y -1)) && (mapChar == '0' || mapChar == '2'))//mira char de encima, primero strlen para asegurarnos de que la fila abarca lo suficiente para evitar segfault.
                    (*(mapListDir(x, y - 1)) = 'A'); //marca como transitable (pdte de comprobar sus verticales)
                else if (lstPtr == g_config.maplist || mapChar == ' ' || !mapChar)
                    return (0);
                (*(mapListDir(x, y)) = 'T'); //marca como transitable con todos los ejes comprobados.
            }
            else if (mapChar == ' ' || !mapChar) //nótese que en floodRight, llegar al NULL en un barrido es condición de invalidez del mapa, por lo que su comprobación es a la vez condición de salida del while y de la función.
                return (0);
        }
    return (1);
}

int     floodLeft(int x, int y)
{
    t_list  *lstPtr;
    char    mapChar;

    while (x > -1 && (mapChar = mapList(x, y)) && mapChar != '1' && mapChar != 'T') //der. a izq. transitables contiguas; en floodLeft ni de coña queremos entrar si x == -1, sería segfault al canto, sino que significa que todo el barrido bien hasta el final y es condición de salida.
    {
        if (x > 0 && (mapChar == '0' || mapChar == '2' || mapChar == 'A'))//si encontramos un transitable en cualquier casilla menos la de pos0, bien
        {
            //mapChar == '2' ? spriteReg : mapChar; //no implementado: si es '2', registra sprite en spritelist con función spriteReg
            if ((lstPtr = mapListMem(y))->next && ((mapListMem(y + 1))->len) >= (size_t)x && (mapChar = mapList(x, y + 1)) && (mapChar == '0' || mapChar == '2')) //primero strlen para asegurarnos de que la fila abarca lo suficiente para evitar segfault...
                (*(mapListDir(x, y + 1)) = 'A'); //marca como transitable, pdte de comprobar verticales
            else if (!lstPtr->next || mapChar == ' ' || !mapChar)
                return (0);
            if (lstPtr != g_config.maplist && ((mapListMem(y - 1))->len) >= (size_t)x && (mapChar = mapList(x, y -1)) && (mapChar == '0' || mapChar == '2'))
                (*(mapListDir(x, y - 1)) = 'A'); //marca como transitable, pdte de comprobar verticales
            else if (lstPtr == g_config.maplist || mapChar == ' ' || !mapChar)
                return (0);
            (*(mapListDir(x, y)) = 'T'); //marca como transitable
        }
        else if (mapChar == ' ' || !x)//si encontramos un espacio o hemos encontrado un transitable en pos0, mapa inválido
            return (0);
        x--;
    }
    return (1);
}

void    unfloodMap(void)
{
    t_list  *mapPtr;
    char    mapChar;
    int     i;

    mapPtr = g_config.maplist;
    while (mapPtr)
    {
        i = 0;
        while ((mapChar = *(char *)(mapPtr->content + i)))
        {
            if (mapChar == 'T')
                (*(char *)(mapPtr->content + i)) = '0';
            i++;
        }
        mapPtr = mapPtr->next;
    }
    
    mapPtr = g_config.maplist;
    write(1, "\n", 1);
        while (mapPtr)
    {
        printf("\n # %s", mapPtr->content);
        mapPtr = mapPtr->next;
    }
}

int     floodFill(void)
{
    char    mapChar;
    char    foundA;
    t_list  *listPtr;
    int     c = 0;
    int     x;
    int     y;


    x = g_player.posx;
    y = g_player.posy;
    foundA = '1';
    if ((mapChar = mapList(x, y)) && mapChar != '1' && mapChar != 'T') //transitables contiguas
    {
        if (((mapListMem(y + 1))->len) >= (size_t)x && (mapChar = mapList(x, y + 1)) && (mapChar == '0' || mapChar == '2')) //primero strlen para asegurarnos de que la fila de arriba abarca lo suficiente para evitar segfault...
            (*(mapListDir(x, y + 1)) = 'A'); //marca como transitable provisional, pdte de comprobar verticales
        else if (mapChar == ' ' || !mapChar)
            return (-1);
        if (((mapListMem(y - 1))->len) >= (size_t)x && (mapChar = mapList(x, y -1)) && (mapChar == '0' || mapChar == '2'))
            (*(mapListDir(x, y - 1)) = 'A'); //marca como transitable, pdte de comprobar verticales
        else if (mapChar == ' ' || !mapChar)
            return (-1);
    }
    while (foundA) //mientras siga encontrando As (es decir, transitables provisionales), sigue haciendo barridos de inundación, hasta dejar de encontrarlas.
    {    
        y = 0;
        foundA = 0;
        while (y <= g_config.maph)
        {
            c++;
            x = 0;
            while ((mapChar = mapList(x, y)))
            {
                if (mapChar == 'A')
                {
                    if (!foundA)
                        foundA = '1';
                    if (!(floodRight(x, y)))
                    {
                        printf("\nX = %d Y = %d Barridos = %d", x, y, c);
                        return (-1);
                    }
                    if (!(floodLeft(x, y)))
                        return (-1);
                }
                x++;
            }
            y++;
        }
    }

    /*    if (!(floodRight(x, y)))
            return (-1);
        if (!(floodLeft(x, y)))
            return (-1);
    */
    listPtr = g_config.maplist;
    while (listPtr)
    {
        printf("# %s\n", listPtr->content);
        listPtr = listPtr->next;
    }
    write(1, "\n", 1);

    unfloodMap();
    return (1);
}

//NUEVO PLAN Algoritmo floodfill

//IF NSEW --->> g_player.posx, g_player.posy, if 2x o más NSEW, tira mapa
//IF S ---->>spriteData[index].x, spriteData[index].y (al igual que el mapa, hay que mallocear y crear un array o t_list de sprites, igual un puntero desde un struct global para tener siempre a mano... hay que sabe total de sprites antes de mallocear y pasarlos... igual al encontrar un sprite, guardar su posición y subir un contador, o hacer otra lista enlazada ;))
//a partir de NSEW, analiza mapa para asegurar que zona del jugador está rodeada por 1

int     getMapArray(int fd, char *firstLine)
{
    int     i;
    int     f;
    int     y;
    char    foundPlayer;
    char    stayOut;
    char    *mapchrs;
    char    *line;
    t_list  *listPtr;
    t_spritedata *sprtListPtr;
    char    *tmp;
    t_list  *midLine = NULL;

    y = 0;
    mapchrs = " 012NnSsEeWw";
    stayOut = 0;
    foundPlayer = 0;
    while (!stayOut)
    {
        if (!y)
            line = firstLine;
        else
            if (!(ft_get_next_line(fd, &line))) // me chiva la última línea... bieeen.
                stayOut = 49;
        /*if (!line[0]) //si encuentro línea inválida, mapa acaba
        {
            if (g_config.spritelist)
                freeSprtList(&g_config.spritelist);
            if (g_config.maplist)
                freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
            return (-1);
        }*/
        i = 0;
        while (line[i] && (tmp = ft_strchr(mapchrs, line[i]))) //mientras exista un char y sea un mapchar queremos estar dentro de este while y subir i para recorrer la línea. hay que analizar no-mapchr después en su caso
        {
            if (line[i] == '2')
                spriteCounter((double)i, (double)y, line[i]); //si encuentras un sprite, metelo en spritelist y cuentalo          
            //primera o última línea
            if (!y || stayOut) //si estamos en primera (y == 0) o última (stayOut activado) línea de todas no pueden contener ningún NSEW.
            {
                if (tmp >= (mapchrs + 4)) //si encuentras al personaje en primera o última linea, mapa inválido, error -1
                {
                    if (g_config.spritelist)
                        freeSprtList(&g_config.spritelist);
                    if (g_config.maplist)
                        freeList(&g_config.maplist);
                    return (-1);
                }
            }
            i++;
        }
        if (i > 0 && !line[i]) //si i no es mayor que 0 es línea vacía; si es mayor que cero y hemos llegado a NULL es fin de línea; llegamos a final de línea crea línea nueva de mapList; si es la primera línea a ella, apunta g_config.maplist a ella para indizarla
        {
            tmp = ft_strdup(line);
            listPtr = ft_lstnew((char *)tmp);
            listPtr->len = ft_strlen((const char *)tmp);
            if (!y) //si es primera línea
                g_config.maplist = listPtr;
            else //si es última - todo esto se podría ternarizar.
                ft_lstadd_back(&g_config.maplist, listPtr);
        }
        else //si no se cumple lo anterior, es línea inválida; esta línea no cuenta y la anterior será fin de mapa. Si la última línea del mapa es la última del archivo, 'stayOut' cumplirá esta función.
            break ;
        if (y >= 2) //si tenemos al menos 3 líneas buscaremos al jugador (NSEW) en las líneas de en medio, y comprobaremos que sus cuatro vecinos inmediatos son válidos, y comprobaremos que solo hay un jugador
            {
                f = 0;
                if (y == 2)
                    midLine = g_config.maplist->next; //la primera línea de en medio es la siguiente a la primera de todas, y se analiza al copiar la tercera línea
                else if (y > 2)
                    midLine = midLine->next; //sucesivamente será la siguiente a la anterior, y se analizará tras copiar la línea siguiente a sí misma
                while (*((char *)(midLine->content + f))) //mientras no sea NULL
                {
                    if ((tmp = ft_strchr(mapchrs, *((char *)(midLine->content + f)))) && tmp > (mapchrs + 3))//si es mapchr y es mapchr de los posteriores a pos 3
                    {
                        if (foundPlayer) //si ya se había encontrado jugador, hay mas de un jugador, mapa inválido
                        {
                            if (g_config.spritelist)
                                freeSprtList(&g_config.spritelist);
                            freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                            return (-4);
                        }
                        else if (f == 0 /*si f es NULL no entramos pero weno*/|| *((char *)(midLine->content + f + 1)) == '\0' || *((char *)(midLine->content + f + 1)) == ' ' || *((char *)(midLine->content + f - 1)) == ' ' || (mapListMem(y - 2))->len < f || (mapListMem(y))->len < f ||  mapList(f, y - 2) == ' ' || mapList(f, y) == ' ') //si el jugador está como primer char o último char de línea, o si es contiguo a un espacio, tira todo el mapa, hombre ya
                        {
                            if (g_config.spritelist)
                                freeSprtList(&g_config.spritelist);
                            freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                            return (-1);
                        }
                        foundPlayer = 49; //si encontramos jugador lo reportamos
                        *((char *)(midLine->content + f)) = 'A'; //marcamos pos de jugador como transitable provisional (no se ha comprobado transitabilidad en todo el eje, solo en sus vecinos, lo primero se hace en floodFill)
                        g_player.posx = (double)f + 0.5;//asignamos su posición en eje X a posx inicial del jugador, con un desplazamiento para estar en medio de la casilla
                        g_player.posy = (double)(y - 1) + 0.5; // asignamos su posición en eje Y a posy del jugador. Y es Y - 1 porque y siempre es la posterior a midLine, donde analizamos presencia del jugador para poder mirar arriba y abajo, y nuevamente 0.5 es un offset para llevar al jugador al medio de su casilla.
                        //y aquí asignamos la orientación inicial del jugador en función de su letra N->Norte, S->Sur, E-Este, W-Oeste.
                        if (*tmp == 'N' || *tmp == 'n')
                        {
                            g_player.dirx = (double)-0;
                            g_player.diry = (double)-1;
                            g_player.planex = (double)0.66;
                            g_player.planey = (double)-0;
                        }
                        else if (*tmp == 'S' || *tmp == 's')
                        {
                            g_player.dirx = (double)0;
                            g_player.diry = (double)1;
                            g_player.planex = (double)-0.66;
                            g_player.planey = (double)0;
                        }
                        else if (*tmp == 'E' || *tmp == 'e')
                        {
                            g_player.dirx = (double)1;
                            g_player.diry = (double)-0;
                            g_player.planex = (double)0;
                            g_player.planey = (double)0.66;
                        }
                        else if (*tmp == 'W' || *tmp == 'w')
                        {
                            g_player.dirx = (double)-1;
                            g_player.diry = (double)0;
                            g_player.planex = (double)-0;
                            g_player.planey = (double)-0.66;
                        }
                    }
                    f++;     
                }
            }
        if (!y)
            {
                free(firstLine);
                line = NULL;
            }
        y++;
    }
    /*    ////////
        if (!y || stayOut) //primera (y == 0) y última (stayOut activado) línea de todas no pueden contener ningún NSEW.
        {
            //while (line[i] == '1' || line[i] == ' ')
            while (line[i] && (tmp = ft_strchr(mapchrs, line[i])) && tmp < (mapchrs + 4)) // Mientras line[i] exista y sea un char de posiciones 0 a 3 de mapchrs (no NSEW)
            {
                if (line[i] == '2')
                    spriteCounter((double)i, (double)y, line[i]);
                i++;
            }
            if (line[i] && !y) //si encuentras al personaje en la primera línea, mapa inválido
                return (-1);
            else if (!line[0]) //si última línea vacía
                break ;
            else if (line[i]) //si encuentras al personaje en la última línea 
            {
                if (g_config.spritelist)
                    freeSprtList(&g_config.spritelist);
                freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                return (-1);
            }
            else if (!y)
            {
                tmp = ft_strdup(line);
                listPtr = ft_lstnew((char *)tmp);
                listPtr->len = ft_strlen((const char *)tmp);
                g_config.maplist = listPtr;
            }
            else
            {
                tmp = ft_strdup(line);
                listPtr = ft_lstnew((char *)tmp);
                listPtr->len = ft_strlen((const char *)tmp);
                ft_lstadd_back(&g_config.maplist, listPtr);
            }
        }
        else 
        {  
            while ((line[i] && ft_strchr(mapchrs, line[i]))) //al principio de la cadena, si mapchrs, salta hasta primer char no mapchr
            {
                if (line[i] == '2')
                    spriteCounter((double)i, (double)y, line[i]);
                i++;
            }
            if (line[i] && y < 2) //si encontramos línea inválida y no hay al menos 3 líneas, cortamos --> esto ahora fuera del while
            {
                if (g_config.spritelist)
                    freeSprtList(&g_config.spritelist);
                freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                return (-2);
            }
            else if (line[i]) //si encontramos línea inválida y hay al menos 3 líneas, cortamos en la línea anterior --> esto ahora fuera del while
                {
                    stayOut = 0;
                    break ;
                }

            else
            {
                tmp = ft_strdup(line);
                listPtr = ft_lstnew((char *)tmp);
                listPtr->len = ft_strlen((const char *)tmp);
                ft_lstadd_back(&g_config.maplist, listPtr);
            }
        }
        if (y >= 2) //buscaremos al jugador (NSEW) en las líneas de en medio, y comprobaremos que sus vecinos inmediatos son válidos y que solo hay un jugador
        {
            if (y == 2)
                midLine = g_config.maplist->next; //siempre línea de en medio
            else if (y > 2)
                midLine = midLine->next;
            i = 0;
            while (*((char *)(midLine->content + i))) //mientras no sea NULL
            {
                if ((tmp = ft_strchr(mapchrs, *((char *)(midLine->content + i)))) && tmp > (mapchrs + 3))//si es mapchr y es mapchr de los posteriores a pos 3
                {
                
                //printf("\nposx Value: %f\n", g_player.posx);
                //printf("\nposy Value: %f\n", g_player.posy);
                //printf("\nmidlineContent: %s\n", ((char *)(midLine->content)));
                //printf("\ni: %d\n", i);
                    if (foundPlayer) //si hay mas de un jugador, mapa inválido
                    {
                        if (g_config.spritelist)
                            freeSprtList(&g_config.spritelist);
                        freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                        return (-4);
                    }
                    else if (i == 0 || *((char *)(midLine->content + i + 1)) == '\0' || mapList(i, y - 2) == ' ' || mapList(i, y) == ' ' || mapList(i + 1, y - 1) == ' ' || mapList(i - 1, y - 1) == ' ') //si el jugador está como primer char o último char de línea, o si es contiguo a un espacio, tira todo el mapa, hombre ya
                    {
                        if (g_config.spritelist)
                            freeSprtList(&g_config.spritelist);
                        freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                        return (-1);
                    } 
                    foundPlayer = 49;
                    *((char *)(midLine->content + i)) = 'A';
                    g_player.posx = (double)i + 0.5;//cuenta como NWES, si no es la primera, aborta badMap, de lo contrario compara x-1 x+1 y+1 y-1
                    g_player.posy = (double)(y - 1) + 0.5; // -1 porque y es la tercera línea, la posterior a midLine, 0.5 es un offset para llevar al jugador al medio del cuadrado.
                    //printf("\nposx Value: %f\n", g_player.posx);
                    //printf("\nposy Value: %f\n", g_player.posy);
                    if (*tmp == 'N' || *tmp == 'n')
                    {
                        g_player.dirx = (double)-0;
                        g_player.diry = (double)-1;
                        g_player.planex = (double)0.66;
                        g_player.planey = (double)-0;
                    }
                    else if (*tmp == 'S' || *tmp == 's')
                    {
                        g_player.dirx = (double)0;
                        g_player.diry = (double)1;
                        g_player.planex = (double)-0.66;
                        g_player.planey = (double)0;
                    }
                    else if (*tmp == 'E' || *tmp == 'e')
                    {
                        g_player.dirx = (double)1;
                        g_player.diry = (double)-0;
                        g_player.planex = (double)0;
                        g_player.planey = (double)0.66;
                    }
                    else if (*tmp == 'W' || *tmp == 'w')
                    {
                        g_player.dirx = (double)-1;
                        g_player.diry = (double)0;
                        g_player.planex = (double)-0;
                        g_player.planey = (double)-0.66;
                    }
                }
                i++;
            }
        }
        
        y++; //y siempre está en tercera línea
        printf("\nY Value: %d\n", y);
    }*/
    g_config.maph = --y; //Al salir, sea por EOF, pasando por el último y++, o por llegar a línea inválida que debe descontarse, y siempre acaba valiendo uno más que la posición de la última línea del mapa, por lo que debemos restarle uno
    printf("\nmapH Value: %d\n", g_config.maph);
    listPtr = g_config.maplist;
    while (listPtr)
    {
        printf("\n%zu # %s", listPtr->len, listPtr->content);
        listPtr = listPtr->next;
    }
    printf("\nY Value: %d\n", y);
    sprtListPtr = g_config.spritelist;
    int tonti = 1;
    while (sprtListPtr)
    {
        printf("\nSprite %d: X%f, Y%f Sprite Type: %c, Sprite Num %d", tonti, sprtListPtr->posx, sprtListPtr->posy, sprtListPtr->spritetype, g_config.spritenum);
        sprtListPtr = sprtListPtr->next;
        tonti++;
    }
    //freeList(&g_config.maplist);
    if (y < 2) //mapa debe tener al menos tres líneas para ser valido
    {
        if (g_config.maplist)
        {
            if (g_config.spritelist)
                freeSprtList(&g_config.spritelist);
            freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
            return (-2);
        }
        else
            return (-2);
    }
    if (!foundPlayer) //mapa debe tener un jugador para ser válido
    {
        if (g_config.maplist)
        {
            if (g_config.spritelist)
                freeSprtList(&g_config.spritelist);
            freeList(&g_config.maplist); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
            return (-3);
        }
        else
            return (-3);
    }
    if (floodFill() == -1)
    {
        if (g_config.spritelist)
            freeSprtList(&g_config.spritelist);
        freeList(&g_config.maplist);
        return (-1);
    }
    return (1);
}


/*
** This function analyses a line. If the entire line consists of mapchars,
** it returns 1 to validate it as a mapline. If it finds a non-mapchar in
** the line or the line is empty, it returns 0 to reject it.
*/
int     isMap(char *line)
{
    int     i;
    char    *tmp;
    char    *mapchrs;

    i = 0;
    mapchrs = " 012NnSsEeWw";
    while (line[i] && (tmp = ft_strchr(mapchrs, line[i])))
        i++;
    if (i > 0 && !line[i])
        return (1);
    else
        return (0);  
}


/*
** The result array saves results of each map parsing function. 1 simply
** means successful; negative numbers correspond to error messages.
*/
int    getMap(const char *ptr)
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
            i = 1;
            if (result[0] < 1)
                result[0] = getres(*line);
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
            while (i < 6 && result[i] == 1)
                i++;
            if (i == 6) //si todas las configuraciones obligatorias están hechas puede seguir buscando las opcionales hasta encontrar una mapline o fin de archivo
                if (isMap(*line)) //si encontramos una línea del mapa
                        break ;
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
        i = 1;
        while (result[i] > -1)
            i++;
        if (i < 6 && result[i] < 0) //Errores 'rojos' (1-5) son mortales y terminan el programa; amarillos permiten lanzar el programa con valores por defecto
            return (0);
        if ((i = getMapArray(fd, *line)) == -1)
        {
            //free(*line);
            //*line = NULL;
            ft_putstr(outOfBounds, strlen(outOfBounds));
            return (0);
        }
        else if (i == -2)
        {
            //free(*line);
            //*line = NULL;
            ft_putstr(badMap3line, strlen(badMap3line));
            return (0);   
        }
        else if (i == -3)
        {
            //free(*line);
            //*line = NULL;
            ft_putstr(noPlayer, strlen(noPlayer));
            return (0);
        }
        else if (i == -4)
        {
            //free(*line);
            //*line = NULL;
            ft_putstr(tooManyPlayers, strlen(tooManyPlayers));
            return (0);
        }
        //if (*line)
        //{
        //    free(*line);
        //    *line = NULL;
        //}

        printf("\nResolution: %d, %d", g_config.screenw, g_config.screenh);
        char c = mapList(1, 1);
       printf("\nHABEERRRRR %c", c);
    }
                  //  printf("%d\n%d\n", g_config.screenw, g_config.screenh);
    //printf("FD: %d", fd);
    if (close(fd) < 0)
        ft_putstr(couldNotClose, ft_strlen(couldNotClose));
    close(fdtest);
    return (1);
}

void makeclsimg(void)
{
    g_clsimg.mlx_img = mlx_new_image(g_screendata.mlx_ptr, g_config.screenw, g_config.screenh);
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
        g_blueMetalImg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, g_blueMetalImg.texPath, &g_config.texw, &g_config.texh);
        g_yellowMetalImg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, g_yellowMetalImg.texPath, &g_config.texw, &g_config.texh);
        g_greenMetalImg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, g_greenMetalImg.texPath, &g_config.texw, &g_config.texh);
        g_pinkMetalImg.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, g_pinkMetalImg.texPath, &g_config.texw, &g_config.texh);
        g_sprt2img.mlx_img = mlx_xpm_file_to_image(g_screendata.mlx_ptr, g_config.spritetexpath, &g_config.spritew, &g_config.spriteh);
        if (!g_blueMetalImg.mlx_img || !g_yellowMetalImg.mlx_img || !g_greenMetalImg.mlx_img || !g_pinkMetalImg.mlx_img || !g_sprt2img.mlx_img)
        {
            if (!g_blueMetalImg.mlx_img)
                ft_putstr(pathNOFail, ft_strlen(pathNOFail));
            if (!g_yellowMetalImg.mlx_img)
                ft_putstr(pathSOFail, ft_strlen(pathSOFail));
            if (!g_greenMetalImg.mlx_img)
                ft_putstr(pathWEFail, ft_strlen(pathWEFail));
            if (!g_pinkMetalImg.mlx_img)
                ft_putstr(pathEAFail, ft_strlen(pathEAFail));
            if (!g_sprt2img.mlx_img)
                ft_putstr(pathSprFail, ft_strlen(pathSprFail));
            exit(EXIT_FAILURE); //Fugoso?
        }
        if ((getTexRes(wallSize, g_blueMetalImg.texPath)) < 0)
            ft_putstr(wallTexSizeFail, ft_strlen(wallTexSizeFail));
        else
        {
            g_config.texw = wallSize[0];
            g_config.texh = wallSize[1];
        }
        compTexRes();
        if ((getTexRes(sprSize, g_config.spritetexpath)) < 0)
            ft_putstr(sprTexSizeFail, ft_strlen(sprTexSizeFail));
        else
        {
            g_config.spritew = sprSize[0];
            g_config.spriteh = sprSize[1];
        }
        
        printf("\nRetrieved Tex Sizes: %d, %d\n", g_config.spritew, g_config.spriteh);
        
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
      if (!getMap(argv[1]))
        return (EXIT_FAILURE);
      //printf("\n%s", argv[1]);
      g_player.newdirxy = malloc(2 * sizeof(double));
//Create screen
   //if (getMap fails, do not start)
   
   
   
    if (!(g_screendata.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, g_config.screenw, g_config.screenh, "Norminator 3D")))
        return (EXIT_FAILURE);
    makeclsimg();
    makeTexImg();
    mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
    mlx_hook(g_screendata.mlx_win, 17, 0, ft_stop, (void*)0);
    mlx_hook(g_screendata.mlx_win, 2, 0, ft_keyPress, (void*)0);
    mlx_hook(g_screendata.mlx_win, 3, 0, ft_keyRelease, (void *)0);
    mlx_loop_hook(g_screendata.mlx_ptr, ft_rayCaster, (void *)0);    
    mlx_loop(g_screendata.mlx_ptr);
    return(EXIT_SUCCESS);
  }

  