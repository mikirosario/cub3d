/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:13:30 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/07 20:31:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_NOTIFICATIONS_H
# define PRINT_NOTIFICATIONS_H

#define rgbF GREEN"\nRGB Floor Color: %d, %d, %d"RESET
#define hexF GREEN"\nHex Floor Color: %x\n"RESET
#define defaultF GREEN"\nDefault Floor Color\n"RESET
#define rgbC GREEN"\nRGB Ceiling Color: %d, %d, %d"RESET
#define hexC GREEN"\nHex Ceiling Color: %x\n"RESET
#define defaultC GREEN"\nDefault Ceiling Color\n"RESET
#define	mapHeight GREEN"\nMap Height: %d\n"RESET
#define wallTexSize GREEN"\nWall Texture Size (WxH): %d x %d\n"RESET
#define	spriteTexSize GREEN"\nSprite Texture Size (WxH): %d x %d\n"RESET

#endif