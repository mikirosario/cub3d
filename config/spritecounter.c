/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecounter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:53:56 by mrosario          #+#    #+#             */
/*   Updated: 2020/09/17 19:06:02 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_imagedata *g_simg[10];

/*
** This function moves the sprite passed as lstmem to the back of the list, and
** redirects the rest of the list to reflect the new ordering. If the sprite is
** already at the back of the list, it will not do anything. Will adapt this
** for use with t_list in libft.
*/

void			ft_movesprttoback(t_spritedata *firstmem, t_spritedata *lstmem)
{
	t_spritedata	*preceding;
	t_spritedata	*proceding;

	if (!lstmem->next)
		return ;
	else if (firstmem == lstmem)
	{
		g_config.spritelist = firstmem->next;
		preceding = firstmem;
		while (preceding->next)
			preceding = preceding->next;
		preceding->next = lstmem;
		lstmem->next = NULL;
		return ;
	}
	proceding = lstmem->next;
	preceding = firstmem;
	while (preceding->next != lstmem)
		preceding = preceding->next;
	preceding->next = proceding;
	while (preceding->next)
		preceding = preceding->next;
	preceding->next = lstmem;
	lstmem->next = NULL;
}

t_spritedata	*ft_sprtlstnew(void const *content)
{
	t_spritedata *tmp;

	tmp = malloc(sizeof(t_spritedata));
	if (tmp)
	{
		tmp->posx = 0;
		tmp->posy = 0;
		tmp->frame = 0;
		tmp->framelimit = 0;
		tmp->spritetype = 0;
		tmp->udiv = 1;
		tmp->vdiv = 1;
		tmp->vmove = 0;
		tmp->remove = 0;
		if (content)
			tmp->texture = (void *)content;
		else
			tmp->texture = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

t_spritedata	*ft_sprtlstlast(t_spritedata *lst)
{
	t_spritedata	*tmp;

	tmp = lst;
	if (!lst)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void			ft_sprtlstadd_back(t_spritedata **alst, t_spritedata *new)
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
** Aquí podemos asignar la textura en función del número en el mapa :)
*/

void			spritecounter(double x, double y, char c)
{
	static t_spritedata *lstptr = NULL;

	g_config.spritenum++;
	if (!g_config.spritelist)
	{
		g_config.spritelist = ft_sprtlstnew((void *)0);
		lstptr = g_config.spritelist;
	}
	else
	{
		ft_sprtlstadd_back(&g_config.spritelist, (ft_sprtlstnew((void *)0)));
		lstptr = lstptr->next;
	}
	lstptr->posx = (double)x + 0.5;
	lstptr->posy = (double)y + 0.5;
	lstptr->spritetype = c;
	lstptr->checkdamage = 0;
	lstptr->life = 6;
	lstptr->hitanimationframes = 0;
}
