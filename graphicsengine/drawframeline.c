/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawframeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 19:45:47 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/28 17:54:05 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** This is the beginning of a function to assign textures based on wall number
** that I used in a much earlier version of this project, when I got the
** textures this way instead of depending on the side facing the player.
**
** I'm saving it in case I want it for a future version.
**
** Needs to be modified to work with maplist.
**
**  g_framedata.texy = (int)(g_framedata.texpos) & (g_config.texh - 1);
**	if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 1)
**		texPtr = g_blueMetalImg.tex_Ptr;
**	else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 2)
**		texPtr = g_yellowMetalImg.texPtr;
**	else if (g_worldMap[g_raydata.mapx][g_raydata.mapy] == 3)
**		texPtr = g_greenMetalImg.tex_Ptr;
**	else
**		texPtr = g_pinkMetalImg.tex_Ptr;
**	//make color darker for y-sides
**	buf[ibuf] = g_raydata.side == 1 ? (((texPtr[g_framedata.texx + \
** g_framedata.texy * g_config.texw]) >> 1) & 8355711) : \
** texPtr[g_framedata.texx + g_framedata.texy * g_config.texw];
**	//increment texPos by step
**	g_framedata.texpos += g_framedata.step;
**
** Anyway, this function below, drawfloor, does what it says on the tin. It
** draws the floor. ;) It just need to keep drawing until it reaches the end
** of the vertical line, which is screenH - 1 (we start counting from 0) lines
** from the top. It will only draw while pixel is less than screenH - 1 pixels
** on the y axis, that is, if after the ceiling and floor we still haven't
** reached the end of the screen.
**
** Nothin needs to be returned from this function.
*/

void	drawfloor(int x, int pixel, unsigned int *buf)
{
	while (pixel < (x + (g_config.screenh - 1) * g_config.screenw))
	{
		buf[pixel] = g_framedata.xfloorcolor;
		pixel += g_config.screenw;
	}
}

/*
** This function assigns the texture based on the side we are facing as we look
** at the exposed wall. If side == 1 and stepY (ray direction in the Y or
** up-down axis) is positive, we're looking south, so it's the south wall. If
** side == 1 and stepY is negative, we're looking north, so it's the north
** wall. If side is 0 and stepX (ray direction in the X or east-west axis) is
** positive, we're facing east, so it's the east wall. If side is 0 and stepX
** is negative, we're facing west, so it's the west wall.
**
** Once we know which texture we need to paint, we need to paint the line of
** pixels from the texture until the drawEnd position. To do that, first we
** must determine which pixel from the texture to paint (texY) for each point
** on the line. This will be the previously determined starting texture
** coordinate (texPos), which I will then bitwise AND or 'mask' with texture
** height is this will prevent overflow according to Lode for reasons I frankly
** do not yet understand, but I believe him. ;)
**
** Anyway, step, which is likewise defined beforehand, will establish how many
** pixels to move up in the texture depending on the line height, which itself
** becomes larger as distance decreases. Specifically, step will be texture
** height divided by line height. For every pixel until drawEnd we will move
** step pixels down the texture.
**
** I have three modes for drawing walls, which you can switch between with the
** m key, and two of them are for textured walls and turn the shading on and
** off. If shading is on (m == 1) then for each side 1 wall we shade the color
** by bitshifting right and then applying a mask to set the first byte to zero
** as otherwise it won't be for reasons, again, Lode understands, and I am
** currently just accepting and do not yet fully understand. ;)
**
** In either case, we then use the x and y coordinates of the texture pixel to
** dereference that pixel and pass its value to our image buffer pixel. We do
** this for every image buffer pixel until drawEnd, which is where the wall
** stops. If the wall fills the screen, drawStart and drawEnd would be the top
** and bottom of the screen, respectively.
**
** It returns the pixel after the drawEnd pixel position.
*/

