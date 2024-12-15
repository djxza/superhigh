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
INCFLAGS += -I./src

LDFLAGS  = -luser32
#LDFLAGS += ./lib/glfw/.build/src/libglfw3.a
LDFLAGS += -L./lib/glfw/.build/src/
LDFLAGS += -lglfw3
LDFLAGS += -lopengl32 -lgdi32
#LDFLAGS += -L./lib/glfw/.build/src/
#LDFLAGS += -lglfw3


SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, bin/obj/%.o, $(SRC))

bin/obj/%.o: src/%.cpp
	$(CC) -c $< -o $@ $(CCFLAGS)

all: $(OBJ)
	$(CC) $(filter %.o, $(OBJ)) -o $(OUT) $(LDFLAGS)

build_libs: build_glfw

run:
	$(OUT)

build_glfw:
	cd lib/glfw && \
	cmake -B .build -S . -G "MinGW Makefiles" && \
	cd .build && \
	make

clean:
	rm -rf $(OUT) $(shell find . -name *.o)