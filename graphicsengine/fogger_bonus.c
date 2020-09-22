/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fogger_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 05:32:48 by miki              #+#    #+#             */
/*   Updated: 2020/09/22 05:52:27 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

unsigned int	fogger(unsigned int argb, double fog)
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char trans;

	fog = 0.75;
	blue = argb;
	green = argb >> 8;
	red = argb >> 16;
	trans = argb >> 24;
	blue = (1 - fog) * blue;
	green = (1 - fog) * green;
	red = (1 - fog) * red;
	return (create_trgb(trans, red, green, blue));
}