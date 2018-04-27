#ifndef __FISHBOWL_H__
#define __FISHBOWL_H__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "colors.h"
#include "fish.h"
#include "plant.h"

class FishBowl {
	protected:
		float width;
		float height;
		float depth;
		std::vector<Plant> plants;
		std::vector<Fish> fishes;

	public:
		FishBowl(const float& width, const float& height, const float& depth);
		void draw(bool play);
		void addFish(const float& x, const float& y, const float& z, const float& vx, const float& vy, const float& vz, const int&color, const float&size);
		void addPlant(const float& x, const float& y, const int& z, const int& discos, const int&color, const int& R);
};

#endif
