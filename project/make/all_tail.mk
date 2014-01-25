# Here we set up the directories that all of the 
# object files will be ending up in.
BUILD_DIRS := $(BUILD_DIR_NBODY) $(BUILD_DIR_NBODY-TEST)
$(BUILD_DIRS) $(INSTALL_DIR)/bin $(INSTALL_DIR)/include $(INSTALL_DIR)/lib $(INSTALL_DIR)/test :
	$(MKDIR) $@

TARGETS := $(TARGET_NBODY) $(TARGET_NBODY-TEST)
OBJECTS := $(OBJECTS_NBODY) $(OBJECTS_NBODY-TEST)

all : $(TARGETS)

%-test.x : | $(INSTALL_DIR)/test
	$(LD) -o $@ $^ $(LDFLAGS)
	$@

%.a : | $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	$(AR) rcs $@ $^

%.x : | $(INSTALL_DIR)/bin
	$(LD) -o $@ $^ $(LDFLAGS)

$(TARGET_NBODY) : $(OBJECTS_NBODY)
$(TARGET_NBODY-TEST) : $(OBJECTS_NBODY-TEST)

$(OBJECTS_NBODY) : | $(BUILD_DIR_NBODY)
$(OBJECTS_NBODY-TEST) : | $(BUILD_DIR_NBODY-TEST)

COMPILE_CXX = $(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c -o $@ $<
$(BUILD_DIR_NBODY)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY-TEST)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY-TEST)/%.o : %.cc ; $(COMPILE_CXX)

clean:
	$(RM) -r $(TARGETS) $(BUILD_DIRS) $(ARTIFACTS)

.PHONY : all clean

.PRECIOUS : %-test.x
