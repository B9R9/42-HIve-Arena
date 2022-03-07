#include <stdio.h>
#include <stdlib.h>


char 	**printposition(int position[0][2], char **map)
{
	map[position[0][0]][position[0][1]] = 'B';
	return (map);
}

int		main(void)
{
	int i = 0;
	int x = 0;
	int bee_position[1][2] = {12, 1};
	char	**map;

	map = (char **)malloc((sizeof(char *) * 25) + 1);
	while ( i < 33)
	{
		map[i] = (char *)malloc((sizeof(char) * 32) + 1);
		i++;
	}
	map[i] = 0;
	i = 0;

	while (i < 25)
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
	
	printf("TEST\n");
	while (1)
	{
		if (bee_position[0][0] != 1)
		{
			bee_position[0][0] -= 1;
		}
		else if (( bee_position[0][1] == 5 || bee_position[0][1] == 10 || bee_position[0][1] == 15 || bee_position[0][1] == 20 ) && (bee_position[0][0] == 1))
		{
			bee_position[0][0] +=1;
		}
		else if (bee_position[0][0]  == 1)
		{
			bee_position[0][1] += 1;
		}
		printposition(bee_position, map);
		i = 0;
		while(i < 25)
			printf("%s\n", map[i++]);
		printf("\n");
	}

	return (0);
}