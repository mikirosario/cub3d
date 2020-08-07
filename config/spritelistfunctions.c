/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritelistfunctions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:47:39 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/05 17:31:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			freesprtlist(spriteData_t **alst)
{
	spriteData_t *tmp;

	while (*alst)
	{
		tmp = (&(**alst))->next;
		free(*alst);
		*alst = tmp;
	}
}

spriteData_t	*spriteiter(int listmember)
{
	spriteData_t	*ptr;
	int				i;

	i = 0;
	ptr = g_config.spriteList;
	while (i++ < listmember)
		ptr = ptr->next;
	return (ptr);
}
