SDL_Window*   window   = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font*     font     = NULL;

void sdl_setup(void) {    
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_OPENGL);

	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    font = TTF_OpenFont("DejaVuSerif.ttf", 72);
}

void sdl_cleanup() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
