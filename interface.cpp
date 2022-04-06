#pragma once
#include "pong.h"
#include <iostream>

using namespace std;

int sdl_init(int width, int height)
{
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);
	// Load title image
	title = SDL_LoadBMP("title.bmp");
	// Load numbermap image
	numbermap = SDL_LoadBMP("numbermap.bmp");
	// Load gameover image
	gameover = SDL_LoadBMP("gameover.bmp");
	// Set the title colourkey.
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);
	return 0;
}

void loadMusic() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Mix_GetError();
	}
	// Load background music 
	bg = Mix_LoadMUS("audio.mp3");
	// Load sound effect audio
	ball_effect = Mix_LoadMUS("ball.mp3");
	clap = Mix_LoadMUS("clap.mp3");
	if (bg == NULL || ball_effect == NULL || clap == NULL)
	{
		cout << Mix_GetError();
	}
}

void draw_menu()
{
	SDL_Rect src;
	SDL_Rect dest;
	src.x = 0;
	src.y = 0;
	src.w = title->w;
	src.h = title->h;

	dest.x = (screen->w / 2) - (src.w / 2);
	dest.y = (screen->h / 2) - (src.h / 2);
	dest.w = title->w;
	dest.h = title->h;

	SDL_BlitSurface(title, &src, screen, &dest);
}

void draw_stripe(int line)
{
	SDL_Rect border;

    border.x = 0;
	border.y = screen->h / 2 - line;
	border.w = screen->w;
	border.h = screen->h / 17;

	int r = SDL_FillRect(screen, &border, SDL_MapRGB(screen->format, 0, 77, 0));
	if (r != 0)
	{
		cout << "Function draw_border failed!"; 
	}
}

void draw_net() 
{
	SDL_Rect net;
	
	net.x = screen->w / 2 + 3;
	net.y = 6;
	net.w = 7;
	net.h = 15;

	//draw the net
	for(int i = 0; i < 30; i++) {
		int r = SDL_FillRect(screen, &net, 0xffffffff);
		if (r != 0) cout << "fill rectangle faliled in func draw_net()";
		net.y = net.y + 30;
	}		
}

void draw_vertical_line(int pos) {
	SDL_Rect line;
	line.x = pos;
	line.y = 10;
	line.w = 5;
	line.h = screen->h - 20;
	int r = SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r != 0) cout << "fill rectangle failed in func draw_line()";
}

void draw_horizontal_line(int pos) {
	SDL_Rect line;
	line.x = 10;
	line.y = pos;
	line.w = screen->w - 15;
	line.h = 5;
	int r = SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r != 0) cout << "fill rectangle failed in func draw_line";
}

void draw_vertical_line1(int pos) {
	SDL_Rect line;
	line.x = pos;
	line.y = 65;
	line.w = 5;
	line.h = screen->h - 120;
	int r = SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r != 0) cout << "fill rectangle failed in func draw_line";
}

void draw_horizontal_line1() {
	SDL_Rect line;
	line.x = 150;
	line.y = 240;
	line.w = screen->w - 300;
	line.h = 5;
	int r = SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r != 0) cout << "fill rectangle failed in func draw_line";
}

void draw_line() {
	draw_net();
	draw_vertical_line(10);
	draw_vertical_line(630);
	draw_horizontal_line(10);
	draw_horizontal_line(470);
	draw_horizontal_line(60);
	draw_horizontal_line(420);
	draw_vertical_line1(150);
	draw_vertical_line1(490);
    draw_horizontal_line1();
}
int check_collision(ball_class a, paddle_class b)
{
	int left_a = a.x;
	int right_a = a.x + a.w;
	int top_a = a.y;
	int bottom_a = a.y + a.h;

	int left_b = b.x;
	int right_b = b.x + b.w;
	int top_b = b.y;
	int bottom_b = b.y + b.h;

	if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b)
	{
		return 0;
	}
	return 1;
}

int check_score()
{
	// if a player reaches 3 points, reset the score
	if (score[0] == 3)
	{
		score[0] = 0;
		score[1] = 0;
		return 1;
	}
	if (score[1] == 3)
	{
		score[0] = 0;
		score[1] = 0;
		return 2;
	}
	// return 0 if no one has reached a score of 3 yet
	return 0;
}

void draw_player_0_score()
{
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) - src.w - 12; // 12 is just padding spacing
	dest.y = 5;
	dest.w = 64;
	dest.h = 64;

	if (score[0] > 0 && score[0] < 10)
	{
		src.x += src.w * score[0];
	}
	SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_player_1_score()
{
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) + 12;
	dest.y = 5;
	dest.w = 64;
	dest.h = 64;

	if (score[1] > 0 && score[1] < 10)
	{
		src.x += src.w * score[1];
	}
	SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_game_over(int p)
{

	SDL_Rect p1;
	SDL_Rect p2;
	SDL_Rect cpu;
	SDL_Rect dest;

	p1.x = 0;
	p1.y = 0;
	p1.w = gameover->w;
	p1.h = 75;

	p2.x = 0;
	p2.y = 75;
	p2.w = gameover->w;
	p2.h = 75;

	cpu.x = 0;
	cpu.y = 150;
	cpu.w = gameover->w;
	cpu.h = 75;

	dest.x = (screen->w / 2) - (gameover->w / 2);
	dest.y = (screen->h / 2) - (75 / 2);
	dest.w = gameover->w;
	dest.h = 75;
	switch (p)
	{
	case 1:
		SDL_BlitSurface(gameover, &p1, screen, &dest);
		break;
	case 2:
		SDL_BlitSurface(gameover, &p2, screen, &dest);
		break;
	default:
		SDL_BlitSurface(gameover, &cpu, screen, &dest);
	}
}
