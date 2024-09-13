#include "include.h"
#include <stdbool.h>

static void reset_values(t_data *game)
{
	game->ray = 0;
    game->vertical_hypotenuse = 0;
    game->horizontal_hypotenuse = 0;
    game->step_x = game->file->player_x;
    game->step_y = game->file->player_y;
}

int main()
{
    // Create a dummy map for testing
    char *map[] = 
	{
        "11111111111",
        "10000000001",
        "1000P000001",
        "11111111111"
    };

    t_file file;
    file.map = map;
    file.player_x = 4 * TILE_SIZE + TILE_SIZE/2;
    file.player_y = 2 * TILE_SIZE + TILE_SIZE/2;

    t_data game;
    game.file = &file;

/************** TEST CASE 1 *****************/

	reset_values(&game);
	game.player_angle = 0;
	printf(BOLD_GREY"\nTest case 1: 0 Radian (x coordinate +)\n\n"RESET_COLOR);
    dda(&game);

/************** TEST CASE 2 *****************/

	reset_values(&game);
	game.player_angle = M_PI;
	printf(BOLD_GREY"\nTest case 2: M_PI Radian (x coordinate -)\n\n"RESET_COLOR);
    dda(&game);

/************** TEST CASE 3 *****************/

	reset_values(&game);
	game.player_angle = M_PI/2;
	printf(BOLD_GREY"\nTest case 3: M_PI/2 Radian (y coordinate +)\n\n"RESET_COLOR);
    dda(&game);

/************** TEST CASE 4 *****************/

	reset_values(&game);
	game.player_angle = 3 * M_PI/2;
	printf(BOLD_GREY"\nTest case 4: 3M_PI/2 Radian (y coordinate -)\n\n"RESET_COLOR);
    dda(&game);

    return 0;
}
