typedef struct {
	char p0;
	char p1;
} pos_data_t;

pos_data_t grid_select(char grid[3][3], char row, char col) {
	printf("Selected: %d\n", (char)(grid[row][col]));
	return (pos_data_t) { row, col };
}

void grid_draw(const char grid[3][3]) {
    int c = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row][col] != EMPTY) {
				SDL_Rect rect;
				rect.x = (col*TILE_SIZE)+5;
				rect.y = (row*TILE_SIZE)+5;
				rect.w = (int)(TILE_SIZE)-10;
				rect.h = (int)(TILE_SIZE)-10;

				SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
				SDL_RenderFillRect(renderer, &rect);

                SDL_RenderCopy(renderer, texts[grid[row][col] - 1].texture, NULL, &rect);
            }
        }
	}
}

void grid_lines_draw(void) {
	for (int i = 0; i < 3; i++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// horizontal lines
		SDL_RenderDrawLine(renderer, 0, TILE_SIZE*i, WINDOW_SIZE, TILE_SIZE*i);

		// vertical lines
		SDL_RenderDrawLine(renderer, TILE_SIZE*i, 0, TILE_SIZE*i, WINDOW_SIZE);
	}
}

bool grid_check(void) {
    int count = 0;
    int i = 1;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row][col] != EMPTY) {
                if (grid[row][col] != i++) {
                    count++;
                }
            }
        }
    }

    if (count != 0) return false;
    return true;
}

void grid_reset(void) {

}

void display_contents(const char grid[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			printf("%d\t", grid[row][col]);
		}

		printf("\n");
	}

	printf("\n");
}
