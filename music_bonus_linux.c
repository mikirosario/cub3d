/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus_linux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 00:07:26 by miki              #+#    #+#             */
/*   Updated: 2020/09/24 18:51:59 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Finally. FINALLY I UNDERSTAND! Finally I understand what strlcpy and strlcat
** are for! xD Anyway, this function is a roundabout way of playing a sound by
** assembling the command from here and the paths in music_bonus.h, which is
** more complicated than just plugging the system command into the code, but
** since I have Linux and Mac versions of this software this saves me from
** having to split every file that calls a sound into Mac and Linux versions. :p
**
** If your file name is obscenely long it just won't play. 40ish chars is more
** than enough for anyone sane, I say. ;p
*/

int		playsound(char *sound)
{
	char	cmd[50];
	char	*aplay[2];
	int		i;

	aplay[0] = "aplay -q ";
	aplay[1] = "aplay -d 2 -q ";
	i = !(ft_strcmp(DISCOVERY, sound)) ? 1 : 0;
	ft_strlcpy(cmd, aplay[i], 51);
	if (ft_strlcat(cmd, sound, 51) >= 51)
		return (0);
	system(cmd);
	return (1);
}

/*
** Execvp turns the forked process into an mpg123 process, with the flags
** quiet and infinite loop. Now it can be killed by the parent program using
** the child pid. No more messy system call. :D
**
** Playtrack plays mp3 files at the paths referenced in music_bonus.h.
**
** Playtrack takes the track name and uses it to transform the entire program
** into nothing more than music player. Warning: using this without forking may
** be hazardous to your health. ;)
*/

void	playtrack(char *track)
{
	char	*args[6];

	args[0] = "mpg123";
	args[1] = "-q";
	args[2] = "-l -1";
	args[3] = "-f 10000";
	args[4] = track;
	args[5] = NULL;
	execvp(args[0], args);
}
