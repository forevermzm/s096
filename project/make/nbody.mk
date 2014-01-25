# Virtual path directive - find all 
vpath %.cpp src

NBODY_NAME := nbody

## The actual result of building this project:
## a static library named 'libnbody.a'.
TARGET_NBODY := $(INSTALL_DIR)/lib/lib$(NBODY_NAME).a
$(TARGET_NBODY) : | $(INSTALL_DIR)/include/$(NBODY_NAME)

## Where to put all of the compiled object files
BUILD_DIR_NBODY := $(BUILD_DIR)/$(NBODY_NAME)

## List of object files to produce (from the similarly
## named .cpp files). Add any extra files you want to have
## compiled here.
OBJECTS_NBODY := \
	$(BUILD_DIR_NBODY)/gcd.o \
	$(BUILD_DIR_NBODY)/rational.o \
	#$(BUILD_DIR_NBODY)/add.o \
	#$(BUILD_DIR_NBODY)/any.o \
	#$(BUILD_DIR_NBODY)/other.o \
	#$(BUILD_DIR_NBODY)/files.o \
	#$(BUILD_DIR_NBODY)/here.o \

## Copies over the public header files to install/include
$(INSTALL_DIR)/include/$(NBODY_NAME) ::
	$(MKDIR) $@
	$(RSYNC) include/$(NBODY_NAME)/ $@/

## Add the public include files to the list of artifacts
## to be cleaned up on a 'make clean'
ARTIFACTS += $(INSTALL_DIR)/include/$(NBODY_NAME)

