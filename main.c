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
    Vector3 cubeS[12] = {
        // Back (Z = 20)
        { 4, 5, 6, TL_WHITE },
        { 4, 6, 7, TL_WHITE },
    
        // Left
        { 0, 3, 4, TL_WHITE },
        { 3, 4, 7, TL_WHITE },
    
        // Right
        { 1, 5, 6, TL_WHITE },
        { 1, 2, 6, TL_WHITE },
   
        // Top
        { 1, 4, 5, TL_WHITE },
        { 0, 1, 4, TL_WHITE },
    
        // Bottom
        { 2, 3, 6, TL_WHITE },
        { 3, 6, 7, TL_WHITE },
        
        // Front (Z = 10)
        { 0, 1, 2, TL_WHITE },
        { 0, 2, 3, TL_WHITE }
    };
    for(int n = 0; n < 200; n++) {
    	printf("\033[2J");
   		Vector3 cube[8] = {
	        { -200+n, -500, 10, TL_WHITE },
	        {  200+n, -500, 10, TL_RED },
	        {  200+n, -100, 10, TL_GREEN },
	        { -200+n, -100, 10, TL_BLUE },
	        { -200+n, -500,  30, TL_YELLOW },
	        {  200+n, -500,  30, TL_CYAN },
	        {  200+n, -100,  30, TL_MAGENTA },
	        { -200+n, -100,  30, TL_WHITE }
	    };
    	drawPolyhedron(cube, cubeS, 12);
    	usleep(1000000/1);
    }
}
