/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:35:50 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/17 00:19:41 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/dda.h"
#include <stdio.h>

int count_tiles_right(t_data *game, int start_x, int start_y)
{
	int count = 0;
	int x = start_x;
	while (x < game->file->widthmap)
	{
		if (game->file->map[start_y][x] == '1')
		{
			printf("Right: Found wall - position map[%d][%d]: %c\n", start_y, x, game->file->map[start_y][x]);
			break;
		}
		count++;
		x++;
	}
	return count;
}

// Function to count tiles to the left
int count_tiles_left(t_data *game, int start_x, int start_y)
{
	int count = 0;
	int x = start_x;
	while (x >= 0)
	{
		if (game->file->map[start_y][x] == '1')
		{
			printf("Left: Found wall - position map[%d][%d]: %c\n", start_y, x, game->file->map[start_y][x]);
			break;
		}
		count++;
		x--;
	}
	return count;
}

// Function to count tiles downwards
int count_tiles_down(t_data *game, int start_x, int start_y)
{
	int count = 0;
	int y = start_y;
	while (y < game->file->heightmap)
	{
		if (game->file->map[y][start_x] == '1')
		{
			printf("Down: Found wall - position map[%d][%d]: %c\n", y, start_x, game->file->map[y][start_x]);
			break;
		}
		count++;
		y++;
	}
	return count;
}

// Function to count tiles upwards
int is_wall_up(t_data *game, int start_x, int start_y)
{
    int y = start_y - 1; // Check the tile directly above
    
    if (y >= 0 && game->file->map[y][start_x] == '1')
    {
        printf("Up: Closest tile is a wall - position map[%d][%d]: %c\n", y, start_x, game->file->map[y][start_x]);
        return 1; // Wall found
    }
    
    printf("Up: Closest tile is not a wall\n");
    return 0; // No wall found
}









static void reset_values(t_data *game)
{
    game->ray = 0;
    game->vertical_hypotenuse = 0;
    game->horizontal_hypotenuse = 0;
    game->horizontal_hypotenuse = 0;
    game->step_x = game->file->player_x;
    game->step_y = game->file->player_y;
    game->vertical_x = 0;
    game->vertical_y = 0;
    game->horizontal_x = 0;
    game->horizontal_y = 0;
    game->quadrant = 0;
    game->file->player_x = 100;
    game->file->player_y = 100;
}


int main()
{
    // Create a dummy map for testing
    char *map[] =
        {
            "111111",
            "100001",
            "11P101",
            "111111",
        };
    t_file file;
    file.map = map;
    file.player_x = 100;
    file.player_y = 100;
	file.heightmap = 4;
	file.widthmap = 6;
    t_data game;
    game.file = &file;

	int x = (int)(game.file->player_x/TILE_SIZE);
	int y = (int)(game.file->player_y/TILE_SIZE);
	// Count in all four directions
	int tiles_right = count_tiles_right(&game, x, y);
	int tiles_left = count_tiles_left(&game, x, y);
	int tiles_down = count_tiles_down(&game, x, y);
	//int tiles_up = count_tiles_up(&game, x, y);

	// Output results
	
	printf("\nx pixels: %d x array position: %d", file.player_x, x);
	printf("\ny pixels: %d y array position: %d\n", file.player_y, y);
	printf("Number of tiles to the right: %d\n", tiles_right);
	printf("Number of tiles to the left: %d\n", tiles_left);
	printf("Number of tiles down: %d\n", tiles_down);
	//printf("Number of tiles up: %d\n", tiles_up);
	printf("Is wall up up: %d\n", is_wall_up(&game, x, y));

	//printf("%d",grid[(int)(y_pixel/TILE_SIZE)][(int)(y_pixel/TILE_SIZE)]);

	return 0;
}