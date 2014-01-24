vpath %.cpp src

BUILD_DIR_PROJECT := $(BUILD_DIR)/project
TARGET_PROJECT := $(INSTALL_DIR)/lib/libproject.a
CXXFLAGS := $(CXXFLAGS)

$(TARGET_PROJECT) : | $(INSTALL_DIR)/include/project

#SOURCES_PROJECT := $(shell echo $(SOURCE_DIR)/src/*.cpp)
#OBJECTS_PROJECT := $(SOURCES_PROJECT:.cpp=.o)
#OBJECTS_PROJECT := $(OBJECTS_PROJECT:$(SOURCE_DIR)/src=$(BUILD_DIR_PROJECT))
OBJECTS_PROJECT := \
	$(BUILD_DIR_PROJECT)/gcd.o \
	$(BUILD_DIR_PROJECT)/rational.o

#OBJECTS_PROJECT := $(shell echo $(BUILD_DIR_PROJECT)/*.o)

$(INSTALL_DIR)/include/project ::
	$(MKDIR) $@
	$(RSYNC) include/project/ $@/

ARTIFACTS += $(INSTALL_DIR)/include/project

