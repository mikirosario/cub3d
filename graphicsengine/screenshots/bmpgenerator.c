/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpgenerator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:11:02 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/19 20:42:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	padding(void)
{
	int	pad;

	return (pad = ((3 * g_config.screenW) % 4));
}

unsigned char	*uint_to_uchar(unsigned char *threebytes, unsigned int integer)
{
	threebytes[0] = (unsigned char)(integer);
	threebytes[1] = (unsigned char)(integer >> 8);
	threebytes[2] = (unsigned char)(integer >> 16);
	return (threebytes);
}

void	int_to_uchar(unsigned char *fourbytes, int integer)
{
	fourbytes[0] = (unsigned char)(integer);
	fourbytes[1] = (unsigned char)(integer >> 8);
	fourbytes[2] = (unsigned char)(integer >> 16);
	fourbytes[3] = (unsigned char)(integer >> 24);
}

ssize_t		copyscreen(int fd, unsigned int *buf)
{
	int	x;
	int	y;
	unsigned char threebytes[3];
	int	i;
	int pad;
	//unsigned int color;
	ssize_t res;

	y = g_config.screenH - 1;
	x = y * g_config.screenW;
	res = 1;
	pad = padding();
	while (res && y >= 0)
	{
		while (res && x < ((y * g_config.screenW) + g_config.screenW))
		{
	//		color = (buf[x] & 0xFF0000) | (buf[x] & 0x00FF00) | (buf[x] & 0x0000FF);
			uint_to_uchar(threebytes, (buf[x]));
			res = write(fd, threebytes, 3);
			x++;
		}
		if ((i = pad))
			while (res && i--)
				res = write(fd, "\0", 1);
		x = --y * g_config.screenW;
	}
	return (res);
}

/*
** So, since 54 fits into a single byte, and bmp uses little-endianness, we can
** just cast 54 to unsigned char and plop it into position 10, leaving
** positions 11 - 13 filled with zeros. Yay!
*/

ssize_t	writeinfoheader(int fd)
{
	unsigned char	infoheader[40];
	
	ft_bzero(infoheader, 40);
	infoheader[0] = (unsigned char)40; //0, 1, 2, 3
	int_to_uchar(&infoheader[4], g_config.screenW); //4, 5, 6, 7
	int_to_uchar(&infoheader[8], g_config.screenH); //8, 9, 10, 11
	infoheader[12] = (unsigned char)1; //12, 13
	infoheader[14] = (unsigned char)24;
	return (write(fd, infoheader, 40));
}

ssize_t	writefileheader(int fd)
{
	int pad = padding();
	int filesize = ((3 * g_config.screenW + pad) * g_config.screenH) + 54;
	unsigned char	fileheader[14];
	ft_bzero(fileheader, 14);
	fileheader[0] = 'B';
	fileheader[1] = 'M';
	int_to_uchar(&fileheader[2], filesize);
	//2, 3, 4, 5 -->Filesize
	//6, 7, 8, 9 --> Reserved
	fileheader[10] = (unsigned char)54;
	return (write(fd, fileheader, 14));
}

/*
** Your screenshot in BMP format, your highness... :P
*/

int	screenshot(unsigned int *buf)
{
	int				fd;

	g_config.screenshot = 0;
	if (!(fd = open("screenie.bmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777)))
		return (0); //aquí un mensaje de error
	if (!(writefileheader(fd)) || !(writeinfoheader(fd)) || !(copyscreen(fd, buf)))
		return (0);
	else
	ft_printf("\nSUCCESS! Your first step into a wider world.\n");
	close (fd);
	return (1);
}