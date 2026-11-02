#ifndef _TERMLIB_H_
#define _TERMLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
typedef struct Color {
	uint8_t r, g, b;
} Color;
typedef struct Vector2 {
	int x, y;
	Color c;
} Vector2;
typedef struct Vector1a {
	struct Vector1 {
		int x;
		Color c;
	} d;
	struct Vector1a* n;
} Vector2a;
typedef struct Vector3 {
	float x, y, z;
	Color c;
} Vector3;
Vector2a* getVLine(Vector2a* ptr, Vector2 n1, Vector2 n2) {
	Vector2a* w = ptr;
	int dy = n2.y - n1.y;
	for(int a = 1; a <= dy; a++) {
		w->d.x = n1.x + (int)(a * (n2.x - n1.x) / (float)(n2.y - n1.y));
		w->d.c.r = n1.c.r + a * (n2.c.r - n1.c.r) / dy;
		w->d.c.g = n1.c.g + a * (n2.c.g - n1.c.g) / dy;
		w->d.c.b = n1.c.b + a * (n2.c.b - n1.c.b) / dy;
		w->n = malloc(sizeof(Vector2a));
		w = w->n;
	}
	return w;
}
int cmp_v(Vector2 n1, Vector2 n2) {
	if(n1.y == n2.y) return n1.x > n2.x;
	return n1.y < n2.y;
}
Vector2* arrSort(Vector2 n1, Vector2 n2, Vector2 n3) {
	Vector2* s = malloc(3*sizeof(Vector2));
	int x = cmp_v(n1, n2);
	int y = cmp_v(n2, n3);
	int z = cmp_v(n3, n1);
	if(x && !z) {
		s[0] = n1;
		s[1] = y ? n2 : n3;
		s[2] = y ? n3 : n2;
	}
	if(y && !x) {
		s[0] = n2;
		s[1] = z ? n3 : n1;
		s[2] = z ? n1 : n3;
	}
	if(z && !y) {
		s[0] = n3;
		s[1] = x ? n1 : n2;
		s[2] = x ? n2 : n1;
	}
	return s;
}
void drawTriangle(Vector2 o1, Vector2 o2, Vector2 o3) {
	Vector2* n = arrSort(o1, o2, o3);
	Vector2a* le = malloc(sizeof(Vector2a));
	Vector2a* re = malloc(sizeof(Vector2a));
	if(n[0].y == n[1].y) {
		getVLine(le, n[1], n[2]);
		getVLine(re, n[0], n[2]);
	}
	else if(n[1].y == n[2].y) {
		getVLine(le, n[0], n[2]);
		getVLine(re, n[0], n[1]);
	}
	else if(n[1].y * abs(n[2].x - n[0].x) / abs(n[2].y - n[0].y) + n[0].x < n[1].x) {
		getVLine(le, n[0], n[2]);
		getVLine(getVLine(re, n[0], n[1]), n[1], n[2]);
	}
	else {
		getVLine(getVLine(le, n[0], n[1]), n[1], n[2]);
		getVLine(re, n[0], n[2]);
	}
	int dy = n[2].y - n[0].y;
	for(int a = 0; a < dy; a++) {
		printf("\033[%d;%dH", a + n[0].y + 50, le->d.x * 2 + 100);
		uint8_t r = le->d.c.r;
		uint8_t g = le->d.c.g;
		uint8_t b = le->d.c.b;
		int dx = re->d.x - le->d.x;
		if(!dx) printf("\033[48;2;%d;%d;%dm  ", r, g, b);
		else {
			for(int i = 0; i <= dx; i++) {
				printf("\033[48;2;%d;%d;%dm  ", r, g, b);
				r += (re->d.c.r - le->d.c.r) / dx;
				g += (re->d.c.g - le->d.c.g) / dx;
				b += (re->d.c.b - le->d.c.b) / dx;
			}
		}
		le = le->n;
		re = re->n;
	}
	printf("\033[48;2;0;0;0m");
	fflush(stdout);
	free(n);
}
Vector2 proyect(Vector3 w) {
	return (Vector2){ (w.x / w.z), (w.y / w.z), w.c };
}
#endif
