#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

int		is_empty(int dir, agent_info_t info);

int		is_up(int col, int player)
{
	int	index = 0;
	int upP0[] = {2, 8, 14, 20, 26};
	int upP1[] = {27, 21, 15, 9, 3};

	while(index < 5)
	{
		if (player == 0)
		{
			if (col == upP0[index])
				return 1;
		}
		else if (player == 1)
		{
			if (col == upP1[index])
				return 1;
		}
		index++;
	}
	return 0;
}

int is_down(int col, int player)
{
	int	index = 0;
	int downP0[] = {5, 11, 17, 23, 29};
	int downP1[] = {24, 18, 12, 6, 0};
	
	while (index < 5)
	{
		if (player == 0)
		{	if (col == downP0[index])
				return 1;
		}
		else if (player == 1)
		{	if (col == downP1[index])
				return 1;
		}
		index++;
	}
	return 0;
}

int		bee_spy(agent_info_t info)
{
	if (info.player == 0)
	{	
		if (info.col == 26 && info.row != 11)
			return is_empty(N, info);
		else if (info.col == 29 && info.row !=14)
			return is_empty(S, info);
		else
		{
			if(info.row == 15)
				return is_empty(W, info);
			else 
				return is_empty(E, info);
		}
	}
	else if (info.player == 1)
	{
		if (info.col == 3 && info.row != 11)
			return is_empty(N, info);
		else if (info.col == 0 && info.row !=14)
			return is_empty(S, info);
		else
		{
			if(info.row == 15)
				return is_empty(E, info);
			else 
				return is_empty(W, info);
		}
	}
		return (0);
}

int		go_around( int dir, agent_info_t info)
{
	
	
	/*
	if (info.bee == 3 || info.bee == 4)
	{
		if (dir == N)
			return is_empty(rand() % 8, info);
		return(is_empty(dir - 1, info));
	}
	else
	{
		if (dir == NE)
			return is_empty(rand() % 8, info);
		return (is_empty(dir + 1, info));
	}*/
	return (0);
}

int		is_empty(int dir, agent_info_t info)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};
	coords_t coords = direction_to_coords(center, dir);
	cell_t next_position = info.cells[coords.row][coords.col];
	if(next_position == EMPTY)
		return dir;
	return go_around(dir, info);
}

int		looking_for_flower(agent_info_t info)
{
	if (info.player == 0)
	{
		if (info.bee == 0)
		{
			if (is_up(info.col, info.player) == 1 && info.row != 1)
			{
				return is_empty(N, info);
			}
			if (is_down(info.col, info.player) == 1 && info.row != 10)
				return is_empty(S, info);
			else 
				return is_empty(E, info);
		}
		else if (info.bee == 1)
		{
			if(info.col < 15)
				return is_empty(E, info);
			if (is_up(info.col, info.player) == 1 && info.row != 1)
				return is_empty(N, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 10)
				return is_empty(S, info);
			else 
				return is_empty(E, info);
		}
		else if(info.bee == 2)
		{
			if (info.col == 25 && info.row != 11)
				return is_empty(N, info);
			else if (info. col == 30 && info.row != 14)
				return is_empty(S, info);
			else
				{
					if(info.row == 14)
						return is_empty(W, info);
					else
						return is_empty(E, info);
				}
		}
		else if (info.bee == 3)
		{
			if(info.col < 15)
				return is_empty(E, info);
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return is_empty(S, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 12)
				return is_empty(N, info);
			else 
				return is_empty(E, info);
		}
		else if (info.bee == 4)
		{
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return is_empty(S, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 12)
				return is_empty(N, info);
			else 
				return is_empty(E, info);
		}
	}
	else if (info.player == 1)
	{
		if (info.bee == 0)
		{
			if (is_up(info.col, info.player) == 1 && info.row != 1)
				return is_empty(N, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 10)
				return is_empty(S, info);
			else 
				return is_empty(W, info);
		}
		else if (info.bee == 1)
		{
			if(info.col > 15)
				return is_empty(W, info);
			if (is_up(info.col, info.player) == 1 && info.row != 1)
				return is_empty(N, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 10)
				return is_empty(S, info);
			else 
				return is_empty(W, info);
		}
		else if(info.bee == 2)
		{
			if (info.col == 4 && info.row != 10)
				return is_empty(N, info);
			else if (info. col == 0 && info.row != 15)
				return is_empty(S, info);
			else
				{
					if(info.row == 14)
						return is_empty(W, info);
					else
						return is_empty(E, info);
				}
		}
		else if (info.bee == 3)
		{
			if(info.col > 15)
				return is_empty(W, info);
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return is_empty(S, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 12)
				return is_empty(N, info);
			else 
				return is_empty(W, info);
		}
		else if (info.bee == 4)
		{
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return is_empty(S, info);
			else if (is_down(info.col, info.player) == 1 && info.row != 12)
				return is_empty(N, info);
			else 
				return is_empty(W, info);
		}
	}
	return (0);
}


