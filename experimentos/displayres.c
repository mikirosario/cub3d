/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:57:21 by mrosario          #+#    #+#             */
/*   Updated: 2020/03/04 15:07:14 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     getRes(const char *line)
{
    const char  *charPtr;
    int         resCount;

    charPtr = line;
    resCount = 0;
    if (!line)
        return (-2);
    while (*charPtr && (*charPtr != 'R' && *charPtr != 'r'))
        charPtr++;
    while (*charPtr && resCount < 3)
    {
        if (*charPtr > 47 && *charPtr < 58)
        {
            resCount++;
            if (resCount == 1)
                g_config.screenW = ft_atoi(charPtr);
            else
                g_config.screenH = ft_atoi(charPtr);
            while (*charPtr > 47 && *charPtr < 58)
                charPtr++;
        }
        else
            charPtr++;
    }
    return (resCount == 2 ? 1 : -1);
}

