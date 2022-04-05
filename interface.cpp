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
void draw_net() 
{
	SDL_Rect net1, net2;

	net1.x = screen->w / 2 - 5;
	net1.y = 20;
	net1.w = 5;
	net1.h = screen->h - 30;
    
	net2.x = screen->w / 2 + 10;
	net2.y = 20;
	net2.w = 5;
	net2.h = screen->h - 30;
	//draw the net		
	int r1 = SDL_FillRect(screen, &net1, SDL_MapRGB(screen->format, 255, 255, 255));
	int r2 = SDL_FillRect(screen, &net2, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r1 != 0 || r2 != 0) { 	
		cout << "fill rectangle faliled in func draw_net()";
	}
}

void draw_border(int line)
{
	SDL_Rect border;

	border.x = screen->w / 2 - line;
	border.y = 0;
	border.w = screen->w / 15;
	border.h = screen->h;

	for (int i = 0; i < 15; i++)
	{
		int r = SDL_FillRect(screen, &border, SDL_MapRGB(screen->format, 0, 77, 0));
		if (r != 0)
		{
			cout << "Function draw_border failed!";
		}
		border.y = border.y + 30;
	}
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
	dest.y = 0;
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
	dest.y = 0;
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
