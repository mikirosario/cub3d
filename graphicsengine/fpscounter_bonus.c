/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpscounter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:35:31 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:15:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** This is a frame counter. In the raycaster function is the static variable
** timestart. If it is equal to zero, we store the time when the raycaster
** function started in this variable (in seconds), otherwise it is left alone.
**
** We then pass the address of timestart to this function every frame. In this
** frame we have a static variable fps which increments by 1 every time it is
** called (which is every frame).
**
** We take the time again in this function (in seconds). Since the time
** function returns time in seconds, we know that the second they become
** unequal (literally) one second will have elapsed from when timestart was
** measured. At that point we print the value of fps on the screen, we save it
** to oldfps to continue printing it every frame until a new fps is detected
** (one second later, of course), we reset timestart to zero to take the time
** again from the calling function, we reset fps to count from zero. Otherwise
** we continue printing the old fps.
*/

void	countframes(time_t *timestart)
{
	time_t			endtime;
	static int		fps = 0;
	static char		*fps_str = NULL;

	fps++;
	if ((endtime = time(NULL) != *timestart))
	{
		if (fps_str)
			del(fps_str);
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		0, g_config.screenh - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		0, g_config.screenh - 80, 0x0000ff00, (fps_str = ft_itoa(fps)));
		*timestart = 0;
		fps = 0;
	}
	else
	{
		if (!fps_str)
			fps_str = ft_calloc(1, 1);
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		0, g_config.screenh - 100, 0x0000ff00, "FRAMEAZOS POR SEGUNDO:");
		mlx_string_put(g_screendata.mlx_ptr, g_screendata.mlx_win, \
		0, g_config.screenh - 80, 0x0000ff00, fps_str);
	}
}
