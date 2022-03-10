#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"


int pairchecker(int col)
{
	int index = 0;
	int pair[] = {2, 8, 14, 20, 26};

	while(index < 5)
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
	int impair[] = {5, 11, 17, 23, 27};

	while(index < 5)
	{
		if (col == impair[index])
			return (1);
		index++;
	}
	return(0);
}

int mouvementbee0(agent_info_t li)
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
		return (2);
	}
}

int mouvementbee1(agent_info_t li)
{
	if(li.col < 14)
	{
		return (2);
	}
	else
	{
		if(pairchecker(li.col) == 1 && li.row != 1)
		{
			return (0);
		}
		else if(impairchecker(li.col) == 1 && li.row != 11)
		{
			return (4);
		}
		else
		{
			return(2);
		}
	}
}

int mouvementbee2(agent_info_t li)
{
	if(li.col < 27)
	{
		return (2);
	}
	return (0);
}

int mouvementbee3(agent_info_t li)
{
	if(li.col < 14)
	{
		return (2);
	}
	else
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
			return(2);
		}
	}
}

int mouvementbee4(agent_info_t li)
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
		return(2);
	}
}

int dispachtbee(int bee, agent_info_t li)
{
	if(bee == 0)
	{
		return(mouvementbee0(li));
	}
	else if(bee == 1)
	{
		return(mouvementbee1(li));
	}
	else if(bee == 2)
	{
		return(mouvementbee2(li));
	}
	else if(bee == 3)
	{
		return(mouvementbee3(li));
	}
	else if(bee == 4)
	{
		return(mouvementbee4(li));
	}
	return (0);
}

int is_bee_block(cell_t cell)
{
			switch(cell)
			{
			case BEE_0:
			case BEE_1:
			//case BEE_0_WITH_FLOWER:
			//case BEE_1_WITH_FLOWER:
				return 1;
			default:
				return 0;
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
	int hiverow;
	int hivecol;

	if (info.col == 27)
	{
		hiverow = 13;
		hivecol = 28;
	}
	else
	{
		hiverow = 12;
		hivecol = 2;
	}

    cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	
	printf("VALEUR DE BEE = %d\n", bee);
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
			if(is_bee_block(bee))
			{
				return (command_t){
					.action = MOVE,
					.direction = rand () % 8
				};
			}
			else
			{
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
	if (is_bee_block(bee) && info.turn > 9)
	{
		return (command_t){
			.action = MOVE,
			.direction = rand() % 8
		};

	}
	else
	{
		return(command_t) {
        .action = MOVE,
        .direction = dispachtbee(info.bee, info)
    };
	}
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
