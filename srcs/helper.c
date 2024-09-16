/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:54:18 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 12:00:56 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool is_equal(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

float calculate_distance_to_wall(t_data *game)
{
    int j = 0;
    double distance = 0;

    while (1)
    {
        int x = game->file->player_x + cos(game->player_angle) * j;
        int y = game->file->player_y - sin(game->player_angle) * j; // Invert y
        int map_x = x / TILE_SIZE;
        int map_y = y / TILE_SIZE;
        if (game->file->map[map_y][map_x] == '1')
        {
            distance = sqrt(pow(x - game->file->player_x, 2) + pow(y - game->file->player_y, 2));
            return distance;
        }
        j++;
    }
}

float angle(float angle_player)
{
    while (angle_player > M_PI / 2)
        angle_player -= M_PI / 2;
    return (angle_player);
}

int quadrant_of_angle(float angle_player)
{
    return ((int)(angle_player / (M_PI / 2)) + 1);
}