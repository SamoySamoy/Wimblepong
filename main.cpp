#include "object.h"
#include "object.cpp"
 
int main (int argc, char *args[]) {
    //SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1) {
		
		return 0;
	}
	SDL_GetWindowSize(window, &width, &height);
	int sleep = 0;
	int quit = 0;
	int state = 0;
	int r = 0;
	Uint32 next_game_tick = SDL_GetTicks();
	// Initialize the ball position data. 
	init_game();
	//render loop
	while(quit == 0) {
		//check for new events every frame
		SDL_PumpEvents();
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_ESCAPE]) {
			quit = 1;
		}
		if (keystate[SDL_SCANCODE_DOWN]) {
			move_paddle(0);
		}
		if (keystate[SDL_SCANCODE_UP]) {
			move_paddle(1);
		}
		//draw background
		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, 0x000000ff);
		//display main menu
		if (state == 0 ) {
			if (keystate[SDL_SCANCODE_SPACE]) {
				state = 1;
			}
			draw_menu();
		//display gameover
		} else if (state == 2) {
			if (keystate[SDL_SCANCODE_SPACE]) {
				state = 0;
				//delay for a little bit so the space bar press dosnt get triggered twice
				//while the main menu is showing
            			SDL_Delay(500);
			}
			if (r == 1) {
				//if player 1 is AI if player 1 was human display the return value of r not 3
				draw_game_over(3);
			} else {
				//display gameover
				draw_game_over(r);
			}	
		//display the game
		} else if (state == 1) {
			//check score
			r = check_score();
			//if either player wins, change to game over state
			if (r == 1) {
				state = 2;	
			} else if (r == 2) {
				state = 2;	
			}
			move_paddle_ai();
			// Move the balls for the next frame. 
			move_ball();
			draw_net();
			draw_paddle();
			// Put the ball on the screen.
			draw_ball();
			draw_player_0_score();
			draw_player_1_score();
		}
		SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof (Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
		//draw to the display
		SDL_RenderPresent(renderer);
		//time it takes to render  frame in milliseconds
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();
		if( sleep >= 0 ) {				
			SDL_Delay(sleep);
		}
	}
	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(numbermap);
	SDL_FreeSurface(end);

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);
	
	//Destroy window 
	SDL_DestroyWindow(window);

	//Quit SDL subsystems 
	SDL_Quit(); 
	return 0;
}

