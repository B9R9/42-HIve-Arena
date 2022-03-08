/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:33:51 by briffard          #+#    #+#             */
/*   Updated: 2022/03/08 14:23:52 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IA_H
# define IA_H


/*INCLUDE*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*CONST VARIABLE*/
int	up[]	= {2, 8, 14, 20, 26};
int	down[]	= {5, 11, 17, 23, 29};

typedef struct	s_membee
{
	int	**last_positionbee;
}				t_membee;

typedef struct	s_brain
{
	char	**map;
	int		**hive_position;
	int		**home;
}t_brain;

/*PROTOTYPE*/
t_brain			braininit( t_brain li);
t_brain			setup(agent_info_t info, t_brain li);

t_membee		beeinit(agent_info_t info,t_membee li);

command_t		bee0();
command_t		bee4();

void		panicattack(char *str);/ afaire 

