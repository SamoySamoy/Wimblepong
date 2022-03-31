#include "pong.h"

using namespace std;

int sdl_init(int width, int height) {
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
	//create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
	//create the screen texture to render the screen surface to the actual display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);
	//Load the title image
	title = SDL_LoadBMP("title.bmp");
	//Load the numbermap image
	numbermap = SDL_LoadBMP("numbermap.bmp");
	//Load the gameover image
	end = SDL_LoadBMP("gameover.bmp");
	// Set the title colourkey. 
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);
	return 0;
}

int check_score() {
	// if a player reaches 3 points, reset the score 
	if (score[0] == 3) {
		score[0] = 0;
		score[1] = 0;
		return 1;
	}
	if (score[1] == 3) {
		score[0] = 0;
		score[1] = 0;
		return 2;
	}
	//return 0 if no one has reached a score of 3 yet
	return 0;
}

int check_collision(ball_class a, paddle_class b) {
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;
	
	if (left_a > right_b) {
		return 0;
	}
	if (right_a < left_b) {
		return 0;
	}
	if (top_a > bottom_b) {
		return 0;
	}
	if (bottom_a < top_b) {
		return 0;
	}
	return 1;
}

void draw_game_over(int p) { 

	SDL_Rect p1;
	SDL_Rect p2;
	SDL_Rect cpu;
	SDL_Rect dest;

	p1.x = 0;
	p1.y = 0;
	p1.w = end->w;
	p1.h = 75;

	p2.x = 0;
	p2.y = 75;
	p2.w = end->w;
	p2.h = 75;
	
	cpu.x = 0;
	cpu.y = 150;
	cpu.w = end->w;
	cpu.h = 75;

	dest.x = (screen->w / 2) - (end->w / 2);
	dest.y = (screen->h / 2) - (75 / 2);
	dest.w = end->w;
	dest.h = 75;
	
	switch (p) {	
		case 1:			
			SDL_BlitSurface(end, &p1, screen, &dest);
			break;
		case 2:
			SDL_BlitSurface(end, &p2, screen, &dest);
			break;
		default:
			SDL_BlitSurface(end, &cpu, screen, &dest);
	}	
}

void draw_menu() {
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

/* void draw_background() {
 
	SDL_Rect src;
	
	//draw bg with net
	src.x = 0;
	src.y = 0;
	src.w = screen->w;
	src.h = screen->h;

	//draw the backgorund
	//int r = SDL_FillRect(screen,&src,0);
	
	//if (r !=0){
		
	//	printf("fill rectangle faliled in func draw_background()");
	//}
} */

void draw_net() {

	SDL_Rect net;
	
	net.x = screen->w / 2;
	net.y = 20;
	net.w = 5;
	net.h = 15;

	//draw the net
	for(int i = 0; i < 15; i++) {		
		int r = SDL_FillRect(screen, &net, SDL_MapRGB(screen->format, 231, 60, 231));
		if (r != 0) { 	
			printf("fill rectangle faliled in func draw_net()");
		}
		net.y = net.y + 30;
	}
}

void draw_player_0_score() {	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) - src.w - 12; //12 is just padding spacing
	dest.y = 0;
	dest.w = 64;
	dest.h = 64;

	if (score[0] > 0 && score[0] < 10) {
		src.x += src.w * score[0];
	}
	SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_player_1_score() {	
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
	
	if (score[1] > 0 && score[1] < 10) {	
		src.x += src.w * score[1];
	}
	SDL_BlitSurface(numbermap, &src, screen, &dest);
}
