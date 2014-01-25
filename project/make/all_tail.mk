# Here we set up the directories that all of the 
# object files will be ending up in.

all : $(TARGET_NBODY) $(TARGET_NBODY-TEST)

%-test.x : | $(INSTALL_DIR)/test
	$(LD) -o $@ $^ $(LDFLAGS)
	$@

%.a : | $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	$(AR) rcs $@ $^

%.x : | $(INSTALL_DIR)/bin
	$(LD) -o $@ $^ $(LDFLAGS)

$(TARGET_NBODY) : $(OBJECTS_NBODY)
$(TARGET_NBODY-TEST) : $(OBJECTS_NBODY-TEST)

$(OBJECTS_NBODY) $(patsubst %.o,%.d, $(OBJECTS_NBODY)) : | $(BUILD_DIR_NBODY)
$(OBJECTS_NBODY-TEST) $(patsubst %.o,%.d, $(OBJECTS_NBODY-TEST)) : | $(BUILD_DIR_NBODY-TEST)

BUILD_DIRS := $(sort $(BUILD_DIR_NBODY) $(BUILD_DIR_NBODY-TEST))
TARGETS := $(sort $(TARGET_NBODY) $(TARGET_NBODY-TEST))
OBJECTS := $(sort $(OBJECTS_NBODY) $(OBJECTS_NBODY-TEST))

$(BUILD_DIRS) $(INSTALL_DIR)/bin $(INSTALL_DIR)/include $(INSTALL_DIR)/lib $(INSTALL_DIR)/test :
	$(MKDIR) $@

COMPILE_CXX = $(CXX) -c -o $@ $< $(CXXFLAGS) $(DEBUG_FLAGS) 
$(BUILD_DIR_NBODY)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY-TEST)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_NBODY-TEST)/%.o : %.cc ; $(COMPILE_CXX)

$(addsuffix %.d, $(BUILD_DIRS)/) : %.cpp
	$(SHELL) -ec "$(CXX) $(CXXFLAGS) -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

$(addsuffix %.d, $(BUILD_DIRS)/) : %.cc
	$(SHELL) -ec "$(CXX) $(CXXFLAGS) -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

$(OBJECTS) : %.o : %.d

-include $(patsubst %.o,%.d,$(OBJECTS))

clean:
	$(RM) -r $(TARGETS) $(BUILD_DIRS) $(ARTIFACTS)

.PHONY : all clean

.PRECIOUS : %-test.x

