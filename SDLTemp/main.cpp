#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *win = SDL_CreateWindow("=_=",
								SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
								800, 600,
								SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		SDL_Quit();
		return 1;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(win,
												-1,
												SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		std::cout << "Failed to create renderer" << std::endl;
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 2;
	}

	SDL_Surface *test = IMG_Load("okay.png");
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, test);
	SDL_FreeSurface(test);

	bool quit = false;
	while (!quit) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);	
	SDL_Quit();
	return 0;
}