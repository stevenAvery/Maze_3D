// TODO load from config file
// DONE state manager
// TODO player class that handles movement and collision
// DONE genereate maze panels rather than the entire cube
// TODO have maze load in textures


//#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include "GameStateManager.h"
#include "PlayState.h"

#define MAX_FPS 60

GameStateManager stateManager;
PlayState playState;

void init() {
	stateManager.setState(&playState);
}

void update(void) {
	stateManager.update();
}

void render(void) {
	stateManager.render();
}

void mainLoop(int value) {
	update();
	render();
	glutTimerFunc(1000/MAX_FPS, mainLoop, value);
}

void changeSize(int w, int h) {
	stateManager.changeSize(w, h);
}

void keyboardFunc(unsigned char key, int x, int y) {
	stateManager.keyboardFunc(key, x, y);
}

int main(int argc, char **argv) {
	stateManager.addState(&playState);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(1024, 576);
	glutCreateWindow("3D Maze");
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("Error starting GLEW: %s\n", glewGetErrorString(error));
		exit(0);
	}

	glutTimerFunc(1000/MAX_FPS, mainLoop, 0);
	glutDisplayFunc(render);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboardFunc);

	init();
	glutMainLoop();
}
