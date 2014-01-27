SFML := project/third_party/SFML-2.1/
COMPILER_OPTIONS := -g -O0 -m64 -Wall -Wextra -Wshadow -Werror -pedantic \
										-I$(SFML)include
CFLAGS := -std=c99 $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++11 $(COMPILER_OPTIONS)
LDFLAGS := -lm \
					 $(SFML)lib/libsfml-graphics-s.a \
					 $(SFML)lib/libsfml-window-s.a \
					 $(SFML)lib/libsfml-system-s.a \

#libsfml-audio-s.a
#libsfml-graphics-s.a
#libsfml-network-s.a
#libsfml-system-s.a
#libsfml-window-s.a