int		texturedwalls(int x, int pixel, unsigned int *buf)
{
	unsigned int	*texptr;

	if (g_raydata.side == 1 && g_raydata.stepy > 0)
		texptr = g_sowallimg.tex_ptr;
	else if (g_raydata.side == 1 && g_raydata.stepy < 0)
		texptr = g_nowallimg.tex_ptr;
	else if (g_raydata.side == 0 && g_raydata.stepx > 0)
		texptr = g_eawallimg.tex_ptr;
	else if (g_raydata.side == 0 && g_raydata.stepx < 0)
		texptr = g_wewallimg.tex_ptr;
	while (pixel <= (x + g_framedata.drawend * g_config.screenw))
	{
		g_framedata.texy = (int)(g_framedata.texpos) & (g_config.texh - 1);
		if (g_keydata.m == 1)
			buf[pixel] = g_raydata.side == 1 ? (((texptr[g_framedata.texx + \
			g_framedata.texy * g_config.texw]) >> 1) & 8355711) : \
			texptr[g_framedata.texx + g_framedata.texy * g_config.texw];
		else
			buf[pixel] = texptr[g_framedata.texx + \
			g_framedata.texy * g_config.texw];
		g_framedata.texpos += g_framedata.step;
		pixel += g_config.screenw;
	}
	return (pixel);
}

/*
** This function draws walls in solid color mode. It is simpler than the
** texturedwalls function because no relationship needs to be calculated
** between the texture map and the line bein drawn, as it's always the same
** solid color. Instead, we just assign a color based on which direction the
** ray is going and just paint that color all down the line. I use shading here
** again for the colors when side is 1.
**
** The color is drawn in the image buffer line until drawEnd. It will return
** the pixel after the drawEnd pixel position.
*/

int		solidcolorwalls(int x, int pixel, unsigned int *buf)
{
	g_framedata.xcolor = 0;
	if (g_raydata.side == 1 && g_raydata.stepy > 0)
		g_framedata.xcolor = 0x00ff0000;
	else if (g_raydata.side == 1 && g_raydata.stepy < 0)
		g_framedata.xcolor = 0x0000ff00;
	else if (g_raydata.side == 0 && g_raydata.stepx > 0)
		g_framedata.xcolor = 0x000000ff;
	else if (g_raydata.side == 0 && g_raydata.stepx < 0)
		g_framedata.xcolor = 0x00ffff00;
	if (g_raydata.side == 1)
		g_framedata.xcolor = (g_framedata.xcolor >> 1) & 8355711;
	while (pixel <= (x + g_framedata.drawend * g_config.screenw))
	{
		buf[pixel] = g_framedata.xcolor;
		pixel += g_config.screenw;
	}
	return (pixel);
}

/*
** drawStart tells us where to start drawing the wall in buf, which is the
** image buffer. So until we get to that position in the image buffer we will
** draw ceiling.
**
** Pixel is the indexed position in buf, and begins as equal to X, the first
** pixel in the x column. Pixel will be incremented by screen width, so it will
** always remain under the same x column, meaning the same line of the screen
** image, moving us vertically along whichever line of pixels we are dealing
** with (x). If the screen is filled by the wall then drawStart will equal
** 0, so it will just be the same as x. Since pixel starts out as equal to x,
** it will never be less than drawStart, so no ceiling will be drawn.
**
** This function will return the drawStart pixel position in the image buffer
** when it is finished.
*/

int		drawceiling(int x, int pixel, unsigned int *buf)
{
	while (pixel < (x + g_framedata.drawstart * g_config.screenw))
	{
		buf[pixel] = g_framedata.xceilingcolor;
		pixel += g_config.screenw;
	}
	return (pixel);
}

/*
** This function draws a single line in a frame in strict order, starting with
** the ceiling pixels, then the wall pixels, then the floor pixels, from top to
** bottom. Pressing the m key toggles between solid and textured walls. X is
** the position of the top-most vertical pixel in the line, and will always be
** a value from 0 to screenW - 1, as controlled from the calling function while
** from which this function is called (see raycaster.c).
*/

void	drawframeline(int x, unsigned int *buf)
{
	int	pixel;

	pixel = x;
	pixel = drawceiling(x, pixel, buf);
	if (g_keydata.m == 2)
		pixel = solidcolorwalls(x, pixel, buf);
	else
		pixel = texturedwalls(x, pixel, buf);
	drawfloor(x, pixel, buf);
}
