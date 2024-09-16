/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_tester.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:01:00 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 16:36:46 by ytsyrend         ###   ########.fr       */
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
}


int main()
{
    t_file file;
    file.player_x = 0;
    file.player_y = 0;
    float hor_angle;
	int test_case = 0;
    t_data game;
    game.file = &file;
    while (true)
    {
        reset_values(&game);
		printf(BOLD_GREEN"Input standing position on x: "RESET_COLOR);
		scanf("%d", &game.step_x);
		printf(BOLD_GREEN"Input standing position on y: "RESET_COLOR);
		scanf("%d", &game.step_y);
        printf(BOLD_GREEN "Input player angle (in radians): " RESET_COLOR);
		scanf("%f", &game.player_angle);
        game.quadrant = quadrant_of_angle(game.player_angle);
        if (game.quadrant == 2 || game.quadrant == 4)
        {
            hor_angle = angle(game.player_angle);
        }
        else
        {
            hor_angle = M_PI / 2 - angle(game.player_angle);
        }
        printf("\n" BOLD_BLUE LINE_DECORATION "\n" RESET_COLOR);
        printf(BOLD_RED "Test Case %d:\n" RESET_COLOR, test_case + 1);
        printf(BOLD_GREEN "Player Angle: %.2f Radians\n" RESET_COLOR, game.player_angle);
        printf(BOLD_GREEN "Quadrant: %d\n" RESET_COLOR, game.quadrant);
        printf("\n" BOLD_BLUE "Before Intersection:\n" RESET_COLOR);
        printf("  Step X: %d\n", game.step_x);
        printf("  Step Y: %d\n", game.step_y);
        horizontal_intersection(&game, hor_angle);
        printf("  Hypotenuse: %.2f\n", game.horizontal_hypotenuse);
        printf("\n" BOLD_BLUE "After Intersection:\n" RESET_COLOR);
        printf("  Horizontal Y: %d\n", game.horizontal_y);
        printf("  Horizontal X: %d\n", game.horizontal_x);
        test_case++;
        printf(BOLD_BLUE LINE_DECORATION RESET_COLOR "\n\n");
    }
}