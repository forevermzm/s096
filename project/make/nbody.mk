# Virtual path directive - find all 
vpath %.cpp src

NBODY_NAME := nbody

BUILD_DIR_NBODY := $(BUILD_DIR)/$(NBODY_NAME)
TARGET_NBODY := $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a

$(TARGET_NBODY) : | $(INSTALL_DIR)/include/$(NBODY_NAME)

OBJECTS_NBODY := \
	$(BUILD_DIR_NBODY)/gcd.o \
	$(BUILD_DIR_NBODY)/rational.o \
	#$(BUILD_DIR_NBODY)/add.o \
	#$(BUILD_DIR_NBODY)/any.o \
	#$(BUILD_DIR_NBODY)/other.o \
	#$(BUILD_DIR_NBODY)/files.o \
	#$(BUILD_DIR_NBODY)/here.o \

$(INSTALL_DIR)/include/$(NBODY_NAME) ::
	$(MKDIR) $@
	$(RSYNC) include/$(NBODY_NAME)/ $@/

ARTIFACTS += $(INSTALL_DIR)/include/$(NBODY_NAME)

