## Here we set up the directories that all of the 
## object files will be ending up in.

BUILD_DIRS := $(sort $(BUILD_DIR_NBODY)/ $(BUILD_DIR_NBODY_TEST)/)
TARGETS := $(sort $(TARGET_NBODY) $(TARGET_NBODY_TEST))
OBJECTS := $(sort $(OBJECTS_NBODY) $(OBJECTS_NBODY_TEST))

all : $(TARGETS)
nbody : $(TARGET_NBODY)
nbody-test : $(TARGET_NBODY_TEST)

## Set compile flags for debug mode by default
COMPILE_CXX = $(CXX) -c -o $@ $< $(INCLUDE_FLAGS) $(CXXFLAGS) $(DEBUG_FLAGS) 

## Running 'make release' will set compile flags to release mode
release : COMPILE_CXX = $(CXX) -c -o $@ $< $(INCLUDE_FLAGS) $(CXXFLAGS) $(RELEASE_FLAGS)
release : all

## Rule for making gtest executables:
## First we link %-test.x, then we execute it to run the unit tests.
%-test.x : | $(INSTALL_DIR)/test
	$(LD) -o $@ $^ $(LDFLAGS)
	$@

## Rule for making any static libraries. If you want to find out
## more, see http://linux.die.net/man/1/ar
%.a : | $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	$(AR) rcs $@ $^

## Rule for making any regular executables - link the object files.
%.x : | $(INSTALL_DIR)/bin
	$(LD) -o $@ $^ $(LDFLAGS)

$(TARGET_NBODY) : $(OBJECTS_NBODY)
$(TARGET_NBODY_TEST) : $(OBJECTS_NBODY_TEST)
$(OBJECTS_NBODY) $(patsubst %.o,%.d, $(OBJECTS_NBODY)) : | $(BUILD_DIR_NBODY)
$(OBJECTS_NBODY_TEST) $(patsubst %.o,%.d, $(OBJECTS_NBODY_TEST)) : | $(BUILD_DIR_NBODY_TEST)

$(BUILD_DIRS) $(INSTALL_DIR)/bin $(INSTALL_DIR)/include $(INSTALL_DIR)/lib $(INSTALL_DIR)/test :
	$(MKDIR) $@

$(BUILD_DIR_NBODY)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY)/%.o : %.cc ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY_TEST)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY_TEST)/%.o : %.cc ; $(COMPILE_CXX)

$(OBJECTS) : %.o : %.d

## For each required dependency file in BUILD_DIRS, we use sed and
## g++ -MM to generate a list of the included headers (dependencies)
$(addsuffix /%.d, $(BUILD_DIRS)) : %.cpp
	$(SHELL) -ec "$(CXX) -std=c++11 $(INCLUDE_FLAGS) -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

## You should name all of your files so they end in .cpp, but gtest
## gtest will have some files that end in .cc we need to take care of.
$(addsuffix /%.d, $(BUILD_DIRS)) : %.cc
	$(SHELL) -ec "$(CXX) -std=c++11 $(INCLUDE_FLAGS) -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

## Include the '.d' (dependencies) files; the leading '-' dash
## indicates that we don't want make to warn us if the files
## don't already exist.
-include $(patsubst %.o,%.d,$(OBJECTS))

## Command to remove all of the contents of the build/ directory
## related to our project and all of the generated executables
## and copied header files.
clean:
	$(RM) -r $(TARGETS) $(BUILD_DIRS) $(ARTIFACTS)

# These names don't represent real targets
.PHONY : all clean release nbody nbody-test

# Don't delete our unit test executable even if make is killed or 
# interrupted while it's being run.
.PRECIOUS : %-test.x
