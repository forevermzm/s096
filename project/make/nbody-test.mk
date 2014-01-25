vpath %.cpp test
vpath %.cc test

BUILD_DIR_NBODY-TEST := $(BUILD_DIR)/$(NBODY_NAME)-test
TARGET_NBODY-TEST := $(INSTALL_DIR)/test/$(NBODY_NAME)-test.x

$(TARGET_NBODY-TEST) : $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a
$(TARGET_NBODY-TEST) : LDFLAGS += -lgcov $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a

OBJECTS_NBODY-TEST := \
	$(BUILD_DIR_NBODY-TEST)/gtest-all.o \
	$(BUILD_DIR_NBODY-TEST)/rationalTest.o \
	$(BUILD_DIR_NBODY-TEST)/$(NBODY_NAME)-test.o

$(OBJECTS_NBODY-TEST) : CXXFLAGS += -fprofile-arcs -ftest-coverage

# Settings for gtest
CXXFLAGS := -I$(DEV_DIR)/include -I$(GTEST_DIR)/include $(CXXFLAGS)
vpath %.cc $(GTEST_DIR)/src
$(BUILD_DIR_NBODY-TEST)/gtest-all.o $(BUILD_DIR_NBODY-TEST)/gtest-all.d: CXXFLAGS += -I$(GTEST_DIR)/include -I$(GTEST_DIR) -I$(DEV_DIR)/test
# Need to filter out -Weffc++ flag (or gtest won't compile)
#$(BUILD_DIR_NBODY-TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(OBJECTS_NBODY-TEST) : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(BUILD_DIR_NBODY-TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Wextra,$(CXXFLAGS))
