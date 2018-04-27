#include "fish.h"

std::vector<vertex> vertexs;
std::vector<face> faces;

void load(std::string filename) {
	std::ifstream file(filename.c_str(), std::ios::in);
	std::string line;

	while(getline(file, line)) {
		std::stringstream buffer(line);
		float x, y, z;
		int sc1, sc2, sc3;
		std::string type;

		buffer >> type;
		if(type == "v") {
			buffer >> x >> y >> z;
			vertex v(x, y, z);
			vertexs.push_back(v);
		} else if(type == "f") {
			buffer >> sc1 >> sc2 >> sc3;
			face f(vertexs[sc1 - 1], vertexs[sc2 - 1], vertexs[sc3 - 1]);
			faces.push_back(f);
		}
	}
	file.close();
}

Fish::Fish(const float& x, const float& y, const float& z, const float& vx, const float& vy, const float& vz, const int&color, const float&size) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
	this->color = color;
	this->size = size;

	load("GOLDFISH.OBJ");
}

void Fish::draw() {
	float teta = 0;
	if(0 < vx && 0 < vz) {
		teta = atan(this->vx / this->vz) * (180.0f / 3.14159265);
	} else if(0 < vx && 0 > vz) {
		teta = (atan(this->vz / this->vx) * (180.0f / 3.14159265)) + 180.0f;
	} else if(0 > vx && 0 > vz) {
		teta = (atan(this->vx / this->vz) * (180.0f / 3.14159265)) + 180.0f;
	} else if(0 > vx && 0 < vz) {
		teta = atan(this->vz / this->vx) * (180.0f / 3.14159265);
	}

	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(100 * size, 100 * size, 100 * size);
		glRotatef(teta, 0, 1, 0);

		HSL(this->color, 100, 50);
		for(int i = 0; i < faces.size(); i++) {
			faces[i].draw();
		}
	glPopMatrix();
}
