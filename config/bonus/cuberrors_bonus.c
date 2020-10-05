/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuberrors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:22:12 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/05 15:23:45 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

extern t_error g_iamerror;

/*
** This function will check the result array to identify error flags.
** If a parameter has not been successfully read from the cub file,
** its corresponding result will be 0 and an appropriate error message
** will be displayed.
**
** There are two types of errors - yellow or non-fatal, and red or
** fatal. Non-fatal errors are handled by using default values instead
** of user-configured values. An error message will be displayed but
** the program will not terminate.
**
** All errors from position 1 to position 4 on the array are fatal.
** The error in position 8 is also fatal. The error in position 5 is
** only fatal if sprites are found, but this is determined after
** the maphandler function is run. The rest are non-fatal.
**
** If any fatal errors are found, this function will return 0.
** Otherwise, it will return 1.
*/

int		cuberrorhandler(int *result)
{
	int i;

	if (result[0] == 0)
		g_iamerror.getresfail = 1;
	if (result[1] == 0)
		g_iamerror.getnofail = 1;
	if (result[2] == 0)
		g_iamerror.getsofail = 1;
	if (result[3] == 0)
		g_iamerror.getwefail = 1;
	if (result[4] == 0)
		g_iamerror.geteafail = 1;
	if (result[5] == 0)
		g_iamerror.getsprfail = 1;
	if (result[6] == 0)
		g_iamerror.getfloorfail = 1;
	if (result[7] == 0)
		g_iamerror.getceilfail = 1;
	if (!(result[8]))
		g_iamerror.nomapfound = 1;
	i = 1;
	while (result[i] && i < 7)
		i++;
	g_iamerror.mapchecked = i == 7 ? 1 : 0;
	return (i < 7 || !result[8] ? 0 : 1);
}

/*
** I decided this was a splendid opportunity to put my split function to use,
** even if it does mean a rather laborious process of freeing memory. Well,
** laborious for the computer, for me it was just three lines. But still. ;)
**
** I split all the parameters into a two-dimensional character pointer array,
** so I can later call them one by one to be printed out as needed.
**
** First we print the missing parameters message. Then we'll iterate through our
** gotparam byte using the isbitset function, looking for the unset bits. The
** bits correspond to the listed parameters in reverse order, that is, the
** right-most bit corresponds to the left-most parameter (R). An unset bit
** means that parameter was not found. This could be because the parameter was
** not introduced by the user, or because a cub file error was thrown before the
** parser got to the parameter. Either way, it should be evident what happened
** in the error report. And if not, well I'll just build a wrapper around it to
** interpret it even further... no, j/k. I'm not THAT obsessed with error
** handling... am I? AM I? O_O Not for this project, at least. xD
**
** After this, we print a newline, free the memory, and off we go...
*/

void	missingparamreport(void)
{
	char	**splitarray;
	int		i;

	splitarray = ft_split("R.NO.SO.WE.EA.S.F.C", '.');
	ft_printf(RED"%s"RESET, MISSINGPARAM);
	i = 0;
	while (i < 8)
	{
		if (!(isbitset(g_iamerror.gotparam, i)))
			ft_printf("%s ", splitarray[i]);
		i++;
	}
	write(1, "\n", 1);
	while (i)
		del(splitarray[--i]);
	del(splitarray);
}

/*
** This function handles the new cub file errors. A badline error means
** characters were detected that aren't valid parameters. Map characters that
** aren't also parameters will throw a badline error if they are found before
** all the parameters are checked. The line number where the bad line was found
** will be printed for the user.
**
** If a parameter is found more than once, a dupparam error will be thrown,
** again indicating the line number where it was found for the user.
**
** If anything is found after the map ends (except for a single newline, which
** is allowed), a badendcub error will be thrown. It should be fairly obvious
** where it is, so we don't bother to print the line number.
**
** Finally, in the gotparam byte each bit is set as parameters are found. If all
** parameters are found then all bits will be set, so this byte should equal
** 255. If it does not, then we must have missing parameters, and we will launch
** the missingparamreport function to print them individually.
*/

void	cuberrors(void)
{
	ft_printf(RED"%s%s"RESET, REDERROR, BADCUB);
	if (g_iamerror.badline)
		ft_printf("Line %d: "RED"%s"RESET, g_iamerror.badline, BADLINE);
	if (g_iamerror.dupparam)
		ft_printf("Line %d: "RED"%s"RESET, g_iamerror.dupparam, DUPPARAM);
	if (g_iamerror.badendcub)
		ft_printf(RED"%s"RESET, BADCUBEND);
	if (g_iamerror.gotparam != 255)
		missingparamreport();
}
