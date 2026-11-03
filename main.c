#include "termlib.h"
int main() {
	editDevice(30, 30, 30);
	Vector3a squareVCB[2] = {
		{ 0, 1, 2 },
		{ 0, 2, 3 }
	};
	Vector3 square[4] = {
		{ 30, -30, 120, TL_RED },
		{ 30, 30, 120, TL_GREEN },
		{ -30, 30, 120, TL_BLUE },
		{ -30, -30, 120, TL_WHITE }
	};
	while(1) {
		for(int b = 0; b < 4; b++)
			square[b] = rotate3DYEx(square[b], (Vector2){ 0, 120, TL_WHITE }, 0.01);
		drawPolyhedron(square, squareVCB, 2);
		renderFrame();
	}
}
