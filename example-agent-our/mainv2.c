#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

int		is_col_even(int col)
{
	int	index = 0;
	int even[] = {2, 8, 14, 20, 26, 28};

	while(index < 6)
	{
		if (col == even[index])
			return 1;
		index++;
	}
	return 0;
}

int is_col_odd(int col)
{
	int	index = 0;
	int odd[] = {5, 11, 17, 23, 29};

	while (index < 5)
	{
		if (col == odd[index])
			return 1;
		index++;
	}
	return 0;
}

int		bee_spy(agent_info_t info, char side)
{
	switch(side)
	{
		case 'L':
			if (info.col == 25 && infi.row != 10)
				return N;
			else if (info.col == 29 && info.row !15)
				return S;
			else
			{
				if(info.row == 15)
					return W;
				else 
					return E;
			}
			break;
		case 'R':
			if (info.col == 4 && info.row != 10)
				return N;
			else if (info.col == 0 && info.row !15)
				return S;
			else
			{
				if(info.row == 15)
					return W;
				else 
					return E;
			}
			break;
		default:
			return (rand() % 8);
	}
}

int		looking_for_flower(agent_info_t info,char side)
{
	switch(side)
	{
		case 'L':
			if(info.bee == 0 || info.bee == 1)
			{
				if (info.bee == 1 && info.col < 15)
					return E;
				if(is_col_even(info.col) == 1 && info.row != 1)
					return N;
				else if (is_col_odd(info.col) == 1 && info.row != 11)
					return S;
				else
					return E;
			}
			else if(info.bee == 3 || info.bee == 4)
			{
				if (info.bee  == 3 && info.col < 15)
					return E;
				if(is_col_even(info.col) == 1 && info.row != 23)
					return S;
				else if (is_col_odd(info.col) == 1 && info.row != 15)
					return N;
				else
					return E;
			}
			break;
		case 'R':
			if(info.bee == 0 || info.bee == 1)
			{
				if (info.bee == 1 && info.col < 15)
					return W;
				if(is_col_even(info.col) == 1 && info.row != 1)
					return N;
				else if (is_col_odd(info.col) == 1 && info.row != 11)
					return S;
				else
					return W;
			}
			else if(info.bee == 3 || info.bee == 4)
			{
				if (info.bee  == 3 && info.col < 15)
					return W;
				if(is_col_even(info.col) == 1 && info.row != 23)
					return S;
				else if (is_col_odd(info.col) == 1 && info.row != 15)
					return N;
				else
					return W;
			}
			break;
		default:
				return (rand() % 8);
	}
}


int		dispacht_bee(int bee, agent_info_t info, char side)
{
	if (bee == 0 || bee == 1 || bee == 3 || bee == 4)
	{
		return looking_for_flower(info, side);
	}
	else
		return bee_spy(info, side);

}

int		go_home(agent_info_t info, int hive_row, int hive_col)
{
	if (info.row == hive_row && info.col > hive_col)
		return W;
	else if (info.row == hive_row && info.col < hive_col)
		return E;
	else if (info.col == hive_col && info.row > hive_row)
		return N;
	else if (info.col == hive.col && info.row < hive_row)
		return S;
	else
	{
		if(info.row < hive_row && info.col > hivecol)
			return SW;
		else if (info.row > hive_row && info.col > hive_col)
			return NW;
		else if (info.row < hive_row && info.col < hive_col)
			return SE;
		else if (info.row > hive_row && info.col < hive_col)
			return NE;
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

int	go_around(int bee_position)
{
	if(bee_position == N)
		return NW;
	else if (bee_position == E)
		return NE;
	else if (bee_position == S)
		return SW;
	else if (bee_position == W)
		return NW;
	else
		return (rand() % 8);

}

int bee_on_the_way(agent_info_t info)
{
	int bee_dir = find_neighbour(info,BBE_0);
	if (bee_dir >= 0)
		return go_around(bee_dir);
	bee_dir = find_neighbour(info, BEE_1);
	if (bee_dir >= 0)
		return go_around(bee_dir);
}

int	flower_on_the_way(agent_info_t info);
{
	int flower_dir = find_neighbour(info, FLOWER);
	if (flower_dir >= 0)
		return go_around(flower_dir);
}

command_t	 wall_on_the_way(agent_info_t info)
{
	int wall_dir = find_neighbour(info, WALL);
	if(wall_dir >= 0)
	{
		return (command_t){
			.action = GUARD,
			.direction = wall_dir
		};
	}
}

command_t	attack_other_bee(info)
{
	int	bee_ennemy;

	if(info.player == 0)
	{
		bee_ennemy = find_neighbour(info, BEE_1_WITH_FLOWER);
		if(bee_ennemy >= 0)
		{
			return (command_t){
				.action = GUARD,
				.direction = bee_ennemy
			};
		}
	}
	if(info.player == 1)
	{
		bee_ennemy = find_neighbour(info, BEE_0_WITH_FLOWER);
		if(bee_ennemy >= 0)
		{
			return(command_t){
				.action = GUARD,
				.direction = bee_ennemy
			};
		}
	}
}

command_t think(agent_info_t info)
{
	int 	hive_col = 2;
	int 	hive_row = 12;
	char	side = 'L';

	if (info.turn == 0 && info.col == 27)
	{
		hive_col = 28;
		hive_row = 12;
		side = 'R';
	}
	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	
    
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
			return (command_t){
				.action = MOVE,
				.direction = go_home(info, hiverow, hivecol)
			};
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
    return (command_t) {
        .action = MOVE,
        .direction = dispacht_bee(info.bee, info, side)
    };
}







int main(int argc, char **argv)
{
    if (argc < 3)
        panic("Usage: ./agent arena_host arena_ip");

    srand(time(NULL) + getpid());

    char *host = argv[1];
    int port = atoi(argv[2]);
    char *team_name = "Les muscles";

    agent_main(host, port, team_name, think);
}
