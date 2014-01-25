# First item: dummy "all" rule
all : 

# The compilers and programs to use
SHELL := /bin/sh
CC := gcc
CXX := g++
LD := g++
CP := cp -r
RSYNC := rsync -Cau --out-format='%n%L' --exclude='\.*' --delete
AR := ar
RM := rm -f
ZIP := zip
MKDIR := mkdir -p

# Here we'll define the important locations.
DEV_DIR := .
BUILD_DIR := $(DEV_DIR)/build
INSTALL_DIR := $(DEV_DIR)/install
GTEST_DIR := $(DEV_DIR)/third_party/gtest

# Flags to use during compilation
FLAGS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic -I$(INSTALL_DIR)/include
# Use the C99 standard
CFLAGS := -std=c99 $(FLAGS)
# Use the C++11 standard and warn on violations of Meyers' "Effective C++"
CXXFLAGS := -std=c++11 -Weffc++ $(FLAGS)
#CXXFLAGS := -std=c++11 $(FLAGS)
LDFLAGS := -L$(INSTALL_DIR)/lib -L$(GTEST_DIR)/lib -lm -lrt -lpthread

DEBUG_FLAGS := -g -O0 -D _DEBUG
RELEASE_FLAGS := -O2 -D NDEBUG

ARTIFACTS := 

