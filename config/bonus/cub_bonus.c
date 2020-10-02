/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:38:05 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/02 15:43:23 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d_bonus.h"

extern t_error	g_iamerror;

/*
** This function will first check the result array. If all of the obligatory
** configuration data has been read successfully from the cub file (errors
** 1 - 4 of result array are 0), it will check the line to see if it is a valid
** map line. If it then finds a valid map line, it will assign a result of '1'
** to array member 8 and return 1. If any obligatory configuration data has
** not yet been read successfully, or if the line being analysed is not a
** valid map line, it will return '0'.
*/

int		findfirstmapline(char **line, int *result, int *checked, unsigned int linenum)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	while (i < 7 && result[i] == 1)
		i++;
	while (j < 8 && checked[j] == 1)
		j++;
	if (i == 7 && j == 8)
		if (ismap(*line))
		{
			result[8] = 1;
			g_iamerror.premaplines = linenum - 1;
			return (1);
		}
	return (0);
}

void	getparam(int *result, int *checked, int linenum, char *line)
{
		if (result[0] < 1)
			result[0] = getres(line, linenum, &checked[0]);
		if (result[1] < 1)
			result[1] = getno(line, linenum, &checked[1]);
		if (result[2] < 1)
			result[2] = getso(line, linenum, &checked[2]);
		if (result[3] < 1)
			result[3] = getwe(line, linenum, &checked[3]);
		if (result[4] < 1)
			result[4] = getea(line, linenum, &checked[4]);
		if (result[5] < 1)
			result[5] = getsprite(line, linenum, &checked[5]);
		if (result[6] < 1)
			result[6] = getfcolor(line, linenum, &checked[6]);
		if (result[7] < 1)
			result[7] = getccolor(line, linenum, &checked[7]);
}

/*
** The 'result' array saves result of each map parsing function as an int.
** A 'result' of 1 means the parameter was successfully found and configured.
** Negative numbers returned by the parsing functions correspond to different
** error messages. If all obligatory parameters are configured, optional
** parameters may still be searched for until a map line is found.
**
** If any obligatory parameter is not found, no map search will begin, and EOF
** will be reached with the missing parameters indicated in the 'result' array
** for subsequent error management. If all obligatory parameters are found and
** 'findfirstmapline' discovers a valid map line, it will indicate this in
** result[8] (see findfirstmapline) and terminate the function *without*
** freeing the memory used by line, as the first map line will still be needed
** by the map handler.
**
** UPDATE:
**
** The gatekeeper functions veto cub files with superfluous text or duplicate
** parameters. These were implemented at the end, on request from an evaluator.
** It's not the cleanest implementation, a bit quick and dirty.
**
** The logic is as follows: We set up an array of 8 ints initialized to zero
** with ft_bzero. The array is called checked and keeps track of which
** parameters have been checked, whether or not the check succeeded. We then
** use a function called validitycheck. If a line's text contains a valid
** parameter (R, NO, SO, WE, etc.), we return 2. Spaces are allowed before
** the parameter, but nothing else. If the line is empty, we return 1, since
** we accept empty lines. If anything else is found, validity check signals
** a cubpolice error and badline error and returns 0, ending the while.
**
** Now we sum the values of the checked array. Every time line parser reads one
** of the parameters  (R, NO, SO, WE, etc.) it will set the corresponding
** integer in the checked array to 1. For example, if R is read, checked[0] will
** be set to 1. Thus, if a line passes the validity check and it is not a NULL
** character (empty line), it MUST be a parameter, and therefore, if it's legit
** the first time that parameter is being passed, the sum of the checked array
** values must rise by 1 after all parameter parsers execute. Therefore, if we
** reach the end of the while with a non-null character in our line and no
** parameter parser has 'claimed' it (the checked array sum is the same as at
** the beginning of the while), it MUST be a duplicate parameter. We report
** this to the cubpolice and pass the linenum where it happened for good
** measure, and then kick that garbage out of here.
**
** Note that to make this work with the other functions, the firstmapline
** function now must check the checked array as well as the result array to
** determine whether it is time to start looking for the map, since, although
** some non-obligatory parameters may be wrong or left empty and the game will
** work with default values, ALL of them must now be passed.
**
** If a cubpolice error was detected during file reading, all results are
** considered to have failed and are reset to 0, since, much like Parisians if
** you pronounce a single word wrong, this single mistake means we could not
** understand anything.
**
** Fun time is over, kiddies. Cub files are now serious business and must obey
** the LAW, or else. ¬¬
*/

void	cubread(int *result, char **line, int fd, int linenum)
{
	int	val;
	int	sum;
	int	checked[8];

	ft_bzero(checked, 8 * 4);
	while ((ft_get_next_line(fd, line)) > 0 && ++linenum)
	{
		if (!(*line))
			g_iamerror.mallocfail = 1;
		sum = sumresarray(checked);
		if (!(val = validitycheck(result, *line, sum, linenum)))
			break ;
		getparam(result, checked, linenum, *line);
		if (findfirstmapline(line, result, checked, linenum))
			break ;
		if (val == 2 && sum == (sumresarray(checked)))
		{
			g_iamerror.cubpolice = 1;
			g_iamerror.dupparam = linenum;
			break ;
		}
		del(*line);
	}
	if (g_iamerror.cubpolice)
		policereport(result, checked);
}

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

