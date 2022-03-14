#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

int		is_empty(int dir, agent_info_t info);
int		bee2_move(agent_info_t info);
int		is_up(int col, int player);
int 	s_down(int col, int player);
int		bee_spy(agent_info_t info);
int		looking_for_flower(agent_info_t info);
int		dispacht_bee(int bee, agent_info_t info);
int		go_home(agent_info_t info, int hive_row, int hive_col);
int 	find_neighbour(agent_info_t info, cell_t type);


/*looking for colum to go up*/
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

/*looking for column to go down*/
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

/*check if the next direction is empty*/
int		is_empty(int dir, agent_info_t info)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};
	coords_t coords = direction_to_coords(center, dir);
	cell_t next_position = info.cells[coords.row][coords.col];
	if(next_position == EMPTY)
		return dir;
	else
	{
		if (info.bee == 3 || info.bee == 4)
		{
			while (next_position != EMPTY)
				{
					dir -= 1;
					if (dir == -1)
						dir  = 7;
					coords = direction_to_coords(center,dir);
					next_position = info.cells[coords.row][coords.col];
					if(next_position == EMPTY)
						return dir;
				}
		}
		else
		{
			while (next_position != EMPTY)
			{
				dir += 1;
				if (dir == 8)
					dir = 0;
				coords = direction_to_coords(center,dir);
				next_position = info.cells[coords.row][coords.col];
				if (next_position == EMPTY)
					return dir;
			}
		}
	}
}

/*Movement of our bee*/
int		looking_for_flower(agent_info_t info)
{
	if (info.player == 0)
	{
		if (info.bee == 0)
		{
			if(info.col > 20)
				return is_empty(bee2_move(info),info);
			if (info.row > 10 && is_down(info.col, info.player) == 1)
				return N;
			if (is_up(info.col, info.player) == 1 && info.row != 0)
				return N;
			if (is_down(info.col, info.player) == 1 && info.row != 10)
				return S;
			else 
				return E;
		}
		else if (info.bee == 1)
		{
			
			if (info.row > 11 && is_down(info.col, info.player) == 1)
				return N;
			else if(info.col < 9)
				return E;
			else if (info.col > 20)
				return (is_empty(bee2_move(info),info));
			if (is_up(info.col, info.player) == 1 && info.row != 0)
				return N;
			else if (is_down(info.col, info.player) == 1 && info.row != 11)
				return S;
			else 
				return E;
		}
		else if(info.bee == 2)
		{
			if (info.col == 25 && info.row != 11)
				return N;
			else if (info. col == 30 && info.row != 14)
				return S;
			else
				{
					if(info.row == 14)
						return W;
					else
						return E;
				}
		}
		else if (info.bee == 3)
		{
			if(info.col > 20)
				return is_empty(bee2_move(info),info);
			if (info.row < 13 && is_up(info.col, info.player) == 1)
				return S;
			if(info.col < 9)
				return E;
			if (is_up(info.col, info.player) == 1 && info.row != 24)
				return S;
			else if (is_down(info.col, info.player) == 1 && info.row != 13)
				return N;
			else 
				return E;
		}
		else if (info.bee == 4)
		{
			if(info.col > 20)
				return is_empty(bee2_move(info),info);
			if (info.row < 13 && is_up(info.col, info.player) == 1)
				return S;
			if (is_up(info.col, info.player) == 1 && info.row != 24)
				return S;
			else if (is_down(info.col, info.player) == 1 && info.row != 13)
				return N;
			else 
				return E;
		}
	}
	else if (info.player == 1)
	{
		if (info.bee == 0)
		{
			if(info.col < 10)
				return is_empty(bee2_move(info),info);
			if (info.row > 10 && is_down(info.col, info.player) == 1)
				return N;
			if (is_up(info.col, info.player) == 1 && info.row != 1)
				return N;
			else if (is_down(info.col, info.player) == 1 && info.row != 10)
				return S;
			else 
				return W;
		}
		else if (info.bee == 1)
		{
			if(info.col < 10)
				return is_empty(bee2_move(info),info);
			if (info.row > 11 && is_down(info.col, info.player) == 1)
				return N;
			if(info.col > 22)
				return W;
			if (is_up(info.col, info.player) == 1 && info.row != 1)
				return N;
			else if (is_down(info.col, info.player) == 1 && info.row != 11)
				return S;
			else 
				return W;
		}
		else if(info.bee == 2)
		{
			if (info.col == 4 && info.row != 10)
				return N;
			else if (info. col == 0 && info.row != 15)
				return S;
			else
				{
					if(info.row == 14)
						return W;
					else
						return E;
				}
		}
		else if (info.bee == 3)
		{
			if(info.col < 10)
				return is_empty(bee2_move(info),info);
			if (info.row < 13 && is_up(info.col, info.player) == 1)
				return S;
			if(info.col > 17)
				return W;
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return S;
			else if (is_down(info.col, info.player) == 1 && info.row != 13)
				return N;
			else 
				return W;
		}
		else if (info.bee == 4)
		{
			if(info.col < 10)
				return is_empty(bee2_move(info),info);
			if (info.row < 13 && is_up(info.col, info.player) == 1)
				return S;
			if (is_up(info.col, info.player) == 1 && info.row != 23)
				return S;
			else if (is_down(info.col, info.player) == 1 && info.row > 13)
				return N;
			else 
				return W;
		}
	}
	return (0);
}

/*Dont need it but we are lazzy*/

int		dispacht_bee(int bee, agent_info_t info)
{
	if (bee == 0 || bee == 1 || bee == 3 || bee == 4 || bee == 2)
		return looking_for_flower(info);

}

/*Mouvement to go baack to the Hive*/
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

/*Check direction aroud center*/

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

/*mouvment for the bee 2*/
int	bee2_move(agent_info_t info)
{
	if(info.player == 0)
	{
		 if (info.col == 26 && info.row < 13)
			return S;
		 else if (info.col == 29 && info.row > 10)
			 return N;
		 else if (info.row == 10 && info.col > 26)
			 return W;
		 else
			 return E;
	}
	else if (info.player == 1)
	{
		if (info.col == 3 && info.row < 13)
			return S;
		else if (info.col == 0 && info.row > 10)
			return N;
		else if (info.row == 10 && info.col < 3)
			return E;
		else
			return W;
	}
}

command_t think(agent_info_t info)
{
	int 	hive_col;
	int 	hive_row;
	int 	attack_col;
	int		attack_row;
	int		wall_dir;

	if (info.player == 1)
	{
		hive_col = 27;
		hive_row = 12;
		attack_col = 5;
		attack_row = 13;
	}
	else if (info.player == 0)
	{
		hive_col = 2;
		hive_row = 12;
		attack_col = 29;
		attack_row = 10;
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
			wall_dir = find_neighbour(info, WALL);
			if(wall_dir >= 0)
			{
				return(command_t){
					.action = GUARD,
					.direction = wall_dir
				};
			}
			else
			{
				return (command_t){
					.action = MOVE,
					.direction = is_empty(go_home(info, hive_row, hive_col), info)
					};
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
	wall_dir = find_neighbour(info, WALL);
	if (wall_dir >= 0)
	{
		return (command_t){
			.action = GUARD,
			.direction = wall_dir
		};
	}
	else
	{
		if (info.bee == 2)
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
			else if(info.player == 1)
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
			return (command_t){
				.action = MOVE,
				.direction = is_empty(bee2_move(info), info)
				};
		}
		else
		{
			return (command_t) {
        		.action = MOVE,
        		.direction = is_empty(dispacht_bee(info.bee, info), info)
    		};
		}
	}
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
