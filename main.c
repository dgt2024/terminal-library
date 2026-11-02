#include "termlib.h"
void rotatingSquare() {
	for(float n = 0; n < M_PI * 2; n += 0.005) {
		printf("\033[2J");
		drawTriangle(proyect((Vector3){ 500*cos(n+M_PI), -500, 30+20*sin(n+M_PI), (Color){ 255, 0, 0 } }),
					proyect((Vector3){ 500*cos(n+M_PI), 500, 30+20*sin(n+M_PI), (Color){ 0, 255, 0 } }),
					proyect((Vector3){ 500*cos(n), 500, 30+20*sin(n), (Color){ 0, 0, 255 } }));
		drawTriangle(proyect((Vector3){ 500*cos(n+M_PI), -500, 30+20*sin(n+M_PI), (Color){ 255, 0, 0 } }),
					proyect((Vector3){ 500*cos(n), -500, 30+20*sin(n), (Color){ 255, 255, 255 } }),
					proyect((Vector3){ 500*cos(n), 500, 30+20*sin(n), (Color){ 0, 0, 255 } }));		
		fflush(stdout);
		usleep(1000000/60);
	}
}
int main() {
	Vector2 poly[4] = {
		{ -50, -50, TL_WHITE },
		{ 50, -50, TL_RED },
		{ 50, 50, TL_GREEN },
		{ -50, 50, TL_BLUE }
	};
	drawPolygon(poly, 4);
}
