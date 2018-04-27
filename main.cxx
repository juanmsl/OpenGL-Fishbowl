#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "colors.h"
#include "fish.h"
#include "plant.h"
#include "fishbowl.h"

float FPS = 30.0f;
float WIDTH = 1400;
float HEIGHT = 800;
FishBowl pecera(60, 30, 60);
float aspect = (float)WIDTH / (float)HEIGHT,
	r = 50, teta = 3.14159265f / 2.0f,
	cx = 0, cy = 15, cz = 0,
	px = cos(teta) * r, py = 15, pz = sin(teta) * r;

bool play = true;

void keyPressed(unsigned char key, int x, int y) {
	switch(key) {
		case 'a':
		case 'A':
			teta += 2.0f * (3.14159265f / 180.0f);
		break;
		case 'd':
		case 'D':
			teta -= 2.0f * (3.14159265f / 180.0f);
		break;
		case 'w':
		case 'W':
			r -= 1.0f;
			r = ((r < 0) ? 0 : r );
		break;
		case 's':
		case 'S':
			r += 1.0f;
		break;
		case 'e':
		case 'E':
			py += 1.0f;
		break;
		case 'q':
		case 'Q':
			py -= 1.0f;
		break;
		case 'p':
		case 'P':
			play = !play;
		break;
	}

	px = cos(teta) * r;
	pz = sin(teta) * r;
	glutPostRedisplay();
}

void timeFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000.0f / FPS, timeFunc, value);
}

void myInit (void) {
	HSL(60, 100, 99, true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearDepth(1.0f);
	glDepthRange(-100.0f, 100.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	GLfloat mat_shininess[] = {100.0};
	GLfloat light_position[] = {0, 15, 0, 0.5};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	for(int j = -25; j <= 25; j += 5) {
		for(int i = -25; i <= 25; i+= 5) {
			if(rand() % 5 == 0) {
				pecera.addPlant(i, 0, j, (rand() % 8) + 5, rand() % 15 + 130, 5);
			}
		}
	}

	pecera.addFish(15, 8, 15, -10, 0, -12, 30, 0.6);
	pecera.addFish(13, 12, 18, -10, 0, -12, 45, 0.7);

	pecera.addFish(24, 20, 0, 15, 0, 20, 300, 1);

	pecera.addFish(-5, 15, 0, -6, 0, 8, 135, 0.5);
	pecera.addFish(0, 18, 5, -5, 0, 10, 120, 0.8);

	pecera.addFish(-20, 25, 24, 14, 0, -15, 212, 0.7);
	pecera.addFish(-23, 20, 18, 14, 0, -15, 205, 0.6);
}

void myDisplay (void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, WIDTH * 0.75, HEIGHT);
	glLoadIdentity();
	gluLookAt(px, py, pz, cx, cy, cz, 0, 1, 0);
	pecera.draw(play);

	// FRENTE
	glViewport(WIDTH * 0.75, 0, WIDTH * 0.25, HEIGHT * 0.33);
	glLoadIdentity();
	gluLookAt(0, 15, 50, 0, 15, 0, 0, 1, 0);
	pecera.draw(play);

	// ATRAS
	glViewport(WIDTH * 0.75, HEIGHT * 0.33, WIDTH * 0.25, HEIGHT * 0.33);
	glLoadIdentity();
	gluLookAt(0, 15, -50, 0, 15, 0, 0, 1, 0);
	pecera.draw(play);

	// DERECHA
	glViewport(WIDTH * 0.75, HEIGHT * 0.66, WIDTH * 0.25, HEIGHT * 0.33);
	glLoadIdentity();
	gluLookAt(50, 15, 0, 0, 15, 0, 0, 1, 0);
	pecera.draw(play);

	glFlush();
	glutSwapBuffers();
}

void myResize (int w, int h) {
	h = ((h == 0) ? 1 : h );
	aspect = (float)w/(float)h;
	WIDTH = w;
	HEIGHT = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, aspect, 0.01f, 1000.0f);
}

int main (int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Proyecto");
	myInit();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutKeyboardFunc(keyPressed);
	glutTimerFunc(1000.0f / FPS, timeFunc, 0);
	//glutFullScreen();
	glutMainLoop();

	return 0;
}
