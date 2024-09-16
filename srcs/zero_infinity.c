/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_infinity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:56:13 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 15:50:55 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

int count_boundary(bool positive, int step)
{
    int boundary;

    boundary = 0;
    if (positive)
        boundary = ((step / TILE_SIZE) + 1) * TILE_SIZE;
    else if (!positive)
    {
        if (step % TILE_SIZE == 0) /* když  nestojí uprostřed */
            boundary = ((step / TILE_SIZE) - 1) * TILE_SIZE;
        else
            boundary = ((step / TILE_SIZE)) * TILE_SIZE;
    }
    return (boundary);
}


/* returns cathetus */
int zero_infinity(float angle, t_data *game)
{
    int boundary;
    int cathetus;
    if (is_equal(angle, M_PI / 2))
    {
        boundary = count_boundary(false, game->step_y);
        cathetus = game->step_y - boundary;
        printf("Step position: %d  | ", game->step_y);
        game->step_y = boundary;
    }
    else if (is_equal(angle, 0) || is_equal(angle, 2 * M_PI))
    {
        boundary = count_boundary(true, game->step_x);
        cathetus = boundary - game->step_x;
        printf("Step position: %d  | ", game->step_x);
        game->step_x = boundary;
    }
    else if (is_equal(angle, M_PI))
    {
        boundary = count_boundary(false, game->step_x);
        cathetus = game->step_x - boundary;
        printf("Step position: %d  | ", game->step_x);
        game->step_x = boundary;
    }
    else
    {
        boundary = count_boundary(true, game->step_y);
        cathetus = boundary - game->step_y;
        printf("Step position: %d  | ", game->step_y);
        game->step_y = boundary;
    }
    game->ray += cathetus;
    printf("Boundary: %d | Cathetus: %d | Counted ray: %d | ", boundary, cathetus, (int)game->ray);
    return (cathetus);
}



/* funkce pro aktualizaci delky paprsku */
void update_dda_backward(float distance_x, float distance_y, t_data *game)
{
    printf("Minus one tile");
    // podminka, kdy se nema odecitat
    // if(game->file->map[int(game->step_x/TILE_SIZE)][int(game->step_y/TILE_SIZE)]=='1')
    // {
        
    // }
    // if (game->quadrant == 3)
    //     return ;
    // if (game->quadrant == 1 || game->quadrant == 2)
    //         if (distance_x < distance_y)
    //             {
    //                 game->ray -= distance_x;
    //             }
    // if (game->quadrant == 2 || game->quadrant == 3)
    //     if (distance_x > distance_y)
    //         {
    //             game->ray -= distance_y;
    //         }

    if (distance_x < distance_y)
    {
        game->ray -= distance_x;
    }
    else
    {
        game->ray -= distance_y;
    }
}