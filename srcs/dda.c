/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:57:05 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 15:59:01 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void dda(t_data *game)
{
    game->ray = 0;
    game->vertical_hypotenuse = 0;
    game->horizontal_hypotenuse = 0;
    game->step_x = game->file->player_x;
    game->step_y = game->file->player_y;
    int expected = (int)calculate_distance_to_wall(game);
    int i = 1;
    int last_cathetus;
    while (true)
    {
        printf(BLUE "Checking tile %d: " RESET_COLOR, i++);
        if (is_equal(game->player_angle, M_PI) || is_equal(game->player_angle, M_PI / 2) ||
            is_equal(game->player_angle, 0) || is_equal(game->player_angle, 2 * M_PI) ||
            is_equal(game->player_angle, 3 * M_PI / 2))
        {
            last_cathetus = zero_infinity(game->player_angle, game);
        }
        else
        {
            get_lines(game);
            update_dda(game->horizontal_hypotenuse, game->vertical_hypotenuse, game);
        }
        printf("\n");
        if (check_wall(game->step_y, game->step_x, game))
        {
            if (is_equal(game->player_angle, M_PI) || is_equal(game->player_angle, M_PI / 2))
                game->ray -= last_cathetus;
            // int x = game->step_x / TILE_SIZE;
            else if (game->file->map[game->step_x / TILE_SIZE][game->step_y / TILE_SIZE] == '1')
            {
                update_dda_backward(game->horizontal_hypotenuse, game->vertical_hypotenuse, game);
            }
            break;
        }
    }
    printf(BLUE "\nTotal: " RESET_COLOR);
    printf("Total tiles: %d | ", i - 2);
    printf("Final distance expected: %-6.2d | Final distance counted: %-6.2d\n", expected, (int)game->ray);
    fabs(expected - game->ray) <= 1 ? printf(GREEN "PASSED\n" RESET_COLOR) : printf(RED "FAILED " RESET_COLOR);
    printf("Difference is approx: %d\n", expected - (int)game->ray);
}

void get_lines(t_data *game)
{
    float angle_triangle;
    float rest_triangle;

    angle_triangle = angle(game->player_angle);
    rest_triangle = (M_PI / 2) - angle_triangle;
    game->quadrant = quadrant_of_angle(game->player_angle);
    printf("[Angle %.2f in %d quadrant: %.2f and %.2f]", game->player_angle, game->quadrant, angle_triangle, rest_triangle);
    if (game->quadrant == 1 || game->quadrant == 3)
    {
        horizontal_intersection(game, rest_triangle);
        vertical_intersection(game, angle_triangle);
    }
    else if (game->quadrant == 2 || game->quadrant == 4)
    {
        horizontal_intersection(game, angle_triangle);
        vertical_intersection(game, rest_triangle);
    }
}

void update_dda(float distance_x, float distance_y, t_data *game)
{
    printf(BOLD "\nChecking shortest tile: " RESET_COLOR);
    if (distance_x < distance_y)
    {
        game->ray += distance_x;
        game->step_x = game->horizontal_x;
        game->step_y = game->horizontal_y;
        printf(RED "Shortest hypotenuse is horizontal: %f Counted ray: %f\n" RESET_COLOR, distance_x, game->ray);
    }
    else
    {
        game->ray += distance_y;
        game->step_x = game->vertical_x;
        game->step_y = game->vertical_y;
        printf(GREEN "Shortest hypotenuse is vertical: %f Counted ray: %f\n" RESET_COLOR, distance_y, game->ray);
    }
}

int check_wall(int y, int x, t_data *game)
{
    int array_y;
    int array_x;

    // "111111",
    // "100001",
    // "10P001",
    // "111111"
    // x = 146 / 40 = 5
    // y = 40 / 40 = 1
    printf(RED"test: %c"RESET_COLOR,game->file->map[1][5]);
    printf(GREEN "\n\tCoordinates \n\ty: %d \n \tx: %d\n" RESET_COLOR, y, x);
    // if (game->quadrant == )
    // {
    //     /* code */
    // }

    array_x = x / TILE_SIZE;
    array_y = y / TILE_SIZE;
    printf("arr_x %d\n", array_x);
    printf("arr_y %d\n", array_y);
    // if (game->quadrant == 1 || game->quadrant == 2)
    //     array_y -= 1;
    // if (game->quadrant == 2 || game->quadrant == 3)
    //     array_x -= 1;
    // printf("map[%d][%d]: %c | ", array_y, array_x,
    //        game->file->map[array_x][array_y]);
    printf("map[%d][%d]: %c | ", array_y, array_x,
           'c');
    if (game->file->map[array_y][array_x] && game->file->map[array_y][array_x] == '1')
        return (1);
    return (0);
}