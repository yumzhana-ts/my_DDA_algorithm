#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define EPSILON 1e-6

#define TILE_SIZE 40
#define RESET_COLOR "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED   "\x1b[31m"
#define BLUE  "\x1b[34m"
#define BOLD "\x1b[1m"
#define BOLD_GREY "\x1b[1m\x1b[90m"

// Placeholder for game data structure
typedef struct s_file
{
    char **map;
    int player_x;
    int player_y;
}              t_file;

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
    t_file *file;
}              t_data;

// Functions provided above
static int count_boundary(bool positive, int step);
static int check_wall(int y, int x, t_data *game);
float angle(float angle_player);
static void zero_infinity(float angle, t_data *game);
static void get_lines(t_data *game);
void dda(t_data *game);
void update_dda(float distance_x, float distance_y, t_data *game);
void get_ray_line_x(t_data *game, float angle);
void get_ray_line_y(t_data *game, float angle);
double calculate_distance_to_wall(t_data *game);
bool is_equal(float a, float b);