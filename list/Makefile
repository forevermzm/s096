SHELL := /bin/sh
CC := gcc

COMPILER_OPTIONS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic
CFLAGS := -std=c99 -Iinclude $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++11 -Weffc++ $(COMPILER_OPTIONS)
DEBUGFLAGS := -g -O0 -D _DEBUG
RELEASEFLAGS := -O2 -D NDEBUG

TARGET  := list-test
SOURCES := $(shell echo src/*.c)
HEADERS := $(shell echo include/*.h)
COMMON  :=
OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES)

clean:
	-rm -f $(OBJECTS)

%.o: %.c $(HEADERS) $(COMMON)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

.PHONY : all release
