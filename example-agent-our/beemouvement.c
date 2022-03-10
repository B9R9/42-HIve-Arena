/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beemouvement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:05:17 by briffard          #+#    #+#             */
/*   Updated: 2022/03/09 13:54:26 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ia.h"

int	pairchecker(int col)
{
	int	index;
	int	pair[] = {2, 8, 14, 20, 26};

	index = 0;
	while(pair[index] != '\0')
	{
		if (col == pair[index])
			return (1);
		index++;
	}
		return (0);
}

int	impairchecker(int col)
{
	int index;
	int	impair[] = {5, 11, 17, 23, 29};
	
	index = 0;
	while (impair[index] != '\0')
	{
		if (col == impair[index])
			return (1);
		index++;
	}
	return (0);
}

int	mouvementbee0(agent_info_t li)
{

	if(pairchecker(li.col) == 1 && li.row != 1)
	{
		return(0)
	}
	else if(impairchecker(li.col) && li.row != 12)
	{
		/*
		return(command_t) {
			.action = MOVE,
			.direction = S };*/
		return(4);
	}
	else
	{
		/*
		return (command_t) {
				.action = MOVE,
				.direction = E
				};
				*/
		return (2);
	}
}

int	mouvementbee1(agent_info_t li)
{
	if(li.col < 14)
	{/*
		return(command_t){
		.action = MOVE,
		.direction = E
		};
		*/
		return (2);
	}
	else
	{
		if(pairchecker(li.col) == 1 && li.row != 1)
		{/*
			return(command_t) {
			.action = MOVE,
			.direction = N };
			*/
			return (0);
		}
		else if(impairchecker(li.col) && li.row != 12)
		{/*
			return(command_t) {
				.action = MOVE,
				.direction = S };
				*/
			return (4);
		}
		else
		{/*
			return (command_t) {
				.action = MOVE,
				.direction = E
				};
				*/
			return (2);
		}
	}
}

int	mouvementbee2(agent_info_t li)
{
	if(li.col < 27)
	{/*
		return (command_t){
			.action = MOVE,
			.direction = E
		};
		*/
		return (2);
	}

}

int	mouvementbee3(agent_info_t li)
{

	if(li.col < 14)
	{/*
		return(command_t){
		.action = MOVE,
		.direction = E
		};
		*/
		return (2);
	}
	else
	{
		if(pairchecker(li.col) == 1 && li.row != 12)
		{/*
			return(command_t) {
			.action = MOVE,
			.direction = S };
			*/
			return (4);
		}
		else if(impairchecker(li.col) && li.row != 1)
		{/*
			return(command_t) {
				.action = MOVE,
				.direction = N };
				*/
			return (0);
		}
		else
		{/*
			return (command_t) {
					.action = MOVE,
					.direction = E
					};
					*/
			return (2);
		}
	}
}

int	mouvementbee4(agent_info_t li)
{

	if(pairchecker(li.col) == 1 && li.row != 12)
	{/*
		return(command_t) {
		.action = MOVE,
		.direction = S };*/
		return (4);
	}
	else if(impairchecker(li.col) && li.row != 1)
	{/*
		return(command_t) {
			.action = MOVE,
			.direction = N };*/
		return (0);
	}
	else
	{/*
		return (command_t) {
				.action = MOVE,
				.direction = E
				};*/
		return (2);
	}
}