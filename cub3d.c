/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:24:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/22 04:15:00 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error g_iamerror;

/*
** I needed a strcmp for this, so here it is. Definitely going into libft.
*/

int		ft_strcmp(const char *s1, const char *s2)
{
    while(*s1 == *s2)
	{
		if (!(*s1))
			return (0);
		s1++;
		s2++;
	}
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : 1);
}

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
	mlx_do_key_autorepeatoff(g_screendata.mlx_ptr);
	mlx_hook(g_screendata.mlx_win, 17, 1L << 17, ft_stop, (void*)0);
	mlx_hook(g_screendata.mlx_win, 2, 1L << 0, keypress, (void*)0);
	mlx_hook(g_screendata.mlx_win, 3, 1L << 1, keyrelease, (void *)0);
	mlx_loop_hook(g_screendata.mlx_ptr, raycaster, &rdata);
	mlx_loop(g_screendata.mlx_ptr);
	return (EXIT_SUCCESS);
}
