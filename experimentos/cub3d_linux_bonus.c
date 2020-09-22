/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_linux_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 04:21:03 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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



void	configure(t_raycasterdata *rdata, char **argv, int argc, int *success)
{
	ft_printf(GREEN"\nCHECKING .CUB FILE...\n"RESET);
	if (!(*success = argc > 3 ? 0 : 1))
		g_iamerror.toomanyargs = 1;
	else if (argc == 3)
		if (!(ft_strcmp("--save", argv[2])))
			g_config.screenshot = 1;
	if (*success && (*success = cubhandler(argv[1])))
	{
		if (g_iamerror.getresfail)
			setdisplayresolution();
		if (!(g_screendata.mlx_ptr = mlx_init()))
			*success = 0;
		else if (!(g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, \
		g_config.screenw, g_config.screenh, "Norminator 3D")))
			*success = 0;
		else if (!maketeximg() || !raycaster_start(rdata))
			*success = 0;
	}
}

/*
** Sound attribution (theme.mp3): HAPPY by texasradiofish (c) copyright 2020
** Licensed under a Creative Commons Noncommercial Sampling Plus license.
** http://dig.ccmixter.org/files/texasradiofish/62035 Ft: Haskel,
** Martijn de Boer, Apoxode, Stefan Kartenberg, Subhashish, boboshin.
*/

int		main(int argc, char **argv)
{
	t_raycasterdata	rdata;
	int				success;

	initialize(&rdata);
	configure(&rdata, argv, argc, &success);
	printnotifications();
	printerrors();
	if (!success)
	{
		freeme();
		return (EXIT_FAILURE);
	}
	g_config.musicpid = fork();
	if (!g_config.musicpid)
		playtrack(MAIN_THEME);
	mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
	mlx_hook(g_screendata.mlx_win, 17, 1L << 17, ft_stop, (void*)0);
	mlx_hook(g_screendata.mlx_win, 2, 1L << 0, keypress, (void*)0);
	mlx_hook(g_screendata.mlx_win, 3, 1L << 1, keyrelease, (void *)0);
	mlx_hook(g_screendata.mlx_win, 4, 1L << 2, mousepress, (void *)0);
	mlx_hook(g_screendata.mlx_win, 5, 1L << 3, mouserelease, (void *)0);
	mlx_hook(g_screendata.mlx_win, 6, 1L << 6, mousemove, (void *)0);
	mlx_loop_hook(g_screendata.mlx_ptr, raycaster_bonus, &rdata);
	mlx_loop(g_screendata.mlx_ptr);
	return (EXIT_SUCCESS);
}
