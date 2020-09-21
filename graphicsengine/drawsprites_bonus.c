/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 18:46:59 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/20 22:32:33 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

extern t_imagedata *g_simg[10];

/*
** As with the wall texture, we use Lode-provided mathemagics to determine
** which sprite texture pixel to draw for every sprite pixel we draw on the
** screen, as a function of the sprite's original height and width in pixels
** (g_config.spriteh and g_config.spritew) divided by its shrunk or expanded
** size (g_framedata.spriteheight and g_framedata.spritewidth) and other bits
** of Lode mathemagics I unfortunately only very vaguely understand. xD The
** numbers 256 and 128 will avoid floats, for example, which I'd normally do
** by rounding or capping precision, vulgar as I am. ;p
**
** We'll make scrny equal to spriteDrawStartY to iterate along the y axis and
** off we go, drawing pixel by pixel.
**
** We ignore the transparency around the sprite when drawing pixels. Remember,
** minilibx is AABBGGRR, so the transparency is at the beginning. :p
*/

void	drawspriteline(t_spriteparams *prms, unsigned int *buf, \
t_spritedata *sprite)
{
	g_config.spriteh = (*g_simg[sprite->spritetype - 48]).texh;
	g_config.spritew = (*g_simg[sprite->spritetype - 48]).texw;
	while (prms->scrny < g_framedata.spritedrawendy)
	{
		prms->d = (prms->scrny - prms->vmovescreen) * \
		256 - g_config.screenh * 128 + g_framedata.spriteheight * 128;
		prms->texy = \
		((prms->d * g_config.spriteh) / g_framedata.spriteheight) / 256;
		g_framedata.xcolor = \
		sprite->texture[g_config.spritew * prms->texy + prms->texx];
		if (g_framedata.xcolor != 0xff000000)
			buf[prms->scrnx + (g_config.screenw * prms->scrny)] = \
			g_framedata.xcolor;
		prms->scrny++;
	}
}

/*
** This function draws a sprite within the player's visual range line by line.
** We've got it all by now! We know where on the image buffer the sprite starts
** and where it ends, we know how big it is. We just need to copy the pixels,
** just as we do with the walls.
**
** Scrnx will be made equal to spriteDrawStartX and used to iterate along the
** X (horizontal) axis on the screen, such that each increment of scrnx will
** represent the top of a new vertical stripe of the sprite to draw.
**
** Embedded in the first while, which controls which stripe/line/column we are
** looking at, we will go ahead and draw pixels ONLY if this line is not
** occluded by something. So the second while, where we actually do the
** drawing, is behind an if(). The if imposes the following conditions, in
** order of confirmation, to allow the drawing to start:
**
** 1. The calculated Y position of the sprite along the Z axis is greater than
** 0 (*transformY > 0), meaning the sprite is in FRONT of the camera. Necessary
** so you don't see things that are BEHIND you.
**
** 2. The calculated x position on the screen is greater than 0 (x > 0),
** meaning that it is NOT off the left side of the screen.
**
** 3. The calculated x position on the screen is less than the width of the
** screen (scrnx < g_config.screenw), meaning that it is NOT off the right side
** of the screen.
**
** 4. Remember the zBuffer? xD We used it to store the perpendicular distance
** from the camera to the wall for every value of X on the screen in an array,
** where each array position corresponds to its X position on the screen. Now
** that we know which x position on the screen we want to draw a sprite on
** (scrnx), we check the perpendicular distance from the camera to the wall
** that we stored for that x position against the value of transformY (the
** distance to the sprite on the Z-axis, aka also perpendicular to the camera).
** In short, as I understand it, if transformY is not less than the
** perpendicular distance to the wall for a given vertical line on the screen,
** it means the sprite is behind that wall, so we don't draw it; otherwise, it
** means it is in front of the wall, so we want to draw it over the wall
** pixels.
*/

void	drawsprite(t_spriteparams *prms, unsigned int *buf, \
t_spritedata *sprite)
{
	prms->scrnx = g_framedata.spritedrawstartx;
	while (prms->scrnx < g_framedata.spritedrawendx)
	{
		prms->texx = (int)(256 * (prms->scrnx - \
		(-g_framedata.spritewidth / 2 + g_framedata.spritescreenx)) * \
		g_config.spritew / g_framedata.spritewidth) / 256;
		prms->scrny = g_framedata.spritedrawstarty;
		if (prms->transformy > 0 && prms->scrnx > 0 && \
		prms->scrnx < g_config.screenw && \
		prms->transformy < g_config.zbuffer[prms->scrnx])
		{
			if (sprite->checkdamage && prms->scrnx == g_config.screenw / 2 - 1) //if checkdamage flag true and the stripe to be drawn is down the middle of the screen
				spraycat(sprite);
			drawspriteline(prms, buf, sprite);
		}
		prms->scrnx++;
	}
}

