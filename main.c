#include "termlib.h"
int main() {
	Vector3 squareVCB[2] = {
		{ 0, 1, 2, TL_WHITE },
		{ 0, 2, 3, TL_WHITE }
	};
	Vector3 square[4] = {
		{ 30, -30, 60, TL_RED },
		{ 30, 30, 60, TL_GREEN },
		{ -30, 30, 60, TL_BLUE },
		{ -30, -30, 60, TL_WHITE }
	};
	while(1) {
		printf("\033[2J");
		for(int b = 0; b < 4; b++)
			square[b] = rotate3DYEx(square[b], (Vector2){ 0, 75, TL_WHITE }, 0.01);
		drawPolyhedron(square, squareVCB, 2);
		usleep(1000000/30);
	}
}
