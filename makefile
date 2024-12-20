CC = g++

OUT = ./bin/main

CCFLAGS  = -std=gnu++2b

# optimisation
# CCFLAGS += -O2

# debug
CCFLAGS += -g

# error settings
CCFLAGS += -Wall -Wextra
CCFLAGS += -Wpedantic

CCFLAGS += $(INCFLAGS)

INCFLAGS  = -I./lib/glfw/include
INCFLAGS += -I./lib/glad/include
INCFLAGS += -I./lib
INCFLAGS += -I./src

LDFLAGS  = -luser32
LDFLAGS += -L./lib/glfw/.build/src/
LDFLAGS += -lglfw3
LDFLAGS += ./lib/glad/glad.o
LDFLAGS += -lopengl32 -lgdi32
LDFLAGS += ./lib/stb/img.c

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, bin/obj/%.o, $(SRC))

bin/obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CCFLAGS)
	
all: $(OBJ)
	$(CC) $(filter %.o, $(OBJ)) -o $(OUT) $(LDFLAGS)

run:
	$(OUT)

build_libs: build_glfw build_glad

build_glfw:
	cd lib/glfw && \
	cmake -B .build -S . -G "MinGW Makefiles" && \
	cd .build && \
	make

build_glad:
	gcc -c ./lib/glad/src/glad.c -I ./lib/glad/include -o ./lib/glad/glad.o

clean:
	rm -rf $(OUT) $(shell find ./bin/ -name *.o)