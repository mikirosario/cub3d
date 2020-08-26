/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 20:36:48 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error g_iamerror;

/*
** These functions will respectively create and put the g_clsimg.mlx_img image
** to window. It was originally meant to be clear screen function, until I
** realized I don't really need a clear screen function. I might find another
** use for it, though, so I'm leaving it here. ;)
**
** I might repurpose it for overlays or something in the bonus. :)
**
**
** void makeclsimg(void)
** {
**    g_clsimg.mlx_img = mlx_new_image(g_screendata.mlx_ptr, g_config.screenw, \
**	  g_config.screenh);
** }
**
** void    cls()
** {
**   mlx_put_image_to_window(g_screendata.mlx_ptr, g_screendata.mlx_win, \
** 	 g_clsimg.mlx_img, 0, 0);
** }
*/

/*
** This function is launched when the user exits normally, by pressing escape
** or by clicking the X on the upper left of the window.
**
** Linux version:
**
** int   ft_stop(int key, void *param)
** {
**	(void)param;
**	if (key == 0xff1b || key == 0)
**	{
**		freeme();
**		ft_printf(GREEN"\n**** THANKS FOR PLAYING! :D ****\n\n"RESET);
**		exit(EXIT_SUCCESS);
**	}
**	return (0);
** }
**
** Mac:
*/

int		ft_stop(int key, void *param)
{
	(void)param;
	if (key == 0x35 || key == 0x00)
	{
		freeme();
		ft_printf(GREEN"\n**** THANKS FOR PLAYING! :D ****\n\n"RESET);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	configure(char *argv, int *success)
{
	if ((*success = cubhandler(argv)))
	{
		if (!(g_screendata.mlx_ptr = mlx_init()))
			*success = 0;
		else if (!(g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, \
		g_config.screenw, g_config.screenh, "Norminator 3D")))
			*success = 0;
		else
			*success = maketeximg();
	}
}

int		main(int argc, char **argv)
{
	int	success;

	(void)argc;
	if (argv[2] && !(ft_strncmp("--save", argv[2], ft_strlen(argv[2]))))
		g_config.screenshot = 1;
	//if too many args, abort error
	ft_printf(GREEN"\nCHECKING .CUB FILE...\n"RESET);
	initialize();
	configure(argv[1], &success);
	printnotifications();
	printerrors();
	if (!success)
	{
		freeme();
		return (EXIT_FAILURE);
	}
	mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
	mlx_hook(g_screendata.mlx_win, 17, 1l << 17, ft_stop, (void*)0);
	mlx_hook(g_screendata.mlx_win, 2, 1L << 0, keypress, (void*)0);
	mlx_hook(g_screendata.mlx_win, 3, 1L << 1, keyrelease, (void *)0);
	mlx_loop_hook(g_screendata.mlx_ptr, raycaster, (void *)0);
	mlx_loop(g_screendata.mlx_ptr);
	return (EXIT_SUCCESS);
}