/*
** Now that we know which x on the screen marks the sprite's position, we
** need to know how big or small we want to draw it, which is the same as
** saying we need to know where on the screen each x with sprite pixels
** will start and where it will end, both on the x and y axes (horizontally and
** vertically). First we determine height as a function of screen height
** divided by transformY, which remember is working as the Z vector here,
** indicating depth inside the screen. Using transformY instead of the real
** distance prevents the fisheye effect, per Lode. vDiv is a divisor we can use
** to shrink the sprite vertically if we want.
**
** We know from the spriteposition function which vertical screen line or
** 'x' will bisect the sprite down the middle (g_framedata.spritescreenx),
** but not where exactly on the screen the sprite begins and ends, which, again
** is the same as saying how big it is.
**
** So now, first we calculate where on the screen's Y axis (vertically) we will
** start drawing the sprite (spriteDrawStartY) and where we will stop
** (spriteDrawEndY). Sprites are basically boxes, so this measurement will hold
** for all the vertical xs in the same sprite. We derive this by dividing
** the negative of the sprite's height in pixels (spriteHeight) by 2 plus the
** screen height divided by 2. Mathemagics. ;) Then we add vMoveScreen to
** further adjust the position as we might prefer (by default it's 0).
**
** We still don't know where the sprite begins and ends on the X (horizontal)
** axis, though. So now we do the same for this axis.
**
** We first calculate the sprite width the same way, taking the screen height
** and dividing by transformY. uDiv is a divisor we can use to shrink the
** sprite horizontally if we want.
**
** From this figure, we then calculate where to start drawing on the X axis
** by dividing the negative of the sprite width we just calculated by 2 and
** adding spriteScreenX, which seems straightforward enough. spriteScreenX
** bisects the sprite, so the sprite starts at spriteScreenX - half the width
** of the sprite, basically. We store this value in spriteDrawStartX. We then
** calculate where we stop drawing the sprite the same way, except it will, of
** course, be spriteScreenX + half the width of the sprite. ^_^
**
** So now we know in exactly which pixel on the image buffer to start drawing
** the sprite and in which pixel to stop. Horray!
**
** NOTE TO SELF: do abs only once to save cycles...
*/

void	spritesize(t_spriteparams *prms, t_spritedata *sprite)
{
	int	size;

	size = abs((int)(g_config.screenh / (prms->transformy)));
	g_framedata.spriteheight = size / sprite->vdiv;
	g_framedata.spritedrawstarty = \
	(-g_framedata.spriteheight / 2 + g_config.screenh / 2 + prms->vmovescreen);
	if (g_framedata.spritedrawstarty < 0)
		g_framedata.spritedrawstarty = 0;
	g_framedata.spritedrawendy = \
	g_framedata.spriteheight / 2 + g_config.screenh / 2 + prms->vmovescreen;
	if (g_framedata.spritedrawendy >= g_config.screenh)
		g_framedata.spritedrawendy = g_config.screenh - 1;
	g_framedata.spritewidth = size / sprite->udiv;
	g_framedata.spritedrawstartx = \
	(-g_framedata.spritewidth / 2 + g_framedata.spritescreenx);
	if (g_framedata.spritedrawstartx < 0)
		g_framedata.spritedrawstartx = 0;
	g_framedata.spritedrawendx = \
	g_framedata.spritewidth / 2 + g_framedata.spritescreenx;
	if (g_framedata.spritedrawendx >= g_config.screenw)
		g_framedata.spritedrawendx = g_config.screenw - 1;
}

