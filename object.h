#pragma once
#include <SDL2/SDL.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

const int SCREEN_WIDTH = 640;	
const int SCREEN_HEIGHT = 480;

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
ball_t ball;
paddle_t paddle[2];
int score[] = {0,0};
int width, height;		//used if fullscreen

SDL_Window* window = NULL;	//The window we'll be rendering to
SDL_Renderer *renderer;		//The renderer SDL will use to draw to the screen

//surfaces
SDL_Surface *screen;
SDL_Surface *title;
SDL_Surface *numbermap;
SDL_Surface *end;

//textures
SDL_Texture *screen_texture;

//Function declarations
int sdl_init(int w, int h, int argc, char *args[]);
void init_game();
int check_score();
int check_collision(ball_t a, paddle_t b);
void move_ball();
void move_paddle_ai();
void move_paddle(int d);
void draw_game_over(int p);
void draw_menu();
void draw_background();
void draw_net();
void draw_ball();
void draw_paddle();
void draw_player_0_score();
void draw_player_1_score();
void run();
