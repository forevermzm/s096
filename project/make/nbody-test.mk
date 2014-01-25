vpath %.cpp test
vpath %.cc test

BUILD_DIR_NBODY-TEST := $(BUILD_DIR)/$(NBODY_NAME)-test
TARGET_NBODY-TEST := $(INSTALL_DIR)/test/$(NBODY_NAME)-test.x

$(TARGET_NBODY-TEST) : $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a
$(TARGET_NBODY-TEST) : LDFLAGS += -lgcov $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a

#SOURCES_NBODY-TEST := $(shell echo $(SOURCE_DIR)/test/*.cpp)
#OBJECTS_NBODY-TEST := $(SOURCES_NBODY-TEST:.cpp=.o)
#OBJECTS_NBODY-TEST := $(OBJECTS_NBODY-TEST:$(SOURCE_DIR)/test=$(BUILD_DIR_NBODY))
#OBJECTS_NBODY-TEST := $(shell echo $(BUILD_DIR_NBODY-TEST)/*.o)
OBJECTS_NBODY-TEST := \
	$(BUILD_DIR_NBODY-TEST)/gtest-all.o \
	$(BUILD_DIR_NBODY-TEST)/rationalTest.o \
	$(BUILD_DIR_NBODY-TEST)/$(NBODY_NAME)-test.o

$(OBJECTS_NBODY-TEST) : CXXFLAGS += -fprofile-arcs -ftest-coverage

# Settings for gtest
GTEST_DIR := $(SOURCE_DIR)/third_party/gtest
CXXFLAGS := -I$(GTEST_DIR)/include $(CXXFLAGS)
vpath %.cc $(GTEST_DIR)/src
$(BUILD_DIR_NBODY-TEST)/gtest-all.o : CXXFLAGS += -I$(GTEST_DIR)/include
# Need to filter out -Weffc++ flag (or gtest won't compile)
$(BUILD_DIR_NBODY-TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(BUILD_DIR_NBODY-TEST)/$(NBODY_NAME)-test.o : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
