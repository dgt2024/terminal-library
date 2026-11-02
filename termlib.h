#ifndef _TERMLIB_H_
#define _TERMLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define TL_BLACK ((Color){ 0, 0, 0 })
#define TL_RED ((Color){ 255, 0, 0 })
#define TL_GREEN ((Color){ 0, 255, 0 })
#define TL_BLUE ((Color){ 0, 0, 255 })
#define TL_YELLOW ((Color){ 255, 255, 0 })
#define TL_MAGENTA ((Color){ 255, 0, 255 })
#define TL_CYAN ((Color){ 0, 255, 255 })
#define TL_WHITE ((Color){ 255, 255, 255 })
#define TL_GRAY ((Color){ 128, 128, 128 })
int tl_height = 100;
int tl_width = 100;
typedef struct Color {
	uint8_t r, g, b;
} Color;
typedef struct Vector2 {
	int x, y;
	Color c;
} Vector2;
struct Vector1a {
	struct Vector1 {
		int x;
		Color c;
	} d;
	struct Vector1a* n;
};
typedef struct Vector3 {
	float x, y, z;
	Color c;
} Vector3;
void freeV1a(struct Vector1a* init) {
	while(init) {
		struct Vector1a* x = init;
		init = init->n;
		free(x);
	}
}
struct Vector3* g;
struct Vector1 atV1a(struct Vector1a* init, int x) {
	for(int a = 0; a < x; a++) init = init->n;
	return init->d;
}
int absCmpV2(Vector2 n1, Vector2 n2) {
	if(n1.y == n2.y) return n1.x < n2.x;
	return n1.y < n2.y;
}
int cmpV2(const void* n1, const void* n2) {
	Vector2 a = *(Vector2*)n1;
	Vector2 b = *(Vector2*)n2;
	if(a.y == b.y) return (a.x > b.x) - (a.x < b.x);
	return (a.y > b.y) - (a.y < b.y);
}
int cmpV3(const void* n1, const void* n2) {
	Vector3 a = *(Vector3*)n1;
	Vector3 b = *(Vector3*)n2;
	int n = g[(int)a.x].x + g[(int)a.y].x + g[(int)a.z].x + g[(int)a.x].y + g[(int)a.y].y + g[(int)a.z].y + g[(int)a.x].z + g[(int)a.y].z + g[(int)a.z].z;
	int m = g[(int)b.x].x + g[(int)b.y].x + g[(int)b.z].x + g[(int)a.x].y + g[(int)a.y].y + g[(int)a.z].y + g[(int)a.x].z + g[(int)a.y].z + g[(int)a.z].z;
	return (n < m) - (n > m);
} 
struct Vector1a* getVLine(struct Vector1a* ptr, Vector2 n1, Vector2 n2) {
	struct Vector1a* w = ptr;
	int dy = n2.y - n1.y;
	for(int a = 1; a <= dy; a++) {
		w->d.x = n1.x + (int)(a * (n2.x - n1.x) / (float)(n2.y - n1.y));
		w->d.c.r = n1.c.r + a * (n2.c.r - n1.c.r) / dy;
		w->d.c.g = n1.c.g + a * (n2.c.g - n1.c.g) / dy;
		w->d.c.b = n1.c.b + a * (n2.c.b - n1.c.b) / dy;
		w->n = malloc(sizeof(struct Vector1a));
		w = w->n;
	}
	w->n = NULL;
	return w;
}
Vector2* arrSort(Vector2 n1, Vector2 n2, Vector2 n3) {
	Vector2* s = malloc(3*sizeof(Vector2));
	int x = absCmpV2(n1, n2);
	int y = absCmpV2(n2, n3);
	int z = absCmpV2(n3, n1);
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
void getTriangle(struct Vector1a* le, struct Vector1a* re, Vector2* n) {
	if(n[0].y == n[1].y) {
		getVLine(le, n[0], n[2]);
		getVLine(re, n[1], n[2]);
	}
	else if(n[1].y == n[2].y) {
		getVLine(le, n[0], n[1]);
		getVLine(re, n[0], n[2]);
	}
	else if(n[1].y * abs(n[2].x - n[0].x) / abs(n[2].y - n[0].y) + n[0].x <= n[1].x) {
		getVLine(le, n[0], n[2]);
		getVLine(getVLine(re, n[0], n[1]), n[1], n[2]);
	}
	else {
		getVLine(getVLine(le, n[0], n[1]), n[1], n[2]);
		getVLine(re, n[0], n[2]);
	}
}
void drawTriangle(Vector2 o1, Vector2 o2, Vector2 o3) {
	Vector2* n = arrSort(o1, o2, o3);
	struct Vector1a* le = malloc(sizeof(struct Vector1a));
	struct Vector1a* re = malloc(sizeof(struct Vector1a));
	getTriangle(le, re, n);
	int dy = n[2].y - n[0].y;
	for(int a = 0; a < dy; a++) {
		printf("\033[%d;%dH", a + n[0].y + tl_height / 2, le->d.x * 2 + tl_width);
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
	printf("\033[48;2;0;0;0m\033[%d;0H", tl_height);
	fflush(stdout);
	free(n);
	freeV1a(le);
	freeV1a(re);
}
Vector2 proyect(Vector3 w) {
	return (Vector2){ (w.x / w.z), (w.y / w.z), w.c };
}
int isInside(Vector2 o1, Vector2 o2, Vector2 o3, Vector2 p) {
	Vector2* n = arrSort(o1, o2, o3);
	if(p.y < n[0].y || p.y > n[2].y) {
		free(n);
		return 0;
	}
	int r = 0;
	struct Vector1a* le = malloc(sizeof(struct Vector1a));
	struct Vector1a* re = malloc(sizeof(struct Vector1a));
	getTriangle(le, re, n);
	if(p.x >= atV1a(le, p.y - le->d.x).x && p.x <= atV1a(re, p.y - re->d.x).x) r = 1;
	free(n);
	freeV1a(le);
	freeV1a(re);
	return r;
}
void drawPolygon(Vector2* arr, int size) {
	if(size < 3) return;
	qsort(arr, size, sizeof(Vector2), cmpV2);
	for(int a = 0; a < size - 2; a++) drawTriangle(arr[a], arr[a+1], arr[a+2]);
}
void drawPolyhedron(Vector3* arr, Vector3* v, int tris) {
	g = arr;
	qsort(v, tris, sizeof(Vector3), cmpV3);
	for(int a = 0; a < tris; a++)
		drawTriangle(proyect(arr[(int)v[a].x]), proyect(arr[(int)v[a].y]), proyect(arr[(int)v[a].z]));
}
#endif
