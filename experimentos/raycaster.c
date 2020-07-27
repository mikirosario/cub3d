/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 01:19:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/02/12 02:01:30 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    ft_rayCaster(void)
{
    //Where 1 is a whole side: initialize player position and direction, and camera plane distance from centre
    g_player.posX = 22;
    g_player.posY = 8;
    g_player.dirX = -1;
    g_player.dirY = 0;
    g_player.planeX = 0;
    g_player.planeY = 0.66;
    g_imageData.time = 0;
    g_imageData.oldTime = 0;
    //player casts ray; calculate ray's position and direction based on player's facing direction modified by plane dir times 
}


int main()
{
    //Create screen
    if ((g_screenData.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screenData.mlx_win = mlx_new_window(g_screenData.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    mlx_loop(g_screenData.mlx_ptr);
    ft_rayCaster();
}