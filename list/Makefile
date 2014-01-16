PROG := list
SHELL := /bin/sh
CC := gcc
CXX := g++

COMPILER_OPTIONS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic
CFLAGS := -std=c99 -Iinclude $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++11 -Weffc++ $(COMPILER_OPTIONS)
LDFLAGS := -Wl,--no-as-needed -lm

DEBUGFLAGS := -g -O0 -D _DEBUG
RELEASEFLAGS := -O2 -D NDEBUG

TARGET  := list-test.x
SOURCES := $(shell echo src/*.c)
HEADERS := $(shell echo include/*.h)
COMMON  :=
OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES)

zip:
	-zip $(PROG).zip include/s096.h \
							     include/$(PROG).h \
									 src/$(PROG).c \
									 src/main.c

clean:
	-rm -f $(TARGET) $(OBJECTS) $(PROG).zip

%.o: %.c $(HEADERS) $(COMMON)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

.PHONY : all release
