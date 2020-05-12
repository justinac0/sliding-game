 /**
 * ============
 * SLIDING GAME
 * ============
 *
 * https://en.wikipedia.org/wiki/Sliding_puzzle
 * 
 */

// drag animate tiles
// add text to tiles
// randomize tiles on new game
// *Load image onto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_SIZE  640
#define WINDOW_TITLE "sliding-game"

#define TILE_COUNT 3
#define TILE_SIZE (WINDOW_SIZE/3)

#define EMPTY -1

char grid[TILE_COUNT][TILE_COUNT] = {
	{ 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, EMPTY }
};

typedef struct {
    SDL_Texture* texture;
    SDL_Surface* surface;
} text_t;

text_t texts[8];

#include "sdl_util.c"
#include "drawing.c"

bool isDragging = false;
pos_data_t lastSelected;

bool processDrag(pos_data_t oldSelect, pos_data_t newSelect) {
    if (oldSelect.p0 == newSelect.p0 && abs(oldSelect.p1 - newSelect.p1) == 1) {
        grid[newSelect.p0][newSelect.p1] = grid[oldSelect.p0][oldSelect.p1];
        grid[oldSelect.p0][oldSelect.p1] = EMPTY;
        return true;
    }

    if (oldSelect.p1 == newSelect.p1 && abs(oldSelect.p0 - newSelect.p0) == 1) {
        grid[newSelect.p0][newSelect.p1] = grid[oldSelect.p0][oldSelect.p1];
        grid[oldSelect.p0][oldSelect.p1] = EMPTY;
        return true;
    }

    return false;
}

int main(void) {
	sdl_setup();

	bool isRunning = true;

    for (int i = 0; i < 8; i++) {
        char t[1];
        sprintf(t, "%d", i+1);
        SDL_Color color = { 0, 0, 0 };
        texts[i].surface = TTF_RenderText_Solid(font, t, color);
        texts[i].texture = SDL_CreateTextureFromSurface(renderer, texts[i].surface);

        int texW = 32;
        int texH = 32;
        SDL_QueryTexture(texts[i].texture, NULL, NULL, &texW, &texH);
    }

	SDL_Event e;
	while (isRunning == true) {
		if (SDL_PollEvent(&e)) {

			switch (e.type) {
				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (isDragging == true) {
						pos_data_t newSelected = grid_select(grid, (int)(e.button.y/TILE_SIZE), (int)(e.button.x/TILE_SIZE));

						if (grid[newSelected.p0][newSelected.p1] == EMPTY) {
                            if (processDrag(lastSelected, newSelected) == true) {
                                isDragging = false;
                            }
                        }
					}

					isDragging = true;

					lastSelected = grid_select(grid, (int)(e.button.y/TILE_SIZE), (int)(e.button.x/TILE_SIZE));
					break;

				case SDL_MOUSEBUTTONUP:
					display_contents(grid);
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		// grid_lines_draw();
		grid_draw(grid);

        SDL_RenderPresent(renderer);

        if (grid_check() == true) {
            grid_reset();
        }
    }

    for (int i = 0; i < 8; i++) {
        SDL_DestroyTexture(texts[i].texture);
        SDL_FreeSurface(texts[i].surface);
    }
   
	sdl_cleanup();

	return 0;
}
