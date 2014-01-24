# The compilers and programs to use
SHELL := /bin/sh
CC := gcc
CXX := g++
LD := g++
CP := cp -r
RSYNC := rsync -Cau -i --exclude='\.*' --delete
AR := ar
RM := rm -f
ZIP := zip
MKDIR := mkdir -p

# Here we'll define the important locations.
SOURCE_DIR := .
BUILD_DIR := ./build
INSTALL_DIR := ./install

# Flags to use during compilation
FLAGS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic -I$(INSTALL_DIR)/include
# Use the C99 standard
CFLAGS := -std=c99 $(FLAGS)
# Use the C++11 standard and warn on violations of Meyers' "Effective C++"
CXXFLAGS := -std=c++11 -Weffc++ $(FLAGS)
LDFLAGS := -L$(INSTALL_DIR)/lib -lm

DEBUG_FLAGS := -g -O0 -D _DEBUG
RELEASE_FLAGS := -O2 -D NDEBUG

ARTIFACTS := 

