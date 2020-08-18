/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:37:36 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/18 18:48:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

 
/*
** This function is a generic, run-of-the-mill "free this memory and set the
** pointer to NULL" function that should really be in my libft by now. :p
*/

void			del(void *freeThis)
{
    free(freeThis);
    freeThis = NULL;
}

/*
** This is a little function I've found very useful. It finds the next number
** from thhe position in a string passed as an argument.

** If your pointer is pointing to a number in a string, it will go through the
** number until the end and then go through any non-numerical characters after
** the number until it finds the next number or a NULL. If you're pointing to a
** part of the string that isn't a number, it will of course ignore the first
** while and directly go to the second one to find the next number.

** If it finds another number, it returns a pointer to it, otherwise it returns
** a NULL pointer. Great line saver. ^_^
**
** This is going in my libft.
*/

char			*getnextnum(char *num)
{
	while (*num && ft_isdigit(*num))
		num++;
	while (*num && !(ft_isdigit(*num)))
		num++;
	return (*num ? num : NULL);
}

/*
** This function converts a trgb color value into a hexadecimal color value.
*/

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}