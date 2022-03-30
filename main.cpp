#include "object.h"
#include "object.cpp"
#include "pong.cpp"
 
int main (int argc, char *args[]) {
	sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args);
	run();
}

