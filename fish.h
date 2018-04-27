#ifndef __FISH_H__
#define __FISH_H__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "colors.h"

struct vertex {
	float x;
	float y;
	float z;
	vertex(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vertex() {

	}

	void draw() {
		glVertex3f(x, y, z);
	}
};

struct face {
	vertex v1;
	vertex v2;
	vertex v3;
	face(vertex v1, vertex v2, vertex v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	void draw() {
		normal(v1, v3, v2);
		glBegin(GL_TRIANGLES);
			v1.draw();
			v2.draw();
			v3.draw();
		glEnd();
	}

	void normal(vertex F, vertex S, vertex T) {
		float a = F.x;
		float b = F.y;
		float c = F.z;

		float d = S.x;
		float e = S.y;
		float f = S.z;

		float g = T.x;
		float h = T.y;
		float i = T.z;

		float nx = (-a)*(((e-b)*(i-c))-((h-b)*(f-c)));
		float ny =  (b)*(((d-a)*(i-c))-((g-a)*(f-c)));
		float nz = (-c)*(((d-a)*(h-b))-((g-a)*(e-b)));

		glNormal3f(nx, ny, nz);
	}
};

class Fish {
	public:
		float x;
		float y;
		float z;
		float vx;
		float vy;
		float vz;
		int color;
		float size;
		Fish(const float& x, const float& y, const float& z, const float& vx, const float& vy, const float& vz, const int&color, const float&size = 1);
		void draw();
};

#endif
