/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecounter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:53:56 by mrosario          #+#    #+#             */
/*   Updated: 2020/08/26 18:28:51 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

extern t_imagedata *g_simg[10];

void			ft_copysprtlst(t_spritedata *copyto, t_spritedata *copyfrom)
{
	int				i;

	while (i < 8)
		copyto->animtex[i] = copyfrom->animtex[i++];
	copyto->frame = copyfrom->frame;
	copyto->framelimit = copyfrom->framelimit;
	copyto->posx = copyfrom->posx;
	copyto->posy = copyfrom->posy;
	copyto->spritetype = copyfrom->spritetype;
	copyto->texture = copyfrom->texture;
	copyto->udiv = copyfrom->udiv;
	copyto->vdiv = copyfrom->vdiv;
	copyto->vmove = copyfrom->vmove;
}

void			ft_movesprttoback(t_spritedata *lstmem)
{
	t_spritedata	tmp;

	ft_copysprtlst(&tmp, lstmem);
	while (lstmem->next)
	{
		ft_copysprtlst(lstmem, lstmem->next);
		lstmem = lstmem->next;
	}
	ft_copysprtlst(lstmem, &tmp);
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
}
