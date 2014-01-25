vpath %.cpp test
vpath %.cc test

BUILD_DIR_NBODY_TEST := $(BUILD_DIR)/$(NBODY_NAME)-test
TARGET_NBODY_TEST := $(INSTALL_DIR)/test/$(NBODY_NAME)-test.x

$(TARGET_NBODY_TEST) : $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a
$(TARGET_NBODY_TEST) : LDFLAGS += -lgcov $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a

OBJECTS_NBODY_TEST := \
	$(BUILD_DIR_NBODY_TEST)/gtest-all.o \
	$(BUILD_DIR_NBODY_TEST)/rationalTest.o \
	$(BUILD_DIR_NBODY_TEST)/$(NBODY_NAME)-test.o

$(OBJECTS_NBODY_TEST) : CXXFLAGS += -fprofile-arcs -ftest-coverage

# Settings for gtest
INCLUDE_FLAGS := -I$(DEV_DIR)/include -I$(GTEST_DIR)/include $(INCLUDE_FLAGS)
vpath %.cc $(GTEST_DIR)/src
$(BUILD_DIR_NBODY_TEST)/gtest-all.o $(BUILD_DIR_NBODY_TEST)/gtest-all.d: INCLUDE_FLAGS += -I$(GTEST_DIR)/include -I$(GTEST_DIR) -I$(DEV_DIR)/test
# Need to filter out -Weffc++ flag (or gtest won't compile)
$(OBJECTS_NBODY_TEST) : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(BUILD_DIR_NBODY_TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Wextra,$(CXXFLAGS))
