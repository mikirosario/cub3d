/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpgenerator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:11:02 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/27 19:52:49 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** This function is like int_to_uchar, but we take only the first three bytes
** of an unsigned integer, instead of all four. We don't need the last one,
** (the most significant byte), because it codes for transparency which we
** don't use in the screenshot, which only has a color depth of 24 bits.
*/

void		uint_to_uchar(unsigned char *threebytes, unsigned int integer)
{
	threebytes[0] = (unsigned char)(integer);
	threebytes[1] = (unsigned char)(integer >> 8);
	threebytes[2] = (unsigned char)(integer >> 16);
}

/*
** This function will take an array of four bytes (unsigned char) and an
** integer (int) as arguments. It passes the int to the array by segmenting
** it byte by byte. Both the original integer and the destination array are
** in little-endian format, so no juggling, we just pass each byte directly.
**
** We take the first byte of the integer and pass it too the first byte in the
** array, right bitshift 8 bits to put the second byte at the integer address
** and pass that, and so on until all four bytes are transferred.
*/

void		int_to_uchar(unsigned char *fourbytes, int integer)
{
	fourbytes[0] = (unsigned char)(integer);
	fourbytes[1] = (unsigned char)(integer >> 8);
	fourbytes[2] = (unsigned char)(integer >> 16);
	fourbytes[3] = (unsigned char)(integer >> 24);
}

/*
** In this function we iterate through the entire image buffer, which is casted
** to uint for ease of use. We retrieve each color, pass it into the threebytes
** array (we only need the rgb values, not the transparency value stored in the
** most significant byte, so we discard that one), write those bytes to the bmp
** file, rinse, repeat for every image line (y). Note that in bmp format images
** are read from the bottom to the top, so first we get the *last* line in the
** buffer and write it *first* in the file, and then iterate upwards until we
** get to the *first* line in the buffer, which is written *last* in the bmp
** file.
**
** In bmp format all color lines must be divisible by four. We will always have
** screenW * 3 bytes per line in the bmp file (one byte per rgb value per
** color). If screenW % 4 is zero the line is divisible by 4 already and we
** don't need any padding. Otherwise, we need to add screenW % 4 bytes of
** padding per line at the end of each line. These bytes are filled with 0s.
**
** If, for whatever reason, we are unable to write to file, write will return
** -1, which we'll treat as a screenshot write error. We should always write
** at least 1 byte here every time write is called, so if write returns 0 this
** will also be treated as a screenshot write error.
*/

ssize_t		copyscreen(int fd, int pad, unsigned int *buf)
{
	int				x;
	int				y;
	int				i;
	unsigned char	threebytes[3];
	ssize_t			res;

	y = g_config.screenh - 1;
	x = y * g_config.screenw;
	res = 1;
	while (res && y >= 0)
	{
		while (res && x < ((y * g_config.screenw) + g_config.screenw))
		{
			uint_to_uchar(threebytes, (buf[x]));
			res = write(fd, threebytes, 3);
			x++;
		}
		if ((i = pad))
			while (res && i--)
				res = write(fd, "\0", 1);
		x = --y * g_config.screenw;
	}
	return (res < 1 ? 0 : 1);
}

/*
** We calculate (as necessary) and fill in the necessary bmp header values
** here. We fill our header with 0s to start (thanks ft_bzero :D).
**
** Since values below 255 (UCHAR_MAX) like 54 fit into a single byte, and bmp
** uses little-endianness, we can just cast the first byte to unsigned char and
** plop it into the first byte for its series, leaving the rest filled with
** zeroes. For values that may use all four bytes of an integer, we use
** int_to_uchar to pass the value.
**
** We MUST write 54 bytes exactly as the header of the bmp file, so if write
** returns ANY other figure we will treat it as a screenshot write error.
*/

ssize_t		writeheader(int fd, int pad)
{
	int				filesize;
	unsigned char	header[54];

	filesize = ((3 * g_config.screenw + pad) * g_config.screenh) + 54;
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	int_to_uchar(&header[2], filesize);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	int_to_uchar(&header[18], g_config.screenw);
	int_to_uchar(&header[22], g_config.screenh);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	return (write(fd, header, 54) != 54 ? 0 : 1);
}

/*
** Your screenshot in BMP format, your highness... :P
**
** If open fails, as per usual, we report an open error. If either of the write
** functions fail, we report a write error. If close fails, we report a close
** error. I KNOW you wanted to see more error flags. Don't lie. To play around
** with all the bitshifting I had to learn for this project, I decided to
** encode and check for these errors bitwise in an error integer. Woot. ;p
*/

int			screenshot(unsigned int *buf)
{
	int	pad;
	int	fd;
	int	error;

	pad = g_config.screenw % 4;
	g_config.screenshot = 0;
	error = 0;
	if ((fd = open("screenie.bmp", O_RDWR | O_CREAT | O_TRUNC | \
	O_APPEND, 0777)) < 3)
		error = error | 00000001;
	else if (!(writeheader(fd, pad)) || !(copyscreen(fd, pad, buf)))
		error = error | 00000010;
	if (fd && (close(fd)) < 0)
		error = error | 00000100;
	if (error)
		bmperror(error);
	else
		ft_printf(GREEN"%s"RESET, SCREENSHOTSAVED);
	return (1);
}
