/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:01:08 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/09/16 13:31:05 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define EPSILON 1e-6

#define TILE_SIZE 40
#define RESET_COLOR "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define BOLD "\x1b[1m"
#define YELLOW "\e[0;33m"
#define BOLD_GREY "\033[1;30m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_RED "\033[1;31m"
#define LINE_DECORATION "------------------------------------------"

// Placeholder for game data structure
typedef struct s_file
{
    char **map;
    int player_x;
    int player_y;
} t_file;

typedef struct s_data
{
    float player_angle;
    float ray;
    float vertical_hypotenuse;
    float horizontal_hypotenuse;
    int step_x;
    int step_y;
    int horizontal_x;
    int horizontal_y;
    int vertical_x;
    int vertical_y;
    int quadrant;
    t_file *file;
} t_data;

// Functions provided above
int count_boundary(bool positive, int step);
int check_wall(int y, int x, t_data *game);
float angle(float angle_player);
int zero_infinity(float angle, t_data *game);
void get_lines(t_data *game);
void dda(t_data *game);
void update_dda(float distance_x, float distance_y, t_data *game);
float calculate_distance_to_wall(t_data *game);
bool is_equal(float a, float b);
void update_dda_backward(float distance_x, float distance_y, t_data *game);
int quadrant_of_angle(float angle_player);
int border_point(int step, bool direction_negative);
void horizontal_intersection(t_data *game, float angle_d);
void vertical_intersection(t_data *game, float angle);
