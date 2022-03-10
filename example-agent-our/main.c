#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"


int find_neighbour(agent_info_t info, cell_t type);
int pairchecker(int col)
{
	int index = 0;
	int pair[] = {2, 8, 14, 20, 26, 28};

	while(index < 6)
	{
		if (col == pair[index])
			return (1);
		index++;
	}
	return(0);
}

int impairchecker(int col)
{
	int index = 0;
	int impair[] = {5, 11, 17, 23, 29};

	while(index < 5)
	{
		if (col == impair[index])
			return (1);
		index++;
	}
	return(0);
}

int mouvementbee0(agent_info_t li, char side)
{
	if(pairchecker(li.col) == 1 && li.row != 1)
	{
		return (0);
	}
	if(impairchecker(li.col) == 1 && li.row != 11)
	{
		return (4);
	}
	else
	{
		if (side == 'R')
			return(6);
		else
			return (2);
	}
}

int mouvementbee1(agent_info_t li, char side)
{
	if (side == 'L')
	{
		if(li.col < 15)
			return 2;
		else
		{
			if (pairchecker(li.col) == 1 && li.row != 1)
				return 0;
			if (impairchecker(li.col) == 1 && li.row != 11)
				return 4;
			else 
				return 2;
		}
	}
	if( side == 'R')
	{
		if(li.col > 15)
			return 6;
		else
		{
			if (pairchecker(li.col) == 1 && li.row != 1)
				return 0;
			else if (impairchecker(li.col) == 1 && li.row != 11)
				return 4;
			else 
				return 6;
		}
	}
}

int mouvementbee2(agent_info_t li, char side)
{
	if(side == 'L')
	{
		if(li.col ==  25 && li.row != 10)
		{
			return (0);
		}
		else if (li.col == 30 && li.row != 15)
			return (4);
		else
		{
			if (li.row == 15)
				return (6);
			else 
				return(2);
		}
	}
	else
	{
		if (li.col == 4 && li.row != 10)
			return (0);
		else if (li.col == 0 && li.row != 15)
			return (4);
		else
		{
			if (li.row == 15)
				return 2;
			else
				return 6;
		}
	}
}

int mouvementbee3(agent_info_t li,char side)
{
	if (side == 'L')
	{
		if(li.col < 15)
			return 2;
		else
		{
			if (pairchecker(li.col) == 1 && li.row != 23)
				return 4;
			else if (impairchecker(li.col) == 1 && li.row != 14)
				return 0;
			else 
				return 2;
		}
	}
	else if( side == 'R')
	{
		if(li.col > 15)
			return 6;
		else
		{
			if (pairchecker(li.col) == 1 && li.row != 23)
				return 4;
			else if (impairchecker(li.col) == 1 && li.row != 14)
				return 0;
			else 
				return 6;
		}
	}
}

int mouvementbee4(agent_info_t li, char side)
{
	if(pairchecker(li.col) == 1 && li.row != 23)
	{
		return (4);
	}
	else if(impairchecker(li.col) == 1 && li.row != 14)
	{
		return (0);
	}
	else
	{
		if (side == 'R')
			return(6);
		else 
			return(2);
	}
}

int dispachtbee(int bee, agent_info_t li, char side)
{
	if(bee == 0)
	{
		return(mouvementbee0(li, side));
	}
	else if(bee == 1)
	{
		return(mouvementbee1(li, side));
	}
	else if(bee == 2)
	{
		return(mouvementbee2(li, side));
	}
	else if(bee == 3)
	{
		return(mouvementbee3(li, side));
	}
	else if(bee == 4)
	{
		return(mouvementbee4(li, side));
	}
	return (0);
}

int is_bee_block(cell_t cell)
{
			switch(cell)
			{
			case BEE_0:
			case BEE_1:
			case BEE_0_WITH_FLOWER:
			case BEE_1_WITH_FLOWER:
				return 1;
			default:
				return 0;
			}
}

int check_block_other_flower(agent_info_t info)
{
	int block_dir;
	 if((block_dir = find_neighbour(info, FLOWER)) >= 0)
		 return (block_dir);
	 return (-1);
}
int check_block(agent_info_t info)
{
	int block_dir;
	 if((block_dir = find_neighbour(info, BEE_0)) >= 0)
		 return (block_dir);
	 if((block_dir = find_neighbour(info, BEE_1)) >= 0)
		 return (block_dir);
	 return (-1);
}

