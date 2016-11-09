
#ifndef	PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream> // cout
#include <stdlib.h> // rand, srand
#include <time.h>   // time
#include "Shaders.h"
#include "Camera.h"
#include "Maze.h"

class PlayState: public GameState {
	public:
		void enter();
		void leave();
		void update();
		void render();
		void changeSize(int w, int h);
		void keyboardFunc(unsigned char key, int x, int y);
};

#endif
