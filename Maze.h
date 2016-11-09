
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <GL/glut.h>
#include <glm/glm.hpp>

class Maze {
	private:
		typedef enum cell {FREE, WALL, START, FINISH} Cell;

		int width;
		int height;
		int gridSize;
		Cell** grid;

		void init(int width, int height);
		void generateRecursive(int x, int y);

	public:
		Maze(int width, int height);
		Maze(void);
		~Maze(void);
		int getWidth(void);
		int getHeight(void);
		bool isCellWall(int x, int y);
		void generate(void);
		std::vector<glm::vec4> getVertices(void);
		std::vector<GLuint> getIndexes(void);
		void print(void);
		int getWallCount(void);
};

#endif
