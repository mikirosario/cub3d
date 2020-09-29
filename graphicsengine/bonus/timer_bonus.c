/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:06:29 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:57:28 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

void	reset_timer(struct timeval *t)
{
	t->tv_sec = 0;
	t->tv_usec = 0;
}

/*
** This function returns the difference in miliseconds between the times passed
** in t0 and t1. If no t0 is passed, it returns 0. If no t1 is passed, then the
** function will create one, use it to get the present time, and then return
** the difference between that time and t0.
*/

double	msec_diff(struct timeval *t0, struct timeval *t1)
{
	struct timeval tend;

	if (!t0)
		return (0);
	else if (!t1)
	{
		gettimeofday(&tend, NULL);
		t1 = &tend;
	}
	return (t1->tv_sec - t0->tv_sec) * 1000.0 + \
	(t1->tv_usec - t0->tv_usec) / 1000.0;
}
