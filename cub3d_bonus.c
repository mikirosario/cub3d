/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/10/03 16:29:14 by mrosario         ###   ########.fr       */
=======
/*   Updated: 2020/10/05 15:54:17 by miki             ###   ########.fr       */
>>>>>>> 0a85661561a9cab0efbeaa4a38ae8fa4dfad0ace
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d_bonus.h"

t_error g_iamerror;

void	musicfork(void)
{
	if (!g_config.screenshot)
		playtrack(MAIN_THEME);
	else
		exit(EXIT_SUCCESS);
}

/*
** This function is a generic, run-of-the-mill "free this memory and set the
** pointer to NULL" function that should really be in my libft by now. :p
*/

void	del(void *freethis)
{
	free(freethis);
	freethis = NULL;
}

/*
** I needed a strcmp for this, so here it is. Definitely going into libft.
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (!(*s1))
			return (0);
		s1++;
		s2++;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : 1);
}

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
** or by clicking the X on the upper left of the window, by beating the game,
** or because it's game over, man, game over.
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
		musicfork();
	mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
	mlx_hook(g_screendata.mlx_win, 17, 1L << 17, ft_stop, (void*)0);
	mlx_hook(g_screendata.mlx_win, 2, 1L << 0, keypress, &g_config);
	mlx_hook(g_screendata.mlx_win, 3, 1L << 1, keyrelease, (void *)0);
	mlx_hook(g_screendata.mlx_win, 4, 1L << 2, mousepress, (void *)0);
	mlx_hook(g_screendata.mlx_win, 5, 1L << 3, mouserelease, (void *)0);
	mlx_hook(g_screendata.mlx_win, 6, 1L << 6, mousemove, (void *)0);
	mlx_loop_hook(g_screendata.mlx_ptr, raycaster_bonus, &rdata);
	mlx_loop(g_screendata.mlx_ptr);
	return (EXIT_SUCCESS);
}
