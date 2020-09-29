/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritelistfunctions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:47:39 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/27 11:21:07 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void			freesprtlist(t_spritedata **alst)
{
	t_spritedata *tmp;

	while (*alst)
	{
		tmp = (&(**alst))->next;
		free(*alst);
		*alst = tmp;
	}
}

t_spritedata	*spriteiter(int listmember)
{
	t_spritedata	*ptr;
	int				i;

	i = 0;
	ptr = g_config.spritelist;
	while (i++ < listmember)
		ptr = ptr->next;
	return (ptr);
}
