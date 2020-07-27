/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_phase1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:31:22 by mrosario          #+#    #+#             */
/*   Updated: 2020/07/27 20:32:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** This is the function that checks a map line for validity. A line is invalid
** if any character not in the mapchrs string is found, or if the line is empty.
** A line is valid if only mapchrs have been found and the last character seen
** is NULL.
**
** The function runs through the line so long as NULL is not found AND a mapchr
** is found. Spaces ARE considered valid mapchars, but TAB or any similar
** elements are NOT as the way they are displayed is user defined.
**
** If a sprite is found, spriteCounter will be called to record its position
** and place it onto a sprite list called spriteList.
**
** If the line being analysed is the first line (!y) or the last line (endmap)
** and the char found is any of those in the mapchr list from N onward (NnSsEeWw)
** then the whole map will be considered invalid and, after freeing any memory
** that has been reserved, the function will order the calling function to abort.
*/

int		linecheck(char *line, int y, char endmap)
{
	int		x;
	char	*match;
	char	*mapchrs;
	t_list	*listPtr;

	mapchrs = " 012NnSsEeWw";
	x = 0;
	while (line[x] && (match = ft_strchr(mapchrs, line[x]))) //mientras exista un char y sea un mapchar queremos estar dentro de este while y subir i para recorrer la línea. hay que analizar no-mapchr después en su caso
	{
		if (line[x] == '2')
			spriteCounter((double)x, (double)y, line[x]); //si encuentras un sprite, metelo en spriteList y cuentalo          
		//primera o última línea
		if (!y || endmap) //si estamos en primera (y == 0) o última (endmap activado) línea de todas no pueden contener ningún NSEW.
		{
			if (match >= (mapchrs + 4)) //si encuentras al personaje en primera o última linea, mapa inválido, error -1
			{
				if (g_config.spriteList)
					freeSprtList(&g_config.spriteList);
				if (g_config.Map)
					freeList(&g_config.Map);
				return (-1);
			}
		}
		x++;
	}
	if (x > 0 && !line[x]) //si i no es mayor que 0 es línea vacía; si es mayor que cero y hemos llegado a NULL es fin de línea; llegamos a final de línea crea línea nueva de mapList; si es la primera línea a ella, apunta g_config.Map a ella para indizarla
        {
            listPtr = ft_lstnew(((char *)ft_strdup(line)));
            listPtr->len = ft_strlen((const char *)line);
			!y ? g_config.Map = listPtr : ft_lstadd_back(&g_config.Map, listPtr);
        }
	else
		return (0);
	return (x);
}

