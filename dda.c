#include "include.h"

double calculate_distance_to_wall(t_data *game)
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

bool is_equal(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

static int count_boundary(bool positive, int step)
{
    int boundary;
    if (positive)
        boundary = ((step / TILE_SIZE) + 1) * TILE_SIZE;
    if (!positive)
    {
        if (step % TILE_SIZE == 0)
            boundary = ((step / TILE_SIZE) - 1) * TILE_SIZE;
        else
            boundary = ((step / TILE_SIZE)) * TILE_SIZE;
    }
    return (boundary);
}

static int check_wall(int y, int x, t_data *game)
{
    printf("map[%d][%d]: %c | " RESET_COLOR, y / TILE_SIZE, x / TILE_SIZE,
           game->file->map[(int)game->step_y / TILE_SIZE][(int)game->step_x / TILE_SIZE]);
    if (game->file->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
        return (1);

    return (0);
}

float angle(float angle_player)
{
    while (angle_player > M_PI / 2)
        angle_player -= M_PI / 2;
    return (angle_player);
}

static void zero_infinity(float angle, t_data *game)
{
    int boundary;
    int cathetus;
    if (is_equal(angle, M_PI / 2))
    {
        boundary = count_boundary(false, game->step_y);
        cathetus = game->step_y - boundary;
        printf("Player position: %d  | ", game->step_y);
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
}

static void get_lines(t_data *game)
{
    float angle_triangle;
    float rest_angle_triangle;

    angle_triangle = angle(game->player_angle);
    rest_angle_triangle = (M_PI / 2) - angle_triangle;
    if (tan(game->player_angle) > 0)
    {
        get_ray_line_x(game, angle_triangle);
        get_ray_line_y(game, rest_angle_triangle);
    }
    else if (tan(game->player_angle) < 0)
    {
        get_ray_line_x(game, rest_angle_triangle);
        get_ray_line_y(game, angle_triangle);
    }
}

void dda(t_data *game)
{
    game->ray = 0;
    game->vertical_hypotenuse = 0;
    game->horizontal_hypotenuse = 0;
    game->step_x = game->file->player_x;
    game->step_y = game->file->player_y;
    int expected = (int)calculate_distance_to_wall(game);
    int i = 1;
    while (true)
    {
        printf(BLUE "Checking tile %d: " RESET_COLOR, i++);
        if (check_wall(game->step_y, game->step_x, game))
            break;
        if (is_equal(game->player_angle, M_PI) || is_equal(game->player_angle, M_PI / 2) ||
            is_equal(game->player_angle, 0) || is_equal(game->player_angle, 2 * M_PI) ||
            is_equal(game->player_angle, 3 * M_PI / 2))
        {
            zero_infinity(game->player_angle, game);
        }
        else
        {
            get_lines(game);
            update_dda(game->horizontal_hypotenuse, game->vertical_hypotenuse, game);
            printf("horizontal hypotenuse: %f | vertical hypotenuse: %f\n", game->horizontal_hypotenuse, game->vertical_hypotenuse);
        }
        printf("\n");
    }
    printf(BLUE "\nTotal: " RESET_COLOR);
    printf("Total tiles: %d | ", i - 2);
    printf("Final distance expected: %-6.2d | Final distance counted: %-6.2d\n", expected, (int)game->ray);
    is_equal(expected, game->ray) == 1 ? printf(GREEN "PASSED\n" RESET_COLOR) : printf(RED "FAILED " RESET_COLOR);
    printf("Difference is approx: %d\n", expected - (int)game->ray);
}

void update_dda(float distance_x, float distance_y, t_data *game)
{
    if (distance_x < distance_y)
    {
        game->ray += distance_x;
        game->step_x = game->horizontal_x;
        game->step_y = game->horizontal_y;
    }
    else
    {
        game->ray += distance_y;
        game->step_x = game->vertical_x;
        game->step_y = game->vertical_y;
    }
    printf("🌟 Distance Status 🌟\n");
    printf("📍 X: %-4f | 📍 Y: %-4f\n", distance_x, distance_y);
}

void get_ray_line_x(t_data *game, float angle)
{
    int boundary;
    int adjacent_cathetus;
    float opposite_cathetus;
    if (cos(game->player_angle) > 0)
    {
        boundary = count_boundary(true, game->step_x);
        adjacent_cathetus = boundary - game->step_x;
        opposite_cathetus = adjacent_cathetus * tan(angle);
        game->horizontal_y = game->file->player_y + opposite_cathetus;
    }
    else
    {
        boundary = count_boundary(false, game->step_x);
        adjacent_cathetus = game->step_x - boundary;
        opposite_cathetus = adjacent_cathetus * tan(angle);
        game->horizontal_y = game->file->player_y - opposite_cathetus;
    }
    game->horizontal_hypotenuse = sqrt(adjacent_cathetus * adjacent_cathetus + opposite_cathetus * opposite_cathetus);
    game->horizontal_x = boundary;
}

void get_ray_line_y(t_data *game, float angle)
{
    int boundary;
    int opposite_cathetus;
    float adjacent_cathetus;
    if (sin(game->player_angle) < 0)
    {
        boundary = count_boundary(true, game->step_y);
        opposite_cathetus = boundary - game->step_y;
        adjacent_cathetus = opposite_cathetus / tan(angle);
        game->vertical_x = adjacent_cathetus + game->file->player_x;
    }
    else
    {
        boundary = count_boundary(false, game->step_y);
        opposite_cathetus = game->step_y - boundary;
        adjacent_cathetus = opposite_cathetus / tan(angle);
        game->vertical_x = game->file->player_x - adjacent_cathetus;
    }
    game->vertical_hypotenuse = sqrt(adjacent_cathetus * adjacent_cathetus + opposite_cathetus * opposite_cathetus);
    game->vertical_y = boundary;
}