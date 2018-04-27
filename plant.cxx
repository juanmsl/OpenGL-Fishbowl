#include "plant.h"

Plant::Plant(const float& x, const float& y, const int& z, const int& discos, const int&color, const int& R) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
	this->discos = discos;
	this->R = R;
}

void Plant::draw() {
	float factorRX = 180.0f / (float) this->discos;
	float factorC = 50.0f / (float) this->discos;
	float limit = this->discos * 1.5f;
	for(float i = this->discos, cl = 0; i < limit; i++, cl++) {
		HSL(this->color, 80, 30 + (factorC * cl));
		float factorH = (i - (this->discos)) * 0.5f;
		float factorRY = 360.0f / i;
		for(float j = 0; j < i; j++) {
			glPushMatrix();
				glTranslatef(x, y + factorH, z);
				glRotatef(factorRY * j, 0, 1, 0);
				glRotatef(factorRX * i, 1, 0, 0);
				glutSolidCone(1, R, 8, 8);
			glPopMatrix();
		}
	}
}
