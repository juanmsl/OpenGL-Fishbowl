#include "fishbowl.h"

FishBowl::FishBowl(const float& width, const float& height, const float& depth) {
	this->width = width;
	this->height = height;
	this->depth = depth;
}

void FishBowl::draw(bool play) {
	for(int i = 0; i < plants.size(); i++) {
		plants[i].draw();
	}

	for(int i = 0; i < fishes.size(); i++) {
		fishes[i].draw();
		if(play) {
			if(fishes[i].x >= (width / 2.0f) - 5 || fishes[i].x <= (-width / 2.0f) + 5) {
				fishes[i].vx *= -1;
			}
			if(fishes[i].z >= (depth / 2.0f) - 5 || fishes[i].z <= (-depth / 2.0f) + 5) {
				fishes[i].vz *= -1;
			}
			fishes[i].x += fishes[i].vx / 100.0f;
			fishes[i].z += fishes[i].vz / 100.0f;
		}
	}

	/*
	* BASE
	*/

	HSL(60, 100, 80);
	glPushMatrix();
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(-(width / 2.0f), 0, depth / 2.0f);
			glVertex3f(-(width / 2.0f), 0, -depth / 2.0f);
			glVertex3f( (width / 2.0f), 0, -depth / 2.0f);
			glVertex3f( (width / 2.0f), 0, depth / 2.0f);
		glEnd();
	glPopMatrix();

	/*
	* AGUA
	*/

	HSLA(240, 100, 50, 0.3);
	glPushMatrix();
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(-(width / 2.0f), height * 0.9f, -depth / 2.0f);
			glVertex3f( (width / 2.0f), height * 0.9f, -depth / 2.0f);
			glVertex3f( (width / 2.0f), height * 0.9f, depth / 2.0f);
			glVertex3f(-(width / 2.0f), height * 0.9f, depth / 2.0f);
		glEnd();
	glPopMatrix();

	/*
	* VIDRIO
	*/

	HSLA(0, 100, 100, 0.2);
	glPushMatrix();
		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
			glVertex3f(-(width / 2.0f),  0,   depth / 2.0f);
			glVertex3f(-(width / 2.0f), height,   depth / 2.0f);
			glVertex3f( (width / 2.0f), height,   depth / 2.0f);
			glVertex3f( (width / 2.0f),  0,   depth / 2.0f);
		glEnd();
		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
			glVertex3f( (width / 2.0f),  0,   depth / 2.0f);
			glVertex3f( (width / 2.0f), height,   depth / 2.0f);
			glVertex3f( (width / 2.0f), height, -depth / 2.0f);
			glVertex3f( (width / 2.0f),  0, -depth / 2.0f);
		glEnd();
		glNormal3f(0, 0, -1);
		glBegin(GL_QUADS);
			glVertex3f( (width / 2.0f),  0, -depth / 2.0f);
			glVertex3f( (width / 2.0f), height, -depth / 2.0f);
			glVertex3f(-(width / 2.0f), height, -depth / 2.0f);
			glVertex3f(-(width / 2.0f),  0, -depth / 2.0f);
		glEnd();
		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
			glVertex3f(-(width / 2.0f),  0, -depth / 2.0f);
			glVertex3f(-(width / 2.0f), height, -depth / 2.0f);
			glVertex3f(-(width / 2.0f), height,   depth / 2.0f);
			glVertex3f(-(width / 2.0f),  0,   depth / 2.0f);
		glEnd();
	glPopMatrix();
}

void FishBowl::addFish(const float& x, const float& y, const float& z, const float& vx, const float& vy, const float& vz, const int&color, const float&size) {
	Fish fish(x, y, z, vx, vy, vz, color, size);
	this->fishes.push_back(fish);
}

void FishBowl::addPlant(const float& x, const float& y, const int& z, const int& discos, const int&color, const int& R) {
	Plant plant(x, y, z, discos, color, R);
	this->plants.push_back(plant);
}
