/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcaster_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:09:52 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/11 17:16:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
** Oh, Norminette. You so crazy. The things you make me do. ;p

void	defineray(t_line *ray, double startx, double starty, double endx, double endy)
{	
	ray->startx = startx;
	ray->starty = starty;
	ray->endx = endx;
	ray->endy = endy;
}
*/

/*
** Hodoor? Horror door? This took me FOREVER to figure out. The pain. The agony!
** The maths! All to eventually discover this simple solution!
**
** Note that doorend tracks 'how open' a door is. 0 means 0% open. 0.1 means
** 10% open. 0.2 means 20% open. 1 means 100% open. We follow the ray halfway
** through the square with the door and record its landing location. Then we
** just ask if it is less than doorend plus whatever mapx we are in. If it is,
** it is allowed to go on its way. If not, it hits.
*/

int		hordoorslide(void)
{
	t_localraydata	local;
	t_spritedata	**door;


	//if we came from below

		local.perpwalldist = ((double)(g_raydata.mapy + (0.5 * g_raydata.stepy)) - g_player.posy + \
		(1 - g_raydata.stepy) / 2) / g_raydata.raydiry;
		local.wallx = g_player.posx + local.perpwalldist * g_raydata.raydirx;


		door = g_config.door;
		while ((*door)->dooraddr != &g_config.map[g_raydata.mapy][g_raydata.mapx])
			door++;
		if (local.wallx > (*door)->doorend + g_raydata.mapx && local.wallx < 1 + g_raydata.mapx)
			return (1);
	
	return (0);
}

/*
** See the (very long) description of hordoorcheck. The logic of verwallcheck is
** exactly the same, just with vectors changed. ;)
*/

