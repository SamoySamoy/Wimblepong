#pragma once // include guard
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;	

class paddle_class {
public:	
	int x, y;  // position on the screen
	int w, h; // width and height
};

class ball_class {
public:	
	int x, y; 
	int w, h;
	int dx, dy; // movement vector
};


// Global setup
ball_class ball;
paddle_class paddle[2];
int score[] = {0,0};

Mix_Music *bg = NULL;
Mix_Chunk *sound = NULL;
SDL_Window *window = NULL;	
SDL_Renderer *renderer;	
SDL_Surface *screen;
SDL_Surface *title;
SDL_Surface *numbermap;
SDL_Surface *gameover;
SDL_Texture *screen_texture;

//Function declarations
void loadMusic();
void run();
int sdl_init(int w, int h);
void init_game();
int check_score();
int check_collision(ball_class a, paddle_class b);
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
