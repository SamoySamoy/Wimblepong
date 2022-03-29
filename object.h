#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using namespace std;

const int SCREEN_WIDTH = 640;	//window height
const int SCREEN_HEIGHT = 480;	//window width

typedef struct ball_s {
	int x, y; // position on the screen
	int w,h; // ball width and height
	int dx, dy; // movement vector
} ball_t;

typedef struct paddle {
	int x,y;
	int w,h;
} paddle_t;

// Global setup
static ball_t ball;
static paddle_t paddle[2];
int score[] = {0,0};
int width, height;		//used if fullscreen

SDL_Window* window = NULL;	//The window we'll be rendering to
SDL_Renderer *renderer;		//The renderer SDL will use to draw to the screen

//surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

//textures
SDL_Texture *screen_texture;

//Function declarations
int init(int w, int h, int argc, char *args[]);
static void init_game();
int check_score();
int check_collision(ball_t a, paddle_t b);
static void move_ball();
static void move_paddle_ai();
static void move_paddle(int d);
static void draw_game_over(int p);
static void draw_menu();
static void draw_background();
static void draw_net();
static void draw_ball();
static void draw_paddle();
static void draw_player_0_score();
static void draw_player_1_score();
