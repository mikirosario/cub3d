/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnotifications.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:13:30 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/10 20:24:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_NOTIFICATIONS_H
# define PRINT_NOTIFICATIONS_H

#define	Res GREEN"\nResolution: "RESET"\n%d x %d\n"
#define wallPaths GREEN"\nNO Wall Path: "RESET"\n%s\n"GREEN"SO Wall Path: "RESET"\n%s\n"GREEN"EA Wall Path: "RESET"\n%s\n"GREEN"WE Wall Path: "RESET"\n%s\n"
#define	sprPaths GREEN"Sprite Path: "RESET"\n%s\n"
#define wallTexSize GREEN"Wall Texture Size (WxH): "RESET"\n%d x %d\n"
#define	spriteTexSize GREEN"Sprite Texture Size (WxH): "RESET"\n%d x %d\n"
#define rgbF GREEN"\nFloor Color:\nRGB: "RESET"%d, %d, %d"
#define hexF GREEN"\nHex: "RESET"%x\n"
#define defaultF YELLOW"\nDefault Floor Color\n"RESET
#define rgbC GREEN"\nCeiling Color:\nRGB: "RESET"%d, %d, %d"
#define hexC GREEN"\nHex: "RESET"%x\n"
#define defaultC YELLOW"\nDefault Ceiling Color\n"RESET
#define	mapHeight GREEN"\nMap Height: "RESET"\n%d\n"

#endif