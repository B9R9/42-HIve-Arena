#include <stdio.h>
#include <stdlib.h>

//#define UP		2, 8, 14, 20, 26
//#define DOWN		5, 11, 17, 23, 29
int	up[] 	= {2, 8, 14, 20, 26};
int down[]	= {5, 11, 17, 23, 29};


char 	**printposition(int **position, char **map, char c)
{
	map[position[0][0]][position[0][1]] = c;
	return (map);
}

int		upchecker(int colonne)
{
	int	index;

	index = 0;
	while (up[index] != '\0')
	{
		if(colonne == up[index])
			return (1);
		index++;
	}
	return (0);
}

int		downchecker(int colonne)
{
	int index;

	index = 0;
	while (down[index] != '\0')
	{
		if(colonne == down[index])
			return (1);
		index++;
	}
	return(0);
}

int		 **returnhome(int **position, int **home)
{
	if (position[0][0] < home[0][0] && position[0][1] > home[0][1])
	{
		position[0][0] += 1;
		position[0][1] -= 1;
	}
	else if (position [0][0] > home[0][0] && position[0][1] > home[0][1])
	{
		position[0][0] -= 1;
		position[0][0] -= 1;
	}
	else if ( position[0][0] < home[0][0] && position[0][1] < home[0][1])
	{
		position[0][0] += 1;
		position[0][1] += 1;
	}
	else if ( position[0][0] > home[0][0] && position[0][1] < home[0][1])
	{
		position[0][0] -= 1;
		position[0][1] += 1;
	}
	return (position);
}

int		main(void)
{
	int i = 0;
	int x = 0;
	int	**bee_position;
	int	**hive_position;
	int	**home_position;
	int **last_position;
	int	**direction;
	char	**map;
	char	bee = 'B';
	char	hive= 'H';
	char	empty= '.';

	bee_position = (int **)malloc((sizeof(int *) * 1) + 1);
	hive_position = (int **)malloc((sizeof(int *) * 1) + 1);
	home_position = (int **)malloc((sizeof(int *) * 1) + 1);
	last_position = (int **)malloc((sizeof(int *) * 1) + 1);
	direction = (int **)malloc((sizeof(int *) * 1) + 1);
	while (i < 3)
	{
		bee_position[i]= (int *)malloc((sizeof(int) * 2) + 1);
		hive_position[i]= (int *)malloc((sizeof(int) * 2) + 1);
		home_position[i]= (int *)malloc((sizeof(int) * 2) + 1);
		direction[i]= (int *)malloc((sizeof(int) * 2) + 1);
		i++;
	}
	bee_position[0][0] = 12;
	bee_position[0][1] = 2;
	hive_position[0][0] = 12;
	hive_position[0][1] =  1;
	home_position[0][0] = 12;
	home_position[0][1] = 2;
	last_position[0][1] = 0;
	last_position[0][1] = 0;
	direction[0][0] = home_position[0][0];
	direction[0][1] = home_position[0][1];
	i = 0;
	map = (char **)malloc((sizeof(char *) * 25) + 1);
	while ( i < 33)
	{
		map[i] = (char *)malloc((sizeof(char) * 32) + 1);
		i++;
	}
	map[i] = 0;
	i = 0;

	while (i < 26)
	{
		x = 0;
		while(x < 31)
		{
			map[i][x] = '.';
			x++;
		}
		map[i][x] = '\0';
		i++;
	}
	
	map = printposition(hive_position, map, hive);
	while (bee_position[0][1] < 30)
	{
		if (upchecker(bee_position[0][1]) == 1 && bee_position[0][0] != 1)
			bee_position[0][0] -= 1;
		else if (downchecker(bee_position[0][1]) == 1 && bee_position [0][0] != 12)
			bee_position[0][0] += 1;
		else 
			bee_position[0][1] += 1;
		i = 0;
		printposition(bee_position, map,bee);
		sleep(1);
		while(i < 25)
			printf("%s\n", map[i++]);
		map = printposition(bee_position, map, empty);
		printf("\n");
		if (bee_position[0][0] == 2 && bee_position[0][1] == 5)
		{
			last_position[0][0] = bee_position[0][0];
			last_position[0][1] = bee_position[0][1];
			break;
		}
	}

	//while ((bee_position[0][0] != home_position[0][0]) && (bee_position[0][1] != home_position[0][1]))
	while (1)
	{
		if(bee_position[0][0] == direction[0][0] && bee_position[0][1] > direction[0][1])
		{
			bee_position[0][1] -= 1;
		}
		else if(bee_position[0][0] == direction[0][0] && bee_position[0][1] < direction[0][1])
		{
			bee_position[0][1] += 1;
		}
		else if (bee_position[0][1] == direction[0][1] && bee_position[0][0] > direction[0][0])
		{
			bee_position[0][0] -= 1;
		}
		else if (bee_position[0][1] == direction[0][1] && bee_position[0][0] < direction[0][0])
		{
			bee_position[0][0] += 1;
		}
		else
		{
			bee_position = returnhome(bee_position, direction);
		}
		printposition(bee_position, map,bee);
		sleep(1);
		i = 0;
		while(i < 25)
		{
			printf("%s\n", map[i++]);
		}
		map = printposition(bee_position, map, empty);
		printf("\n");
		if ((bee_position[0][0] == home_position[0][0] && bee_position[0][1] == home_position[0][1]))
		{
			direction[0][0] = last_position[0][0];
			direction[0][1] = last_position[0][1];
		}
		

	}
	return (0);
}