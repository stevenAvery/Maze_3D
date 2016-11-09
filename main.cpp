// TODO load from config file
// TODO state manager
// TODO player class that handles movement and collision
// DONE genereate maze panels rather than the entire cube
// TODO have maze load in textures


//#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> // rand, srand
#include <cstdio>   // printf
#include <time.h>   // time
#include "Shaders.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Maze.h"

#define MAX_FPS 60

GLuint program;
glm::mat4 projection;
GLuint objVAO;
int triangles;

Camera camera;
Maze myMaze;

void init() {
	// init Maze
	srand(time(NULL)); // seed random number generator

	// initialize the maze
	myMaze.generate();
	myMaze.print();

	// init OpenGL
	GLuint vbuffer;
	GLuint ibuffer;
	GLint vPosition;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	// get the vertices and indices from myMaze
	std::vector<glm::vec4> vecVertices = myMaze.getVertices();
	std::vector<GLuint> vecIndexes = myMaze.getIndexes();

	triangles = vecIndexes.size()/3;

	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, vecVertices.size()*sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vecVertices.size()*sizeof(glm::vec4), &vecVertices[0]); // sizeof(vertices), vertice);

	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecIndexes.size()*sizeof(GLuint), &vecIndexes[0], GL_STATIC_DRAW);

	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void update(void) {
	//std::cout << "new frame" << std::endl;
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	// Update view matrix
	glm::mat4 view = camera.render();

	int viewLoc = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(projection));

	glBindVertexArray(objVAO);
	glDrawElements(GL_TRIANGLES, 3*triangles, GL_UNSIGNED_INT, NULL);

	glutSwapBuffers();
}

void mainLoop(int value) {
	update();
	render();
	glutTimerFunc(1000/MAX_FPS, mainLoop, value);
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	if (h == 0) h = 1;

	float ratio = 1.0 * w / h;
	glViewport(0, 0, w, h);
	projection = glm::perspective(45.0f, ratio, 0.1f, 1000.0f);
}

void keyboardFunc(unsigned char key, int x, int y) {
	if(key == 27)
		glutLeaveMainLoop();
	if(key == 'a')
		camera.move(Camera::LEFT, 0.5f);
	if(key == 'd')
		camera.move(Camera::RIGHT, 0.5f);
	if(key == 'w')
		camera.move(Camera::FORWARD, 0.5f);
	if(key == 's')
		camera.move(Camera::BACKWARD, 0.5f);
	if(key == 'e')
		camera.move(Camera::UP, 0.5f);
	if(key == 'q')
		camera.move(Camera::DOWN, 0.5f);
	if(key == 'j')
		camera.rotateTowards(Camera::LEFT, 0.1f);
	if(key == 'l')
		camera.rotateTowards(Camera::RIGHT, 0.1f);
	if(key == 'i')
		camera.rotateTowards(Camera::UP, 0.1f);
	if(key == 'k')
		camera.rotateTowards(Camera::DOWN, 0.1f);
}

int main(int argc, char **argv) {
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

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	int vs = buildShader(GL_VERTEX_SHADER,   (char *)"shaders/basic.vs");
	int fs = buildShader(GL_FRAGMENT_SHADER, (char *)"shaders/basic.fs");
	program = buildProgram(vs, fs, 0);
	dumpProgram(program, (char *)"Template");
	init();

	glutMainLoop();
}
