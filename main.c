#include "termlib.h"
int main() {
	editDevice(50, 50, 60);
	Vector3a squareVCB[8] = {
		{ 0, 1, 2 },
		{ 1, 2, 3 },
		{ 2, 3, 4 },
		{ 3, 4, 5 },
		{ 4, 5, 6 },
		{ 5, 6, 7 },
		{ 6, 7, 0 },
		{ 7, 0, 1 }
	};
	Vector3 square[8] = {
		{ 30, 30, 150, TL_GREEN },
		{ 30, -30, 150, TL_RED },
		{ -30, 30, 150, TL_BLUE },
		{ -30, -30, 150, TL_WHITE },
		{ -30, 30, 90, TL_YELLOW },
		{ -30, -30, 90, TL_BLACK },
		{ 30, 30, 90, TL_MAGENTA },
		{ 30, -30, 90, TL_CYAN },
	};
	while(1) {
		for(int b = 0; b < 8; b++)
			square[b] = rotate3DYEx(square[b], (Vector2){ 0, 120, TL_WHITE }, 0.01);
		drawPolyhedron(square, squareVCB, 8);
		renderFrame();
	}
}