int		verdoorhitcheck(void)
{
	double	mapy;
	double perpwalldist;
	double	wallx;

//we came from side and exit through the top or bottom, maybe we hit the door, maybe not
	if (g_raydata.sidedisty < g_raydata.sidedistx)
	{	
		mapy = g_raydata.mapy + g_raydata.stepy; //go to next square
		perpwalldist = (mapy - g_player.posy + \
		(1 - g_raydata.stepy) / 2) / g_raydata.raydiry; //calculate perpendicular distance to player camera
		wallx = g_player.posx + perpwalldist * g_raydata.raydirx; //calculate where on the adjacent square edge the ray hit, this will effectively be a y axis value in our square
		wallx -= floor(wallx); //remove the map-centric component of wallx and get the square-centric component
		if ((wallx >= 0.5 && g_raydata.stepx > 0) || (wallx <= 0.5 && g_raydata.stepx <= 0))
			return (1);
	}
	else //if we came from side and are exiting from side, we definiely hit the door
			return (1);
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
** you prefer, it's relative, that is, the y vector, or side facing up or down).
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
**
** Never mind, I think I will need line intersect to animate the door! xD
** Line intersect using version...
** Must modify line intersect to take segments into account...
*/

/*
** This function modifies the raycaster code a bit to cast 'thin' walls that
** are painted across the middle of the square instead of the edge, which are
** used to project closed doors.
**
** To do this I must alter the ray logic a bit. Now, for a map square with a
** horizontal door, we imagine a line parallel to the camera plane bisecting the
** square through the middle. This line is at distance 0.5 from map square edge
** where the wall would normally be, and thus is at distance perpwalldist + 0.5
** from the player. This line represents the closed door.
**
** Now, if a ray intersects this line representing the door, it is a special
** door hit, and will cause this function to return 1, causing the calling
** function to return 2 instead of 1, which will be used by the renderer as a
** signal to render the pixel stripe at a distance of 0.5 further away from the
** player than the usual map square edge, as well as to change the texture,
** check the door state, etc.
**
** If the ray does NOT intersect the door, the function will return 0 and the
** normal dda code will continue to handle the ray's trajectory.
** 
** This function is for doors perpendicular to the y axis (horizontal doors,
** visible from above and below), so it is only called if side == 1, which
** tells us that we hit the edge of a map square from the 'bottom' (or 'top' if
** you prefer, it's relative, that is, the y vector, or side facing up or down).
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
** that is easy. If sidedistx is not less than sidedist y, we DEFINITELY hit
** the door, always, and so always return 1.
**
** If we will leave from the side, however, it will depend on the ray's angle.
** if we leave below the position of the door on the y axis (0.5 over the map
** square edge), then we do not hit the wall, and so return 0. If we leave at
** or above the door position on the y axis, then we hit the door and return
** 1.
**
** For the closed doors it is not necessary to calculate anything more than the
** local y coordinate of the ray when it *leaves* the map square with the wall.
** We only need the line intersection for the opening/closing animations.
**
** To determine whether we hit or missed, I repurpose the equations used to get
** wallx for texture caster (the position *where* we hit the next square edge).
** Confusingly, wallx is actually sometimes a y coordinate. xD I've never liked
** the name wallx for this variable, but I kept it out of respect for the Lode
** tutorial, because, really, where would I be without it!? xD In this
** particular case, wallx is actually the y coordinate of the ray when it
** leaves the map square through the right or left sides.
**
** Anyway, if we calculate wallx as if we were going to draw that side wall, and
** then subtract it from the floor of itself (to keep only the decimals), we
** have a local y value for where we leave the square we are in. Now, while the
** y value is local, the rest of the values are from the player's
** frame of reference, which means that right, left, up and down flip when we
** turn 180 degrees.
**
** So, if we are facing south (stepy > 0) then it is a hit if that value is 0.5
** or more, as the y coordinates run from north to south in ascending order. If
** we are facing north (stepy < 0), then it is a hit if that value is 0.5 or
** *less*, since then the coordinates run from south to north in *descending*
** order. It's a bit confusing, so I also made a version that localizes *all*
** values to the map square frame of reference, so that they are
** player-orientation-invariant. However, I've decided to use that only for the
** door closing/opening animation, as that is where it really gets confusing
** without the transformation, while this little function for closed doors is
** still relatively tame. xD
**
** Note that I don't handle the horizontal casting for horizontal doors, or
** vertical casting for vertical doors, if you look at the door perpendicularly
** it will always appear that the neighbouring floor square is 'overlapping' the
** wall, even if it's a floor square. It's not a bug, it's a feature! xD I only
** intend to use these 'thin walls' to represent doors, which will always be
** between two walls and thus always logically occluded when viewed
** perpendicularly, so I don't need to program perpendicular rendering for them.
**
** Player-orientation-invariant version (local frame of reference):
** int		hordoorhitcheck(void)
** {
**	double	mapx;
**	double perpwalldist;
**	double	raydirx;
**	double	raydiry;
**	double	wallx;
**
** raydirx = g_raydata.stepy == -1 ? g_raydata.raydirx * -1 : g_raydata.raydirx;
** raydiry = g_raydata.raydiry < 0 ? g_raydata.raydiry * -1 : g_raydata.raydiry;
**
**	if (g_raydata.sidedistx < g_raydata.sidedisty)
**	{	
**		mapx = g_raydata.mapx + g_raydata.stepx; //go to next square
**		perpwalldist = (mapx - g_player.posx + \
**		(1 - g_raydata.stepx) / 2) / raydirx;
**		wallx = g_player.posy + perpwalldist * raydiry;
**		wallx -= floor(wallx);
**		if (g_raydata.stepy == -1)
**			wallx = 1 - wallx;
**		if (wallx >= 0.5)
**			return (1);
**	}
**	else
**			return (1);
**	return (0);
** }
**
** Player-orientation-sensitive version (player's frame of reference):
*/

int		hordoorhitcheck(void)
{
	double	mapx;
	double perpwalldist;
	double	wallx;

//we came from side and exit through the top or bottom, maybe we hit the door, maybe not
	if (g_raydata.sidedistx < g_raydata.sidedisty)
	{	
		mapx = g_raydata.mapx + g_raydata.stepx; //go to next square
		perpwalldist = (mapx - g_player.posx + \
		(1 - g_raydata.stepx) / 2) / g_raydata.raydirx; //calculate perpendicular distance to player camera
		wallx = g_player.posy + perpwalldist * g_raydata.raydiry; //calculate where on the adjacent square edge the ray hit, this will effectively be a y axis value in our square
		wallx -= floor(wallx); //remove the map-centric component of wallx and get the square-centric component
		if ((g_raydata.stepy > 0 && wallx >= 0.5) || (g_raydata.stepy <= 0 && wallx <= 0.5))
			return (1);
	}
	else //if we came from side and are exiting from side, we definiely hit the door
			return (1);
	return (0);
}