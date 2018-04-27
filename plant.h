#ifndef __PLANT_H__
#define __PLANT_H__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "colors.h"

class Plant {
	protected:
		float x;
		float y;
		float z;
		int discos;
		int color;
		int R;

	public:
		Plant(const float& x, const float& y, const int& z, const int& discos, const int&color, const int& R);
		void draw();
};

#endif
