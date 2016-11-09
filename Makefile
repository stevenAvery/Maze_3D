all:
	# --------------------------------------------------------------------------
	# -w to hide warnings
	clang++ -std=c++11 -Wall -lGL -lglut -lGLU -lGLEW -lm -lfreeimage *.cpp -o a.out

clean:
	rm a.out
