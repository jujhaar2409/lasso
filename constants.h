//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define SCALE_FACTOR (10)
// #define STEP_TIME 0.05
#define STEP_TIME (0.01 / SCALE_FACTOR)

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X - PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y - 100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

// #define COIN_GAP 1
#define COIN_GAP (0.2)

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360 - RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

// #define RELEASE_SPEED_STEP 20
// #define MIN_RELEASE_SPEED 0
// #define MAX_RELEASE_SPEED 200
// #define INIT_RELEASE_SPEED 100
#define RELEASE_SPEED_STEP (40 * SCALE_FACTOR)
#define MIN_RELEASE_SPEED (400 * SCALE_FACTOR)
#define MAX_RELEASE_SPEED (900*SCALE_FACTOR)
#define INIT_RELEASE_SPEED (700* SCALE_FACTOR)

// #define COIN_SPEED 120
#define COIN_SPEED (800 * SCALE_FACTOR)
#define COIN_ANGLE_DEG (my_random::get_random_in_range(60, 110))

// #define LASSO_G 50
// #define COIN_G 50
#define LASSO_G (800 *SCALE_FACTOR * SCALE_FACTOR)
#define COIN_G (1000 * SCALE_FACTOR* SCALE_FACTOR)

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

// gives the max number of coins that can be in the lasso at once
#define MAX_COINS 10

// COLORS definition
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define BRIGHT_RED 255, 68, 51
#define DARK_RED 124, 48, 48
#define BLUE 0, 0, 255
#define GREEN 0, 255, 0
#define YELLOW 255, 255, 0
#define LIGHT_GRAY 211, 211, 211
#define VERY_LIGHT_BROWN 234, 221, 202
#define LIGHT_BROWN 210, 180, 140
#define GRAY 128, 128, 128
#define BROWN 139, 69, 19
#define BLUE_VIOLET 100, 0, 200
#define SILVER 169, 169, 169
#define GOLD 255, 192, 0
#define STEEL_BLUE 70, 130, 180
#define PURPLE 255, 0, 255

// ITEM COLOR definitions
#define CANVAS_BG_COLOR VERY_LIGHT_BROWN

#define LASSO_CIRCLE_COLOR DARK_RED
#define LASSO_LOOP_COLOR BROWN
#define LASSO_LINE_COLOR BROWN
#define LASSO_BAND_COLOR LIGHT_BROWN

#define BONUS_COIN_COLOR GOLD
#define REGULAR_COIN_COLOR SILVER
#define MAGNET_COIN_COLOR STEEL_BLUE
#define BOMB_COIN_COLOR BRIGHT_RED
#define FRENZY_COIN_COLOR PURPLE
