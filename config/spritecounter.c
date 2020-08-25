/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecounter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:53:56 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/25 19:22:59 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

spriteData_t	*ft_sprtlstnew(void const *content)
{
	spriteData_t *tmp;

	tmp = malloc(sizeof(spriteData_t));
	if (tmp)
	{
		tmp->posX = 0;
		tmp->posY = 0;
		if (content)
			tmp->texture = (void *)content;
		else
			tmp->texture = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

spriteData_t	*ft_sprtlstlast(spriteData_t *lst)
{
	spriteData_t	*tmp;

	tmp = lst;
	if (!lst)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void			ft_sprtlstadd_back(spriteData_t **alst, spriteData_t *new)
{
	if (!new)
		return ;
	if (alst && *alst)
	{
		new->next = (ft_sprtlstlast(*alst))->next;
		(ft_sprtlstlast(*alst))->next = new;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}

/*
**  //aquí podemos asignar la textura en función del número en el mapa :)
*/

void			spritecounter(double x, double y, char c)
{
	static spriteData_t *lstptr = NULL;

	g_config.spriteNum++;
	if (!g_config.spriteList)
	{
		g_config.spriteList = ft_sprtlstnew((void *)0);
		lstptr = g_config.spriteList;
	}
	else
	{
		ft_sprtlstadd_back(&g_config.spriteList, (ft_sprtlstnew((void *)0)));
		lstptr = lstptr->next;
	}
	lstptr->posX = (double)x + 0.5;
	lstptr->posY = (double)y + 0.5;
	if (c == '2')
		lstptr->spriteType = '2';
}
