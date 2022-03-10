/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:33:51 by briffard          #+#    #+#             */
/*   Updated: 2022/03/09 12:08:42 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IA_H
# define IA_H


/*INCLUDE*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "agent.h"

/*CONST VARIABLE*/
//int	up[]	= {2, 8, 14, 20, 26};
//int	down[]	= {5, 11, 17, 23, 29};

typedef struct	s_membee
{
	int	**last_positionbee;
}				*t_membee;

typedef struct	s_brain
{
	//char	**map;// pas besoin
	int		**hive_position;
	int		**home;
}				*t_brain;

/*ARRAY TO POINTER FUNCTION*/
/*FUNCTION*/
int		mouvementbee0(agent_info_t li);
int		mouvementbee1(agent_info_t li);
int		mouvementbee2(agent_info_t li);
int		mouvementbee3(agent_info_t li);
int		mouvementbee4(agent_info_t li);

typedef int	(*funcArray)(agent_info_t li);
static const funcArray mouvementbeefunc[5] = {
	mouvementbee0,
	mouvementbee1,
	mouvementbee2,
	mouvementbee3,
	mouvementbee4,
};

/*PROTOTYPE*/
/*t_brain			puttonull(void);
t_brain			braininit( t_brain li);
t_brain			setup(agent_info_t info, t_brain li);

t_membee		toNull(void);
t_membee		beeinit(agent_info_t info,t_membee li);


void		panicattack(char *str);// afaire 
*/
# endif
