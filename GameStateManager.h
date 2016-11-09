
#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include <vector>

class GameStateManager {
	private:
		std::vector<GameState> states;
		GameState *currentState;

	public:
		GameStateManager();
		void mainLoop(int value);
		void addState(GameState *state);
		void deleteState(GameState *state);
		void setState(GameState *state);
		void init();
		void update();
		void display();
		void changeSize(int w, int h);
		void keyboardFunc(unsigned char key, int x, int y);
};

#endif