int		dispacht_bee(int bee, agent_info_t info)
{
	if (bee == 0 || bee == 1 || bee == 3 || bee == 4)
	{
		return looking_for_flower(info);
	}
	else
		return bee_spy(info);

}

int		go_home(agent_info_t info, int hive_row, int hive_col)
{
	if (info.row == hive_row && info.col > hive_col)
		return W;
	else if (info.row == hive_row && info.col < hive_col)
		return E;
	else if (info.col == hive_col && info.row > hive_row)
		return N;
	else if (info.col == hive_col && info.row < hive_row)
		return S;
	else
	{
		if(info.row < hive_row && info.col > hive_col)
			return SW;
		else if (info.row > hive_row && info.col > hive_col)
			return NW;
		else if (info.row < hive_row && info.col < hive_col)
			return SE;
		else if (info.row > hive_row && info.col < hive_col)
			return NE;
	}
	return (0);
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
/*
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
	int bee_dir = find_neighbour(info,BEE_0);
	if (bee_dir >= 0)
		return go_around(bee_dir);
	bee_dir = find_neighbour(info, BEE_1);
	if (bee_dir >= 0)
		return go_around(bee_dir);
	return (-1);
}

int	flower_on_the_way(agent_info_t info)
{
	int flower_dir = find_neighbour(info, FLOWER);
	if (flower_dir >= 0)
		return go_around(flower_dir);
	return (-1);
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

command_t	attack_other_bee(agent_info_t info)
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
*/
command_t think(agent_info_t info)
{
	int 	hive_col;
	int 	hive_row;

	if (info.player == 1)
	{
		hive_col = 27;
		hive_row = 12;
	}
	else if (info.player == 0)
	{
		hive_col = 2;
		hive_row = 12;
	}
	printf("PLAYER = %d || BEE = %d || TURN = %d || COL = %d || ROW = %D\n", info.player, info.bee, info.turn, info.col, info.row);
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
		{/*
			if(bee_on_the_way(info) >= 0)
			{
				return(command_t){
					.action = MOVE,
					.direction = bee_on_the_way(info)
				};
			}
			else if(flower_on_the_way(info) >= 0)
			{
				return (command_t){
					.action = MOVE,
					.direction = flower_on_the_way(info)
				};
			}
			else
		*/		//{
					int test = is_empty(go_home(info, hive_row, hive_col),info);
					printf("VALEUR DE TEST = %d\n", test);
					return (command_t){
						.action = MOVE,
						.direction = is_empty(go_home(info, hive_row, hive_col),info)
					};
				//}
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
/*	if (bee_on_the_way(info) >= 0 && info.turn > 6)
	{
		return(command_t){
			.action = MOVE,
			.direction = bee_on_the_way(info)
		};
	}
	else
*/	//{
		int MOVE = dispacht_bee(info.bee,info);
		printf("VALEUR DE MOVE = %d\n", MOVE);
    	return (command_t) {
        .action = MOVE,
        .direction = dispacht_bee(info.bee, info)
    	};
	//}
}







int main(int argc, char **argv)
{
    if (argc < 3)
        panic("Usage: ./agent arena_host arena_ip");

    srand(time(NULL) + getpid());

    char *host = argv[1];
    int port = atoi(argv[2]);
    char *team_name = "Framboisier";

    agent_main(host, port, team_name, think);
}