/*
** First this function takes the sprite position (x,y) as stored in each
** member of the spritelist in the posx and posy variables, and subtracts the
** player's position from it on each vector to derive the sprite's position
** relative to the camera.
**
** Then we do mathemagics that Lode says is required for proper matrix
** multiplication and I belileve him, even though it's presently beyond my ken
** to understand why. We store the result in invDet. Here is a representation
** of the matrix maths involved:
**
** Transform sprite with the inverse camera matrix:
** [ planeX   dirX ] -1                                    [ dirY      -dirX ]
** [               ]    =  1/(planeX*dirY-dirX*planeY) *   [                 ]
** [ planeY   dirY ]                                       [ -planeY  planeX ]
**
** We do some more mathemagics after that to transform the spriteX and spriteY
** positions as a function of the player's orientation (which way the player
** is facing, which I store in g_player.dirx and g_player.diry). Ultimately,
** transformY is turned into a pseudo Z-axis or vector representing depth
** inside the screen which, together with shrinking and expanding the sprite,
** will give the illusion of 3D positioning. Finally finally, all this will
** be used to derive the screen line in which the sprite as such is located,
** which I interpret as meaning the line that more or less bisects the sprite
** which we store in spriteScreenX. It is an int, so some rounding may be
** involved, of course. But we will later perform more maths on this number
** to calculate which screen pixels exactly we start and finish drawing the
** sprite. ^_^
**
** For a deeper understanding of what is going on here I would need a proper
** mathematics course. I'm totally up for that, though, if 42 wants to put it
** in the cursus, as long as it gives me days and experience points. ;)
**
** Anyway, vMoveScreen is a multiplier we will use to move the sprite up and
** down through the vMove parameter as needed. ^_^
*/

void	spriteposition(t_spriteparams *prms, t_spritedata *sprite)
{
	g_framedata.spritex = sprite->posx - g_player.posx;
	g_framedata.spritey = sprite->posy - g_player.posy;
	prms->invdet = 1.0 / (g_player.planex * g_player.diry - \
	g_player.dirx * g_player.planey);
	prms->transformx = prms->invdet * (g_player.diry * g_framedata.spritex - \
	g_player.dirx * g_framedata.spritey);
	prms->transformy = prms->invdet * (-g_player.planey * \
	g_framedata.spritex + g_player.planex * g_framedata.spritey);
	g_framedata.spritescreenx = (int)((g_config.screenw / 2) * \
	(1 + prms->transformx / prms->transformy));
	prms->vmovescreen = sprite->vmove == 0 ? \
	0 : (int)(sprite->vmove / prms->transformy);
}

/*
** Yes... I have a struct named prms the only function of which is to hold
** all the parameters I need for the sprite caster without having to declare
** them and send them individually to each function. Norminette made me do it,
** just role with it. :p
**
** Prms contains the following:
**
** typedef	struct	spriteparams_s
** {
**	double	transformy;
**	double	transformx;
**	double	invdet;
**	int		vmovescreen;
**	int		scrnx;
**	int		scrny;
**	int		texx;
**	int		texy;
**	int		d;
** }				t_spriteparams;
**
** Henceforth any reference to these variables will refer to the variables in
** this struct.
**
** This function will draw any sprites in the path of the ray, in order of
** appearance, from furthest to closest.
**
** First we use sortsprites, which will determine the order of each sprite
** relative to the user's current perspective an create a mask array at
** g_config.spriteorder. By iterating through the spritelist using the
** spriteorder values, we will go through the sprites in order of appearance.
**
** Once sorted, we will project and draw the sprites. The sprite dimensions
** and position will depend on their distance from the player.
**
** First we need to know which sprite we want to draw. We are going to draw
** them in order, from the furthest to the closest relative to the camera. We
** use the spriteiter function to iterate through the spritelist, and the
** spriteorder mask we just created to go first to the furthest sprite
** (spriteorder[0]), then the next closest (spriteorder[1]), and so on, until
** all the sprites (spriteNum) have been accounted for. Remember, spriteorder
** starts at position 0 while spriteNum starts at 1, so when i == spriteNum we
** will already have processed the last sprite. Anyway, we get the address of
** the sprite we want to process and send it to the functions that need it. :)
**
** First we need to calculate the position of the sprite on the screen.
**
** Then we need to calculate the height of the sprite on the screen, and then
** use that to calculate the highest and lowest pixels in the current vertical
** screen line that will be taken up by the sprite.
*/

void	castsprites(unsigned int *buf)
{
	int				i;
	t_spritedata	*sprite;
	t_spriteparams	prms;

	i = 0;
	sortsprites(g_config.spriteorder);
	while (i < g_config.spritenum)
	{
		sprite = g_config.sprt[g_config.spriteorder[i]];
		if (sprite->spritetype == '4' || sprite->spritetype == '7')
		 animate(sprite);
		if (sprite->hitanimationframes && sprite->spritetype == '2')
			if (!(--sprite->hitanimationframes))
				sprite->texture = sprite->animtex[0];
		spriteposition(&prms, sprite);
		spritesize(&prms, sprite);
		drawsprite(&prms, buf, sprite);
		if (sprite->remove)
			removesprite(sprite);
		i++;
	}
}
