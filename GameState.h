
#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void display() = 0;
		virtual void changeSize(int w, int h) = 0;
		virtual void keyboardFunc(unsigned char key, int x, int y) = 0;
};

#endif