/*int		cuberrorhandler(int *result)
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
		g_iamerror.getfloorfail = 1;
	if (result[6] == 0)
		g_iamerror.getceilfail = 1;
	if (result[7] == 0)
		g_iamerror.getsprfail = 1;
	if (!(result[8]))
		g_iamerror.nomapfound = 1;
	i = 1;
	while (result[i] && i < 7)
		i++;
	g_iamerror.mapchecked = i == 7 ? 1 : 0;
	return (i < 7 || !result[8] ? 0 : 1);
}*/

/*
** This function is called only after all obligatory configuration
** parameters have been successfully extracted and an initial
** potentially valid map line has been found in the cub file.
**
** This function calls makemaplist to attempt to extract a valid
** map from the cub file starting from the initial line. It will
** set the g_iamerror.mapchecked flag to true.
**
** If makemaplist is successful, it will return 1. If it fails,
** it will return one of a series of negative numbers. Each
** negative return value of makemaplist corresponds to a specific
** error, which will be printed on the screen as the reason for
** map rejection. All of these errors are fatal, so any of them
** will lead to maphandler returning 0 to signal the calling
** function to terminate the program.
**
** Note that the map is analysed even while it is being copied
** from the file, so errors may be found before the entire
** map has been fully analysed or even copied. As a result, the
** reported error will be the first error encountered, and even
** if corrected there may still be more errors in the rest of
** the map.
*/

int		maphandler(int fd, char *line)
{
	int i;

	i = makemaplist(fd, line);
	if (i < 0)
	{
		if (i == -1)
			g_iamerror.outofbounds[2] = 1;
		else if (i == -2)
			g_iamerror.badmap3line = 1;
		else if (i == -3)
			g_iamerror.noplayer = 1;
		else if (i == -4)
			g_iamerror.toomanyplayers[2] = 1;
		else if (i == -5)
			g_iamerror.maptoobig = 1;
		else if (1 == -7)
			g_iamerror.cubpolice = 1;
		return (0);
	}
	return (1);
}

/*
** This function is called from the main function.
**
** This function handles the cub file. It will take as an
** argument the cub file's path, which must be passed to the
** program upon execution as the first argument. It will
** attempt to open the file, read from it, find the
** configuration parameters, use these to configure the
** appropriate program variables (in the g_config global
** struct), identify and report any mistakes, bad paths,
** or user misconfigurations as errors using the result array,
** and terminate the program if it cannot continue due to an
** error.
**
** It will also find the map, determine where it begins
** and ends, analyse it to determine whether it is valid,
** and create a linked list to store it, and retrieve any
** sprites declared in the map and create another linked
** list to store them.
**
** File analysing functions will be launched in the
** the following order: cubread (file reading function),
** cuberrorhandler (cub file error handling function),
** maphandler (map handling function, including errors
** related to map validity).
**
** If any part of this function fails it will return 0,
** leading to program termination. If it succeeds, it will
** return 1. If it cannot close the file, it will complain
** with a yellow error message, but not terminate the
** program.
**
** NOTE: If sprites are found in the map and a texture path
** could not be found in the cub file, the program will
** abort and throw an invalid sprite path error. If sprites
** were not found, any sprite path error will be ignored.
**
** The original function was written with inverse logic to
** the current one. I inverted the logic to shorten the
** code (Norminette strikes again). I'm leaving a copy of
** the old code, though, for reference, as I find it
** easier to follow. ;) (It's functionally identical).
**
** Please excuse the needless ternaries in the else, again,
** Norminette made me do it. :_( :_(
**
** int		cubhandler(const char *ptr)
** {
**	char	*line;
**	int		fd;
**	int		*result;
**	char	success;
**
**	fd = open(ptr, O_RDONLY, S_IRUSR);
**	success = 1;
**	if (!(result = ft_calloc(9, sizeof(int))) || fd < 3)
**	{
**		if (fd < 0)
**			g_iamerror.cubfilenotfound = 1;
**		else if (fd >= 0)
**			g_iamerror.weirdfd = 1;
**		if (!result)
**			g_iamerror.mallocfail = 1;
**		success = 0;
**		free(result);
**	}
**	else
**	{
**		line = NULL;
**		cubread(result, &line, fd);
**		if (!(cuberrorhandler(result)) || !(maphandler(fd, line)) || \
**		(g_config.spritenum && g_iamerror.getsprfail))
**			success = 0;
**	}
**	if (close(fd) < 0)
**		g_iamerror.couldnotclose = 1;
**	return (success ? 1 : 0);
** }
*/

int		cubhandler(const char *ptr)
{
	char	*line;
	int		fd;
	int		*result;
	int		linenum;
	char	success;

	fd = open(ptr, O_RDONLY, S_IRUSR);
	success = 0;
	if ((result = ft_calloc(9, sizeof(int))) && fd >= 3)
	{
		line = NULL;
		cubread(result, &line, fd, (linenum = 0));
		if ((cuberrorhandler(result)) && (maphandler(fd, line)) && \
		(!g_config.spritenum || !g_iamerror.getsprfail) && !g_iamerror.cubpolice)
			success = 1;
		free(result);
	}
	else
	{
		g_iamerror.cubfilenotfound = fd < 0 ? 1 : g_iamerror.cubfilenotfound;
		g_iamerror.weirdfd = fd >= 0 ? 1 : g_iamerror.weirdfd;
		g_iamerror.mallocfail = !result ? 1 : g_iamerror.mallocfail;
	}
	g_iamerror.couldnotclose = close(fd) < 0 ? 1 : g_iamerror.couldnotclose;
	return (success ? 1 : 0);
}
