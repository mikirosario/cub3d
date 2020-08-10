/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maplistfunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:42:19 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/10 17:34:19 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** This function analyses a line. If the entire line consists of mapchars,
** it returns 1 to validate it as a mapline. If it finds a non-mapchar in
** the line or the line is empty, it returns 0 to reject it.
**
** The mapchrs list should really be defined in cubhandler function (cub.c)
** and sent to this function via the maphandler function, as well as to
** the makemaplist function, also from there. This way it would only have to be
** defined once. But... Norminette. WE'LL SEE!
*/

int		ismap(char *line)
{
	int		i;
	char	*tmp;
	char	*mapchrs;

	i = 0;
	mapchrs = " 012NnSsEeWw";
	while (line[i] && (tmp = ft_strchr(mapchrs, line[i])))
		i++;
	if (i > 0 && !line[i])
		return (1);
	else
		return (0);
}

/*
** This function takes a pointer to a t_list pointer as an argument. It
** iterates through every member of the t_list and frees the memory occupied
** by the strings in each list member using the ft_lstiter function to
** iterate and sending it the del function to free the linked content. It then
** iterates through the list again, this time freeing the memory occupied by
** each list member.
*/

void	freelist(t_list **alst)
{
	t_list *tmp;

	ft_lstiter(*alst, del);
	while (*alst)
	{
		tmp = (&(**alst))->next;
		free(*alst);
		*alst = tmp;
	}
}

/*
** This function takes a y coordinate as an argument and finds the member of
** the linked map list that links to the corresponding map string. It then
** returns the address of that map list member.
*/

t_list	*maplistmem(unsigned int y)
{
	t_list			*ptr;
	unsigned int	i;

	i = 0;
	ptr = g_config.Map;
	while (ptr && i++ < y)
		ptr = ptr->next;
	if (!ptr)
		return (0);
	return (ptr);
}

/*
** This function takes x, y coordinates as arguments and finds the position of
** x in the map string linked by map list member number y. It then returns the
** address of the character at that location.
*/

char	*maplistdir(unsigned int x, unsigned int y)
{
	t_list			*ptr;
	unsigned int	i;

	i = 0;
	ptr = g_config.Map;
	while (ptr && i++ < y)
		ptr = ptr->next;
	if (!ptr)
		return (0);
	return (((char *)(ptr->content + x)));
}

/*
** This function takes x, y coordinates as arguments and finds the position of
** x in the map string linked by map list member number y. It then returns the
** the character at that location.
*/

char	maplist(unsigned int x, unsigned int y)
{
	t_list			*ptr;
	unsigned int	i;

	i = 0;
	ptr = g_config.Map;
	while (i++ < y)
		ptr = ptr->next;
	return (*((char *)(ptr->content + x)));
}
