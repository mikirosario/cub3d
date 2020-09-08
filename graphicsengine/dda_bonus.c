/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:13:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/08 23:14:59 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"


int		verticaldoor(void)
{
	//double	sidedistx;
	//double	sidedisty;
	double	mapx;
	//double	mapy;
	t_line	ray;
	t_line	door;
	t_triangle raytodoor;
	double	x;
	double	y;

	double perpwalldist;
	double	wallx;
	//double	anglea;
	//double	anglec;
	//double	sidea;
	
//we came from below and exit through the side, maybe we hit the door, maybe not
	if (g_raydata.sidedistx < g_raydata.sidedisty)
	{
		//g_raydata.sidedistx += g_raydata.deltadistx;

		//g_raydata.side = 0;

		perpwalldist = (g_raydata.mapy - g_player.posy + \
		(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
		wallx = g_player.posx + perpwalldist * g_raydata.raydirx;
		wallx -= floor(wallx);

	
		ray.startx = wallx;
		ray.starty = 0;
		ray.endx = 0;
		
		mapx = g_raydata.mapx + g_raydata.stepx;
		perpwalldist = (mapx - g_player.posx + \
		(1 - g_raydata.stepx) / 2) / g_raydata.raydirx;
		wallx = g_player.posy + perpwalldist * g_raydata.raydiry;
		wallx -= floor(wallx);
		
		ray.endy = wallx;
		door.startx = 0;
		door.starty = 0.5;
		door.endx = 1;
		door.endy = 0.5;
		(void)y;
		(void)x;
		(void)door;
		//if (findintersection(&ray, &door, &x, &y))
			//if ((x > 0 && x < 1))
			if ((ray.endy >= 0.5 && g_raydata.stepy > 0) || (ray.endy <= 0.5 && g_raydata.stepy <= 0))
			{
				raytodoor.opposite = 0.5;
				raytodoor.anglealpha = PI/2;
				raytodoor.angletheta = g_raydata.raydiry * (PI/2);
				ft_hypotenuse(&raytodoor);
				g_raydata.hypo = raytodoor.hypotenuse;
				return (1);
			}
	}
	else //if we came from below and are exiting from above, we definiely hit the door
	{
		//second coordinates wallx, y == 1
		//sidedisty = g_raydata.sidedisty + g_raydata.deltadisty;
		//mapy = g_raydata.mapy + g_raydata.stepy;
		//g_raydata.side = 1;
	
		//RAYDIR * PI/2 == RADIAN!!!!!????
		//perpwalldist = (mapy - g_player.posy + 
		//(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
		//wallx = g_player.posx + 
		//perpwalldist * g_raydata.raydirx;
		//anglea = atan2(g_raydata.raydiry, 1);
		//wallx -= floor(wallx);
	
		//rayline coordinates
		//start x1: g_framedata.wallx, y1: 0
		//end	x2: wallx, y2: 1

		//doorline coordinates
		//start x1: 0, y1: 0.5
		//end x2: 1, y2: 0.5
	
		//rayline
		
		

		/*anglea = fabs(g_raydata.raydiry); //> 0 ? -g_raydata.raydiry : g_raydata.raydiry;
		anglec = PI - anglea - (PI/2);
		sidea = (sin(anglea) * wallx) / sin(anglec);
		a = 0.5;
		c = wallx;
		g_raydata.hypo = sqrt(((pow(a, 2) + pow(c, 2)) - ((2 * a * c) * cos(PI/2))));
		if (sidea >= 0.5)//g_raydata.mapy - (g_raydata.mapy + g_raydata.stepy / 2))*/
			return (1);
	}
	return (0);
}

/*
** This function modifies the raycaster code a bit to cast 'thin' walls that
** are painted across the middle of the square instead of the edge, which
** I will (eventually, finally, after several days of banging my head against
** the table :_( xD) be using as Wolfenstein-style sliding doors.
**
** To do this I must alter the ray logic a bit. Now, if a ray intersects a line
** halfway up the square representing the door, it is a special door hit, and
** will return 1, causing the calling function to return 2 instead of 1, which
** will be used as a signal to render the pixel stripe at a distance of 0.5
** further away from the player than the usual map square edge, as well as
** change the texture, check the door state, etc.
**
** If it does NOT intersect the door line it will return 0 and the normal dda
** code will handle the ray.
**
** For the moment I don't handle the horizontal casting for this, so it will
** interpret the neighbouring floor square as 'overlapping' the wall if
** next to a wall... It's not a bug, it's a feature! xD Meaning I'll get to it.
** Eventually I'll draw an H, when I'm over the sheer trigonometric trauma I've
** been through over the past few days. xD
** 
** This function is for doors perpendicular to the y axis (horizontal doors,
** visible from above and below), so it is only called if side == 1, which
** tells us that we hit the edge of a map square from tbe 'bottom' (or 'top' if
** you prefer, it's relative, that is, the y vector, or side facing the front
** of the player).
**
** Knowing that, I ask again whether sidedistx is less than sidedisty, which
** tells me whether the *next* map square this ray will encounter is on the
** side (x vector) or 'top' (y vector). If sidedistx is less than sidedisty
** then I know that we will leave this map square from the side (x vector). If
** it is not, then I know that we will leave this map square from the
** 'top' (y vector).
**
** Since I also know that we *entered* from the 'bottom', if we leave from the
** 'top' this means we MUST have intersected the middle line along the way, so
** that is easy. If sidedisxt is not less than sidedist y, we definitely hit
** the door, always, and return 1.
**
** If we will leave from the side, however, it will depend on the ray's angle.
** if we leave below the position of the door on the y axis (0.5 over the map
** square edge), then we do not hit the wall and so return 0. If we leave at
** or above the door position on the y axis, then we hit the door and return
** 1.
**
** To determine whether we hit or missed, I repurpose the equations used to get
** wallx for texture caster (the position *where* we hit the next square edge).
** Confusingly, if we leave following the x vector and hit next square on the
** side, wallx is actually a y coordinate. :p I've never liked the name wallx
** but I kept it out of respect for the Lode tutorial, because where would I
** be without it! xD
**
** Anyway, if we calculate wallx as if we were going to draw that wall, and
** then subtract it from the floor of itself (to keep only the decimals), we
** have an absolute y value for where we leave the square we are in. If we are
** facing south (stepy > 0) then it is a hit if that value is 0.5 or greater.
** If we are facing north (stepy < 0), then it is a hit if that value is 0.5 or
** less.
**
** Yes... I made a line intersect function. I made a hypotenuse function. I was
** about to write a thesis on trigonometry. In the end... well they're still
** pretty cool functions. xD But I don't need them here. Into libft they go.
*/

int		hordoorhitcheck(void)
{
	double	mapx;
	double perpwalldist;
	double	wallx;

//we came from below and exit through the side, maybe we hit the door, maybe not
	if (g_raydata.sidedistx < g_raydata.sidedisty)
	{	
		mapx = g_raydata.mapx + g_raydata.stepx; //go to next square
		perpwalldist = (mapx - g_player.posx + \
		(1 - g_raydata.stepx) / 2) / g_raydata.raydirx; //calculate perpendicular distance to player camera
		wallx = g_player.posy + perpwalldist * g_raydata.raydiry; //calculate where on the adjacent square edge the ray hit, this will effectively be a y axis value in our square
		wallx -= floor(wallx); //remove the map-centric component of wallx and get the square-centric component
		if ((wallx >= 0.5 && g_raydata.stepy > 0) || (wallx <= 0.5 && g_raydata.stepy <= 0))
			return (1);
	}
	else //if we came from below and are exiting from above, we definiely hit the door
			return (1);
	return (0);
}

/*
** The hit variable will be initialized to 0 here, and will later be used to
** record a wall hit. Until a wall is hit, we'll keep moving the ray from
** side to side, where walls can be. Depending on the ray's orientation, it
** will move so many walls along one axis for every wall it hits on the other.
** When a wall is hit, we exit.
*/

void	sidetoside(void)
{
	g_raydata.hit = 0;
	while (!g_raydata.hit)
	{
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
		if (g_config.map[g_raydata.mapy][g_raydata.mapx] == '1')
			g_raydata.hit = 1;
		if (g_config.map[g_raydata.mapy][g_raydata.mapx] == '_' && g_raydata.side == 1)
			if (hordoorhitcheck())
				g_raydata.hit = 2;
				//if (g_raydata.sidedisty - g_raydata.deltadisty < g_raydata.mapy + g_raydata.stepy / 2)
				//	g_raydata.hit = 2;
	}
}

/*
** Here the steps and initial side distance of the ray will be calculated. Step
** will determine whether we're moving left or right and up or down, which will
** depend on the value of the rayDir variable (if rayDirX is positive we are
** moving right, which we signify with stepX = 1, if negative we are moving
** left, which we signify with stepX = -1, if rayDirY is positive we are moving
** up, which we signify with stepY = 1, if negative we are moving down which we
** signify with stepY = -1).
**
** The side distance for the initial ray position is special because we can be
** anywhere in relation to the wall. For subsequent calculations of side
** distance, however, we know we will always move from wall edge to wall edge.
*/

void	stepandinitialside(void)
{
	if (g_raydata.raydirx < 0)
	{
		g_raydata.stepx = -1;
		g_raydata.sidedistx = (g_player.posx - g_raydata.mapx) * \
		g_raydata.deltadistx;
	}
	else
	{
		g_raydata.stepx = 1;
		g_raydata.sidedistx = (g_raydata.mapx + 1.0 - g_player.posx) * \
		g_raydata.deltadistx;
	}
	if (g_raydata.raydiry < 0)
	{
		g_raydata.stepy = -1;
		g_raydata.sidedisty = (g_player.posy - g_raydata.mapy) * \
		g_raydata.deltadisty;
	}
	else
	{
		g_raydata.stepy = 1;
		g_raydata.sidedisty = (g_raydata.mapy + 1.0 - g_player.posy) * \
		g_raydata.deltadisty;
	}
}

/*
** The ray starts at the player's position. Here we determine in which
** direction or orientation it is travelling on the map.
**
** For a given orientation (depending on which way it's pointing), a ray will
** always have a set distance from the edge of one wall to the edge of the
** next. We call top and bottom walls y-facing walls and left or right walls
** x-facing walls. The distance from the edge of a wall to the edge of another
** x-facing or y-facing wall is a function of the ray's orientation, that is,
** how much far it travels along one axis versus how far it travels along the
** other. We just need to know whether the next wall it hits will be x-facing
** or y-facing so we know which to paint on screen, and its distance from the
** player so we know how many pixels tall to paint it.
**
** First we will determine these distances, taking the ray's orientation,
** which will, of course, depend on the player's orientation. They will be used
** later by the DDA algorithm to trace the ray's path wall by wall across the
** map to determine where it will first hit a wall.
**
** We calculate the ray's position and direction. Then we determine which box
** of the map we are in (mapX and mapY). Then we calculate the distance the ray
** must travel to go from one x-facing side to the next x-facing side, or one
** y-facing side to the next y-facing side as a function of its orientation.
** Unless facing perfectly west, east, north or south, this will be a
** fractional number.
**
** Then we will call stepandinitialside.
*/

void	castray(int x)
{
	g_player.camerax = 2 * x / (double)g_config.screenw - 1;
	g_raydata.raydirx = g_player.dirx + g_player.planex * g_player.camerax;
	g_raydata.raydiry = g_player.diry + g_player.planey * g_player.camerax;
	g_raydata.mapx = (int)g_player.posx;
	g_raydata.mapy = (int)g_player.posy;
	if (g_raydata.raydiry == 0)
		g_raydata.deltadistx = 0;
	else if (g_raydata.raydirx == 0)
		g_raydata.deltadistx = 1;
	else
	{
		//g_raydata.deltadistx = fabs(1 / g_raydata.raydirx);
		g_raydata.deltadistx = sqrt(1 + (g_raydata.raydiry*g_raydata.raydiry)/(g_raydata.raydirx*g_raydata.raydirx));
	}
	if (g_raydata.raydirx == 0)
		g_raydata.deltadisty = 0;
	else if (g_raydata.raydiry == 0)
		g_raydata.deltadisty = 1;
	else
	{
		g_raydata.deltadisty = sqrt(1 + (g_raydata.raydirx * g_raydata.raydirx)/(g_raydata.raydiry * g_raydata.raydiry));
		//g_raydata.deltadisty = fabs(1 / g_raydata.raydiry);
	}
	stepandinitialside();
	sidetoside();
}
