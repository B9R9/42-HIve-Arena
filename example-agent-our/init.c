/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:02:29 by briffard          #+#    #+#             */
/*   Updated: 2022/03/08 14:23:58 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ia.h"

static	int		**memoryalloc(int **arr);
static	char	**mapinit(char **map);
static	void	panicattack(char *str);

static	void	panicattack(char *str)
{
	write(2, str, strlen(str));
	exit(EXIT_FAILURE);
}

static	int ** memoryalloc(int **arr, int line, int colone)
{
	int i;

	i = 0;
	arr = (int **)malloc((sizeof(int *) * line ) + 1);
	if (!arr)
		panicattack("Error:\nIn init.c: Line 17\nError: allocation memory\n");
	while(i < 3)
	{
		arr[i] = (int *)malloc((sizeof(int) * colone ) + 1);
		if (!arr[i])
			panicattack("Error:\nIn init.c: Line 25\nError: allocation memory\n");
		i++;
	}
		return (arr);
}

static char	**mapinit(char **map)
{
	int i;

	i = 0;
	map = (char **)malloc((sizeof(char *) * 25) + 1);
	if(!map)
		panicattack("Error:\nIn init.c: Line 36\nError: allocation memory\n");
	while (i < 31)
	{
		map[i] = (char *)malloc( (sizeof(char) * 30) + 1);
		if (!map[i])
			panicattack("Error:\nIn init.c: Line 25\nError: allocation memory\n");
		i++;
	}
	i = 0;
	while (i < 26)
	{
		x = 0;
		while (x < 31)
		{
			map[i][x] = '.';
			x++;
		}
		map[i][x] = '\0';
		i++;
	}
	return (map);
}

t_brain		braininit(t_brain li)
{
	li.home = memoryalloc(li.home, 1, 2);
	li.hive_position = memoryalloc(li.hive_poistion, 1 , 2);
	li.map = mapinit(li.map);
	return (li);
}

t_brain		setup(agent_info_t info, t_brain li)
{

	li.hive_position[0][0] = 12;
	li.home[0][0] = 12

	if(info.player == 0)
	{
		li.hive_position[0][1] = 1;
		li.home[0][1] = 2
	}
	else
	{
		li.hive_position[0][1] = 29;
		li.home[0][1] = 28
	}
	return (li);
}

/*==========================================================================*/

t_membee	beeinit(agent_info_t li, t_membee bee)
{
	int	i;
	int line;

	line = 10;
	i = 0;
	if (li.player == 0)
		colone = 2;
	else 
		colone = 28;
	bee.last_positionbee = memoryalloc(bee.last_positionbee,6 , 2);
	while (i < 6)
	{
		bee.last_positionbee[i][0] = line ;
		bee.last_positionbee[i][1] = colone;
		i++;
		line++;
	}
	return (bee);
}
