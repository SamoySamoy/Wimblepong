#pragma once // include guard
#include "pong.h"
#include <iostream>
using namespace std;

void init_game() {
	paddle[0].x = 20;
	paddle[0].y = screen->h / 2 - 50 ;
	paddle[0].w = 10;
	paddle[0].h = 50;

	paddle[1].x = screen->w - 30;
	paddle[1].y = screen->h / 2 - 50;
	paddle[1].w = 10;
	paddle[1].h = 50;

	ball.x = screen->w / 2;
	ball.y = screen->h / 2;
	ball.w = 10;
	ball.h = 10;
	ball.dx = 1;
	ball.dy = 1;
}

void draw_ball() {
	SDL_Rect rec;

	rec.x = ball.x;
	rec.y = ball.y;
	rec.w = ball.w;
	rec.h = ball.h;

	int r = SDL_FillRect(screen , &rec, SDL_MapRGB(screen->format, 43, 255, 0));
	if (r != 0) {	
		cout << "fill rectangle failed in func draw_ball()";
	}
}

void draw_paddle() {
	SDL_Rect rec1, rec2;
	rec1.x = paddle[0].x;
	rec1.y = paddle[0].y;
	rec1.w = paddle[0].w;
	rec1.h = paddle[0].h;

	rec2.x = paddle[1].x;
	rec2.y = paddle[1].y;
	rec2.w = paddle[1].w;
	rec2.h = paddle[1].h;
 	int r1 = SDL_FillRect(screen, &rec1, SDL_MapRGB(screen->format, 255, 255, 255));
	int r2 = SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 255, 255, 255));
	if (r1 != 0 || r2 != 0){	
		cout << "fill rectangle faliled in func draw_paddle()";
	}
}

void move_ball() {
	/* Move the ball by its motion vector. */
	ball.x += ball.dx;
	ball.y += ball.dy;
	
	/* Turn the ball around if it hits the edge of the screen. */
	if (ball.x < 0) {		
		score[1] += 1;
		Mix_PlayMusic(clap, 0);
		init_game();
	}

	if (ball.x > screen->w - 10) { 		
		score[0] += 1;
		Mix_PlayMusic(clap, 0);
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
			// Collision sound effect 
			Mix_PlayMusic(ball_effect, 0);
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
				//teleport ball to avoid multi collision glitch
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



