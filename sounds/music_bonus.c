/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 03:25:32 by miki              #+#    #+#             */
/*   Updated: 2020/09/27 20:28:45 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d_bonus.h"

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
	char	*afplay[3];
	int		i;

	afplay[0] = "afplay ";
	afplay[1] = "afplay -r 0.65 ";
	afplay[2] = "afplay -t 2 ";
	i = 0;
	if (!(ft_strcmp(DOOR, sound)))
		i = 1;
	else if (!(ft_strcmp(DISCOVERY, sound)))
		i = 2;
	ft_strlcpy(cmd, afplay[i], 51);
	if (ft_strlcat(cmd, sound, 51) >= 51)
		return (0);
	system(cmd);
	return (1);
}

/*
** Execvp turns the forked process into an afplay process. Now it can be killed
** by the parent program using the child pid. No more messy system call. :D
**
** Playtrack plays mp3 files at the paths referenced in music_bonus.h.
**
** Playtrack takes the track name and uses it to transform the entire program
** into nothing more than music player. Warning: using this without forking may
** be hazardous to your health. ;)
*/

void	playtrack(char *track)
{
	char	*args[3];

	args[0] = "afplay";
	args[1] = track;
	args[2] = NULL;
	execvp(args[0], args);
}
