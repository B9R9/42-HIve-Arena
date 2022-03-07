#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

typedef struct s_player0
{
	int	hive_player0_coord[0][1] = {12, 1};
	int	bee0_position[0][1] = {10, 2};
	int	bee1_position[0][1] = {11, 2};
	int	bee2_position[0][1] = {12. 2};
	int	bee3_position[0][1] = {13, 2};
	int	bee4_position[0][1] = {14, 2};
}t_player0;

typedef struct s_player1
{
	int	hive_player1_coord[0][1] = {12, 28};
	int	bee0_position[0][1] = {10, 27};
	int	bee1_position[0][1] = {11, 27};
	int	bee2_position[0][1] = {12. 27};
	int	bee3_position[0][1] = {13, 27};
	int	bee4_position[0][1] = {14, 27};
}t_player1;

typedef struct s_memory
{
	struct	t_player0;
	struct	t_player1;
}t_memory;
/*
typedef 
{
	int	*hive_player1_coord = {12, 28};

}t_bee_memory_player01;
*/
int	bee_mouvement(t_memory li, int hive_dir, info)
{
	if(!hive_dir)
	{
	
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
			printf("Valeur de dir: %d\n", dir);
            return dir;
        }
    }

    return -1;
}

command_t think(agent_info_t info)
{
	t_memory	new;

	printf("Player %d || bee n: %d || turn : %d\n", info.player, info.bee, info.turn);
    
	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	
	printf("Valuer de bee = %d\n", bee);
	printf("Valeur de retour is_bee = %d\n", is_bee_with_flower(bee));
    
	if (is_bee_with_flower(bee))
    {
		printf("Valuer de bee avec fleur = %d\n", bee);
        
		int hive_dir = find_neighbour(info, hive_cell(info.player));
		
		printf("Valeur Hive_dir = %d\n", hive_dir);// return -1
        
		if (hive_dir >= 0)
        {
			printf("=================================================\n");
            return (command_t) {
                .action = FORAGE,
                .direction = hive_dir
            };
        }
    }
    else
    {
        int flower_dir = find_neighbour(info, FLOWER);
		
		printf("Valeur de flower_dir= %d\n", flower_dir);
        
		if (flower_dir >= 0)
        {
			printf("=================================================\n");
            return (command_t) {
                .action = FORAGE,
                .direction = flower_dir
            };
        }
    }
	printf("=================================================\n");
    return (command_t) {
        .action = MOVE,
        .direction = rand() % 8
			/*quel direction prendre quand la bee a une fleur mais pas la ruche
			 * en vison.
			 * comment lla bee bouge pour rechercher une fleur */
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
