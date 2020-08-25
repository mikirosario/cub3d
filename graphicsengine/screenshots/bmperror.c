/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmperror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:31:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/25 18:35:05 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	bmperror(int error)
{
	ft_printf(YELLOWERROR);
	if (error & 00000001)
		printf(bmpcreatefail);
	if (error & 00000010)
		printf(bmpwritefail);
	if (error & 00000100)
		printf(bmpclosefail);
}
