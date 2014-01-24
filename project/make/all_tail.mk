# Here we set up the directories that all of the 
# object files will be ending up in.
BUILDDIRS := $(BUILD_DIR_PROJECT) $(BUILD_DIR_PROJECT_TEST)
$(BUILDDIRS) $(INSTALL_DIR)/bin $(INSTALL_DIR)/include $(INSTALL_DIR)/lib $(INSTALL_DIR)/test :
	$(MKDIR) $@

TARGETS := $(TARGET_PROJECT) $(TARGET_PROJECT_TEST)

all : $(TARGETS)

%-test.x : | $(INSTALL_DIR)/test
	$(LD) -o $@ $^ $(LDFLAGS)
	$@

%.a : | $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	$(AR) rcs $@ $^

%.x : | $(INSTALL_DIR)/bin
	$(LD) -o $@ $^ $(LDFLAGS)

$(TARGET_PROJECT) : $(OBJECTS_PROJECT)
$(TARGET_PROJECT_TEST) : $(OBJECTS_PROJECT_TEST)

$(OBJECTS_PROJECT) : | $(BUILD_DIR_PROJECT)
$(OBJECTS_PROJECT_TEST) : | $(BUILD_DIR_PROJECT_TEST)

COMPILE_CXX = $(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c -o $@ $<
$(BUILD_DIR_PROJECT)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_PROJECT_TEST)/%.o : %.cpp ; $(COMPILE_CXX)

clean:
	$(RM) -r $(TARGETS) $(BUILDDIRS) $(ARTIFACTS)

.PHONY : all clean

#.PRECIOUS : %-test.x