int     makeMapList(int fd, char *firstLine)
{
	int		x;
	int		y;
	char	*line;
	char	endmap;
	
    int     f;
    char    foundPlayer;
    char    *mapchrs;
    t_list  *listPtr;
    spriteData_t *sprtListPtr;
    char    *tmp;
    t_list  *midLine = NULL;

    y = 0;
    mapchrs = " 012NnSsEeWw";
    endmap = 0;
    foundPlayer = 0;
    while (!endmap)
    {
        if (!y)
            line = firstLine;
        else
            if (!(ft_get_next_line(fd, &line))) // me chiva la última línea... bieeen.
                endmap = 49;
        if (!(x = linecheck(line, y, endmap)))
		{
			y--;
			endmap = 49;
		}
		else if (x == -1)
			return (-1);

        if (y >= 2) //si tenemos al menos 3 líneas buscaremos al jugador (NSEW) en las líneas de en medio, y comprobaremos que sus cuatro vecinos inmediatos son válidos, y comprobaremos que solo hay un jugador
            {
                f = 0;
                if (y == 2)
                    midLine = g_config.Map->next; //la primera línea de en medio es la siguiente a la primera de todas, y se analiza al copiar la tercera línea
                else if (y > 2)
                    midLine = midLine->next; //sucesivamente será la siguiente a la anterior, y se analizará tras copiar la línea siguiente a sí misma
                while (*((char *)(midLine->content + f))) //mientras no sea NULL
                {
                    if ((tmp = ft_strchr(mapchrs, *((char *)(midLine->content + f)))) && tmp > (mapchrs + 3))//si es mapchr y es mapchr de los posteriores a pos 3
                    {
                        if (foundPlayer) //si ya se había encontrado jugador, hay mas de un jugador, mapa inválido
                        {
                            if (g_config.spriteList)
                                freeSprtList(&g_config.spriteList);
                            freeList(&g_config.Map); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                            return (-4);
                        }
                        else if (f == 0 /*si f es NULL no entramos pero weno*/|| *((char *)(midLine->content + f + 1)) == '\0' || *((char *)(midLine->content + f + 1)) == ' ' || *((char *)(midLine->content + f - 1)) == ' ' || (int)(mapListMem(y - 2))->len < f || (int)(mapListMem(y))->len < f ||  mapList(f, y - 2) == ' ' || mapList(f, y) == ' ') //si el jugador está como primer char o último char de línea, o si es contiguo a un espacio, tira todo el mapa, hombre ya
                        {
                            if (g_config.spriteList)
                                freeSprtList(&g_config.spriteList);
                            freeList(&g_config.Map); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
                            return (-1);
                        }
                        foundPlayer = 49; //si encontramos jugador lo reportamos
                        *((char *)(midLine->content + f)) = 'A'; //marcamos pos de jugador como transitable provisional (no se ha comprobado transitabilidad en todo el eje, solo en sus vecinos, lo primero se hace en floodFill)
                        g_player.posX = (double)f + 0.5;//asignamos su posición en eje X a posX inicial del jugador, con un desplazamiento para estar en medio de la casilla
                        g_player.posY = (double)(y - 1) + 0.5; // asignamos su posición en eje Y a posY del jugador. Y es Y - 1 porque y siempre es la posterior a midLine, donde analizamos presencia del jugador para poder mirar arriba y abajo, y nuevamente 0.5 es un offset para llevar al jugador al medio de su casilla.
                        //y aquí asignamos la orientación inicial del jugador en función de su letra N->Norte, S->Sur, E-Este, W-Oeste.
                        if (*tmp == 'N' || *tmp == 'n')
                        {
                            g_player.dirX = (double)-0;
                            g_player.dirY = (double)-1;
                            g_player.planeX = (double)0.66;
                            g_player.planeY = (double)-0;
                        }
                        else if (*tmp == 'S' || *tmp == 's')
                        {
                            g_player.dirX = (double)0;
                            g_player.dirY = (double)1;
                            g_player.planeX = (double)-0.66;
                            g_player.planeY = (double)0;
                        }
                        else if (*tmp == 'E' || *tmp == 'e')
                        {
                            g_player.dirX = (double)1;
                            g_player.dirY = (double)-0;
                            g_player.planeX = (double)0;
                            g_player.planeY = (double)0.66;
                        }
                        else if (*tmp == 'W' || *tmp == 'w')
                        {
                            g_player.dirX = (double)-1;
                            g_player.dirY = (double)0;
                            g_player.planeX = (double)-0;
                            g_player.planeY = (double)-0.66;
                        }
                    }
                    f++;     
                }
            }
        if (!y)
            {
                free(firstLine);
                line = NULL;
            }
        y++;
    }
    g_config.mapH = --y; //Al salir, sea por EOF, pasando por el último y++, o por llegar a línea inválida que debe descontarse, y siempre acaba valiendo uno más que la posición de la última línea del mapa, por lo que debemos restarle uno
    printf("\nmapH Value: %d\n", g_config.mapH);
    listPtr = g_config.Map;
    while (listPtr)
    {
        printf("\n%zu # %s", listPtr->len, listPtr->content);
        listPtr = listPtr->next;
    }
    printf("\nY Value: %d\n", y);
    sprtListPtr = g_config.spriteList;
    int tonti = 1;
    while (sprtListPtr)
    {
        printf("\nSprite %d: X%f, Y%f Sprite Type: %c, Sprite Num %d", tonti, sprtListPtr->posX, sprtListPtr->posY, sprtListPtr->spriteType, g_config.spriteNum);
        sprtListPtr = sprtListPtr->next;
        tonti++;
    }
    //freeList(&g_config.Map);
    if (y < 2) //mapa debe tener al menos tres líneas para ser valido
    {
        if (g_config.Map)
        {
            if (g_config.spriteList)
                freeSprtList(&g_config.spriteList);
            freeList(&g_config.Map); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
            return (-2);
        }
        else
            return (-2);
    }
    if (!foundPlayer) //mapa debe tener un jugador para ser válido
    {
        if (g_config.Map)
        {
            if (g_config.spriteList)
                freeSprtList(&g_config.spriteList);
            freeList(&g_config.Map); //function with lstiter(lst, del) to free content, then while(lst) tmp = lst->next free (lst) lst = tmp to free list members. ugh.
            return (-3);
        }
        else
            return (-3);
    }
    if (floodFill() == -1)
    {
        if (g_config.spriteList)
            freeSprtList(&g_config.spriteList);
        freeList(&g_config.Map);
        return (-1);
    }
    return (1);
}