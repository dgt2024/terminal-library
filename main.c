#include "termlib.h"
int main() {
	
	Vector3 squareVcb[2] = {
		{ 0, 1, 2, TL_WHITE },
		{ 0, 2, 3, TL_WHITE }
	};
	Vector3 square[4] = {
		{ 30, -30, 30, TL_RED },
		{ 30, 30, 30, TL_GREEN },
		{ -30, 30, 30, TL_BLUE },
		{ -30, -30, 30, TL_WHITE }
	};
	for(float a = 0; a < M_PI; a += 0.01) {
		printf("\033[2J");
		drawPolyhedron(square, squareVcb, 2);
		usleep(1000000/30);
	}
}
