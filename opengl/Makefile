GLLOAD := glsdk/glload/
GLUTIL := glsdk/glutil/
FREEGLUT := glsdk/freeglut/
INCLUDES := -I$(GLLOAD)include/
COMPILER_OPTIONS := -g -O2 -m64 -Wall -Wextra -Wshadow -Werror -pedantic $(INCLUDES)
CFLAGS := -std=c99 $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++11 -Weffc++ $(COMPILER_OPTIONS)
LDFLAGS := -lGL -lGLU -lglut \
					 glsdk/glload/lib/libglload.a \

all: gltest

gltest:
	g++ -o gltest gltest.cpp $(CXXFLAGS) $(LDFLAGS)
#$(GLLOAD)lib/libglload.a \
#					 $(GLUTIL)lib/libglutil.a
.PHONY: all
