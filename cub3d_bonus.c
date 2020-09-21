/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/21 03:14:39 by mikiencolor      ###   ########.fr       */
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
		//kill parent and all children
		kill(0, SIGTERM);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	configure(t_raycasterdata *rdata, char **argv, int argc, int *success)
{
	ft_printf(GREEN"\nCHECKING .CUB FILE...\n"RESET);
	if (!(*success = argc > 3 ? 0 : 1))
		g_iamerror.toomanyargs = 1;
	else if (argc == 3)
		if (!(ft_strncmp("--save", argv[2], ft_strlen(argv[2]))))
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
	//pid_t			ppid;

	initialize();
	configure(&rdata, argv, argc, &success);
	printnotifications();
	printerrors();
	if (!success)
	{
		freeme();
		return (EXIT_FAILURE);
	}
	rdata.animatedoor = NULL;
	rdata.animationframes = 0;
	rdata.portalanimframes = 0;
	reset_timer(&rdata.catsbanetimer);
	reset_timer(&rdata.phrasetimer);
	reset_timer(&rdata.chismetimer);
	reset_timer(&rdata.endingtimer);
	g_config.musicpid = fork();
	if (!g_config.musicpid)
	{
		system("while :; do afplay ./theme.mp3; done");
		//if original parent dies, parent becomes 1. child polls to see if parent is 1.
		//system("while :; do afplay ./theme.mp3; done &");
		//ppid = getppid();
		//while (ppid != 1)
		//	ppid = getppid();
		//kill (0, SIGTERM);
	}
	mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
	mlx_hook(g_screendata.mlx_win, 17, 1L << 17, ft_stop, (void*)0);
	mlx_hook(g_screendata.mlx_win, 2, 1L << 0, keypress, (void*)0);
	mlx_hook(g_screendata.mlx_win, 3, 1L << 1, keyrelease, (void *)0);
	mlx_loop_hook(g_screendata.mlx_ptr, raycaster_bonus, &rdata);
	mlx_loop(g_screendata.mlx_ptr);
	return (EXIT_SUCCESS);
}
