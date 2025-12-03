#include "include/gmt.h"
void init_matrix(char **grid, bool mark_center)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			grid[i][j] = ' ';
		}
	}
	// Initialize grid
	int cx = SIZE / 2;
	int cy = SIZE / 2;
	double radius = SIZE / 2.0 - 1; // radius
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			// Coordinates relative to center
			double dx = j - cx;
			double dy = i - cy;

			// Inside circle check
			if (dx * dx + dy * dy < radius * radius) {
				grid[i][j] = '#'; // fill inside circle
			} else {
				grid[i][j] = ' '; // outside circle
			}
			if (mark_center && dx * dx + dy * dy == 0) {
				grid[i][j] = 'X'; // center marker
			}
		}
	}
}