#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"


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

	printf("Player %d || bee n: %d || turn : %d\n", info.player, info.bee, info.turn);
   printf("Row %d || col: %d\n", info.row, info.col); 
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
