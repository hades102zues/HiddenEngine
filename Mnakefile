#======compiler Flags
cxx_flags = -Wall -std=c++17  -g

#======includes
inc_glad = third-party/glad/include
inc_glm = third-party/glm/include
inc_sdl2 = third-party/sdl2_core/include


includes = -I$(inc_glad) -I$(inc_glm) -I$(inc_sdl2) 


#======libraries
sdl2_path = third-party/sdl2_core/lib


lib_paths = -L$(sdl2_path)

lib_objs = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
lib_objs += -lSDL2

libs = $(lib_paths) $(lib_objs)



#======File Detection
src = $(wildcard src/*.cpp) 

src += $(wildcard src/engine-core/game-engine/*.cpp) 

src += $(wildcard src/renderer/renderer-manager/*.cpp)

obj = $(src:.cpp=.o)




#======control
.PHONY = run all clean launch
run: all
all: clean build launch



build: $(obj) 
	clang++ -o ./game build/*.o $(libs)

%.o: %.cpp
	clang++ -o build/$(notdir $@) -c $< $(cxx_flags) $(includes)

clean: 
	mkdir -p build && rm -f build/*.o && rm -f ./game

launch:
	./game