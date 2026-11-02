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
	Vector3 cube[8] = {
        { -200, -500, 10, TL_WHITE },
        {  200, -500, 10, TL_RED },
        {  200, -100, 10, TL_GREEN },
        { -200, -100, 10, TL_BLUE },
        { -200, -500,  20, TL_YELLOW },
        {  200, -500,  20, TL_CYAN },
        {  200, -100,  20, TL_MAGENTA },
        { -200, -100,  20, TL_WHITE }
    };
    drawPolyhedron(cube, 8);
}
