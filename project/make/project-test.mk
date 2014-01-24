vpath %.cpp test
vpath %.cc test

BUILD_DIR_PROJECT_TEST := $(BUILD_DIR)/project-test
TARGET_PROJECT_TEST := $(INSTALL_DIR)/test/project-test.x

$(TARGET_PROJECT_TEST) : $(INSTALL_DIR)/lib/libproject.a
$(TARGET_PROJECT_TEST) : LDFLAGS += -lgcov $(INSTALL_DIR)/lib/libproject.a

#SOURCES_PROJECT_TEST := $(shell echo $(SOURCE_DIR)/test/*.cpp)
#OBJECTS_PROJECT_TEST := $(SOURCES_PROJECT_TEST:.cpp=.o)
#OBJECTS_PROJECT_TEST := $(OBJECTS_PROJECT_TEST:$(SOURCE_DIR)/test=$(BUILD_DIR_PROJECT))
#OBJECTS_PROJECT_TEST := $(shell echo $(BUILD_DIR_PROJECT_TEST)/*.o)
OBJECTS_PROJECT_TEST := \
	$(BUILD_DIR_PROJECT_TEST)/rationalTest.o \
	$(BUILD_DIR_PROJECT_TEST)/project-test.o

$(OBJECTS_PROJECT_TEST) : CXXFLAGS += -fprofile-arcs -ftest-coverage

# Settings for gtest
GTEST_DIR := $(SOURCE_DIR)/third_party/gtest
CXXFLAGS := -I$(GTEST_DIR)/include $(CXXFLAGS)
vpath %.cc $(GTEST_DIR)/src
$(BUILD_DIR_PROJECT_TEST)/gtest-all.o : CXXFLAGS += -I$(GTEST_DIR)/include
# Need to filter out -Weffc++ flag (or gtest won't compile)
$(BUILD_DIR_PROJECT_TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(BUILD_DIR_PROJECT_TEST)/%.o : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
