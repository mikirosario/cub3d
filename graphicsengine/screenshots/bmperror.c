/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmperror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:31:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:26:17 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	bmperror(int error)
{
	ft_printf(YELLOW"%s"RESET, YELLOWERROR);
	if (error & 00000001)
		printf(YELLOW"%s"RESET, BMPCREATEFAIL);
	if (error & 00000010)
		printf(YELLOW"%s"RESET, BMPWRITEFAIL);
	if (error & 00000100)
		printf(YELLOW"%s"RESET, BMPCLOSEFAIL);
}
