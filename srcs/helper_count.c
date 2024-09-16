/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:35:50 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/17 01:29:25 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/dda.h"
#include <stdio.h>


int is_wall_left(t_data *game, int start_x, int start_y)
{
    int x = start_x - 1; // Check the tile directly to the left
    
    if (x >= 0 && game->file->map[start_y][x] == '1')
    {
        printf("Left: Closest tile is a wall - position map[%d][%d]: %c\n", start_y, x, game->file->map[start_y][x]);
        return 1; // Wall found
    }
    
    printf("Left: Closest tile is not a wall\n");
    return 0; // No wall found
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

int is_wall_right(t_data *game, int start_x, int start_y)
{
    int x = start_x + 1; // Check the tile directly to the right
    
    if (x < game->file->widthmap && game->file->map[start_y][x] == '1')
    {
        printf("Right: Closest tile is a wall - position map[%d][%d]: %c\n", start_y, x, game->file->map[start_y][x]);
        return 1; // Wall found
    }
    
    printf("Right: Closest tile is not a wall\n");
    return 0; // No wall found
}