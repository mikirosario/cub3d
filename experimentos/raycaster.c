/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 01:19:54 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 19:15:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    ft_rayCaster(void)
{
    //Where 1 is a whole side: initialize player position and direction, and camera plane distance from centre
    g_player.posx = 22;
    g_player.posy = 8;
    g_player.dirx = -1;
    g_player.diry = 0;
    g_player.planex = 0;
    g_player.planey = 0.66;
    g_imageData.time = 0;
    g_imageData.oldTime = 0;
    //player casts ray; calculate ray's position and direction based on player's facing direction modified by plane dir times 
}


int main()
{
    //Create screen
    if ((g_screendata.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((g_screendata.mlx_win = mlx_new_window(g_screendata.mlx_ptr, screenWidth, screenHeight, "Norminator 3D")) == NULL)
        return (EXIT_FAILURE);
    mlx_loop(g_screendata.mlx_ptr);
    ft_rayCaster();
}