GCC = g++
INC = ./include
LIB = ./lib


main:main.cpp glad.c
	$(GCC) -g $^ -I$(INC) -I./headers -I./dep -L$(LIB) -lglfw3dll -lopengl32 -lassimp.dll -o $@

	