int	escape_bee(int bee_block, agent_info_t info, char side)
{
	if (bee_block == 2)
		return 1;
	else if (bee_block == 6)
		return 5;
	else if (bee_block == 5)
		return 4;
	else 
	{
		return dispachtbee(info.bee, info, side);
	}
}

int find_neighbour(agent_info_t info, cell_t type)
{
    coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};

    for(int dir = 0 ; dir < 8 ; dir++)
    {
        coords_t coords = direction_to_coords(center, dir);
        cell_t neighbour = info.cells[coords.row][coords.col];
        if (neighbour == type)
        {
            return dir;
        }
    }
    return -1;
}

command_t think(agent_info_t info)
{
	int 	hiverow;
	int 	hivecol;
	char	side;
	int bee_ennemy_with_flower;
	int bee_block;
	int other_flower;

	if (info.col == 27)
	{
		side = 'R';
		hiverow = 13;
		hivecol = 28;
	}
	else if (info.col == 2 )
	{
		side = 'L';
		hiverow = 12;
		hivecol = 2;
	}
	

    cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];

	bee_block = check_block(info);
	if (bee_block >= 0)
	{
		return(command_t){
			.action = MOVE,
			.direction = escape_bee(bee_block,info, side)
		};
	}

	if (info.player == 1)
		 bee_ennemy_with_flower = find_neighbour(info, BEE_0_WITH_FLOWER);
	else
		bee_ennemy_with_flower = find_neighbour(info, BEE_1_WITH_FLOWER);
	if(bee_ennemy_with_flower >= 0)
	{
		return(command_t){
			.action = GUARD,
			.direction = bee_ennemy_with_flower
		};
	}
	
	int	wall_dir = find_neighbour(info, WALL);
	if (wall_dir >= 0)
	{
		return (command_t){
			.action = GUARD,
			.direction = wall_dir
		};
	}

    if (is_bee_with_flower(bee))
    {
        int hive_dir = find_neighbour(info, hive_cell(info.player));
        if (hive_dir >= 0)
        {
            return (command_t) {
                .action = FORAGE,
                .direction = hive_dir
            };
        }
		else
		{
			other_flower = find_neighbour(info, FLOWER);
			if (other_flower >= 0)
				return (command_t){
					.action = MOVE,
					.direction = escape_bee(other_flower, info, side)
				};
				if(info.row == hiverow && info.col > hivecol)
				{
					return(command_t){
						.action = MOVE,
						.direction = 6
					};
				}
				else if (info.row == hiverow && info.col < hivecol)
				{
					return(command_t){
						.action = MOVE,
						.direction = 2
					};
				}
				else if (info.col == hivecol && info.row > hiverow)
				{
					return(command_t){
						.action = MOVE,
						.direction = 0
					};
				}
				else if(info.col == hivecol && info.row < hiverow)
				{
					return(command_t){
						.action = MOVE,
						.direction = 4
					};
				}
				else
				{
					if(info.row < hiverow && info.col > hivecol)
					{
						return(command_t) {
							.action = MOVE,
							.direction = 5 
						};
					}
					else if( info.row > hiverow && info.col > hivecol)
					{
						return(command_t) {
							.action = MOVE,
							.direction = 7
						};
					}
					else if (info.row < hiverow && info.col < hivecol)
					{
						return(command_t) {
							.action = MOVE,
							.direction = 3
						};
					}
					else if (info.row > hiverow && info.col < hivecol)
					{
						return(command_t) {
							.action = MOVE,
							.direction = 1
						};
					}
				}
    	}
	}
    else
    {
        int flower_dir = find_neighbour(info, FLOWER);
        if (flower_dir >= 0)
        {
            return (command_t) {
                .action = FORAGE,
                .direction = flower_dir
            };
        }
    }
	return(command_t){
	.action = MOVE,
	.direction = dispachtbee(info.bee, info, side)
	};
}

int main(int argc, char **argv)
{
    if (argc < 3)
        panic("Usage: ./agent arena_host arena_ip");

    srand(time(NULL) + getpid());

    char *host = argv[1];
    int port = atoi(argv[2]);
    char *team_name = "Les Salopettes";

    agent_main(host, port, team_name, think);
}
