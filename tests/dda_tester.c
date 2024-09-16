/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:29:07 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 23:46:19 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"
#include <stdbool.h>

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
            "10P001",
            "111111",
        };
    printf(RED"test: %c"RESET_COLOR,map[0][5]);
    t_file file;
    file.map = map;
    file.player_x = 100;
    file.player_y = 100;
    file.widthmap = 6; 
    file.heightmap = 4;
    t_data game;
    game.file = &file;
    while(true)
    {
        reset_values(&game);
        printf("input angle:");
        scanf("%f", &game.player_angle);
	    printf(RED"\nTest case Angle: %f\n\n"RESET_COLOR, game.player_angle);
        dda(&game);
    }
}
