#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

const int SCREEN_WIDTH = 640;	//window height
const int SCREEN_HEIGHT = 480;	//window width

typedef struct ball_s {

	int x, y; /* position on the screen */
	int w,h; // ball width and height
	int dx, dy; /* movement vector */
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