#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "object.h"
using namespace std;

int sdl_init(int width, int height, int argc, char *args[]) {
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

void init_game() {
	
	ball.x = screen->w / 2;
	ball.y = screen->h / 2;
	ball.w = 10;
	ball.h = 10;
	ball.dy = 1;
	ball.dx = 1;
	
	paddle[0].x = 20;
	paddle[0].y = screen->h / 2 - 50 ;
	paddle[0].w = 10;
	paddle[0].h = 50;

	paddle[1].x = screen->w - 20 - 10;
	paddle[1].y = screen->h / 2 - 50;
	paddle[1].w = 10;
	paddle[1].h = 50;
}

int check_score() {
	//loop through player scores
	for(int i = 0; i < 2; i++) {
		//check if score is @ the score win limit
		if (score[i] == 10 ) {
			//reset scores
			score[0] = 0;
			score[1] = 0;
			//return 1 if player 1 score @ limit
			if (i == 0) {
				return 1;	
			//return 2 if player 2 score is @ limit
			} else {	
				return 2;
			}
		}
	}
	//return 0 if no one has reached a score of 10 yet
	return 0;
}

int check_collision(ball_t a, paddle_t b) {
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

void move_ball() {
	
	/* Move the ball by its motion vector. */
	ball.x += ball.dx;
	ball.y += ball.dy;
	
	/* Turn the ball around if it hits the edge of the screen. */
	if (ball.x < 0) {		
		score[1] += 1;
		init_game();
	}

	if (ball.x > screen->w - 10) { 		
		score[0] += 1;
		init_game();
	}

	if (ball.y < 0 || ball.y > screen->h - 10) {		
		ball.dy = -ball.dy;
	}
	//check for collision with the paddle
	for (int i = 0; i < 2; i++) {	
		int c = check_collision(ball, paddle[i]); 
		//collision detected	
		if (c == 1) {
			//ball moving left
			if (ball.dx < 0) {	
				ball.dx -= 1;
			//ball moving right
			} else {		
				ball.dx += 1;
			}
			//change ball direction
			ball.dx = -ball.dx;
			
			//change ball angle based on where on the paddle it hit
			int hit_pos = (paddle[i].y + paddle[i].h) - ball.y;

			if (hit_pos >= 0 && hit_pos < 7) {
				ball.dy = 4;
			}

			if (hit_pos >= 7 && hit_pos < 14) {
				ball.dy = 3;
			}
			
			if (hit_pos >= 14 && hit_pos < 21) {
				ball.dy = 2;
			}

			if (hit_pos >= 21 && hit_pos < 28) {
				ball.dy = 1;
			}

			if (hit_pos >= 28 && hit_pos < 32) {
				ball.dy = 0;
			}

			if (hit_pos >= 32 && hit_pos < 39) {
				ball.dy = -1;
			}

			if (hit_pos >= 39 && hit_pos < 46) {
				ball.dy = -2;
			}

			if (hit_pos >= 46 && hit_pos < 53) {
				ball.dy = -3;
			}

			if (hit_pos >= 53 && hit_pos <= 60) {
				ball.dy = -4;
			}

			//ball moving right
			if (ball.dx > 0) {
				//teleport ball to avoid mutli collision glitch
				if (ball.x < 30) {			
					ball.x = 30;
				}
				
			//ball moving left
			} else {			
				//teleport ball to avoid mutli collision glitch
				if (ball.x > 600) {				
					ball.x = 600;
				}
			}
		}
	}
}

void move_paddle_ai() {
	int center = paddle[0].y + 25;
	int screen_center = screen->h / 2 - 25;
	int ball_speed = ball.dy;
	if (ball_speed < 0) {
		ball_speed = -ball_speed;
	}

	//ball moving right
	if (ball.dx > 0) {
		//return to center position
		if (center < screen_center) {			
			paddle[0].y += ball_speed;		
		} else {		
			paddle[0].y -= ball_speed;	
		}
	//ball moving left
	} else {	
		//ball moving down
		if (ball.dy > 0) { 		
			if (ball.y > center) { 			
				paddle[0].y += ball_speed;
			} else { 			
				paddle[0].y -= ball_speed;
			}
		}	
		//ball moving up
		if (ball.dy < 0) {	
			if (ball.y < center) { 				
				paddle[0].y -= ball_speed;			
			} else {			
				paddle[0].y += ball_speed;
			}
		}
		//ball moving stright across
		if (ball.dy == 0) {			
			if (ball.y < center) { 			
				paddle[0].y -= 5;
			} else {			
				paddle[0].y += 5;
			}
		}	 		
	}
}

void move_paddle(int d) {
	// if the down arrow is pressed move paddle down
	if (d == 0) {		
		if(paddle[1].y >= screen->h - paddle[1].h) {		
			paddle[1].y = screen->h - paddle[1].h;		
		} else { 		
			paddle[1].y += 5;
		}
	}	
	// if the up arrow is pressed move paddle up
	if (d == 1) {
		if(paddle[1].y <= 0) {		
			paddle[1].y = 0;
		} else {		
			paddle[1].y -= 5;
		}
	}
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

void draw_background() {
 
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
}

void draw_net() {

	SDL_Rect net;
	
	net.x = screen->w / 2;
	net.y = 20;
	net.w = 5;
	net.h = 15;

	//draw the net
	for(int i = 0; i < 15; i++) {		
		int r = SDL_FillRect(screen, &net, 0xffffffff);
		if (r != 0) { 	
			printf("fill rectangle faliled in func draw_net()");
		}
		net.y = net.y + 30;
	}
}

void draw_ball() {
	SDL_Rect src;

	src.x = ball.x;
	src.y = ball.y;
	src.w = ball.w;
	src.h = ball.h;
	
	int r = SDL_FillRect(screen , &src, 0xffffffff);

	if (r !=0){	
		printf("fill rectangle faliled in func drawball()");
	}
}

void draw_paddle() {
	SDL_Rect src;
	for (int i = 0; i < 2; i++) {
	
		src.x = paddle[i].x;
		src.y = paddle[i].y;
		src.w = paddle[i].w;
		src.h = paddle[i].h;
	
		int r = SDL_FillRect(screen, &src, 0xffffffff);
		if (r !=0){		
			printf("fill rectangle faliled in func draw_paddle()");
		}
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


