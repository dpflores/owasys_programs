#Compiler
ARM_CC = arm-linux-gnueabihf-gcc
ARM_CC_83 = arm-linux-gnueabihf-8.3-gcc

#STRIP
ARM_STRIP = arm-linux-gnueabihf-strip
ARM_STRIP_83 = arm-linux-gnueabihf-8.3-strip

#Compiler flags for the test program
#CFLAGS = -Wall -g -ggdb
CFLAGS = -Wall -mthumb -mthumb-interwork -D_REENTRANT

#OBJECTS
OBJECT = owa4x_AN3

#Source Files
SOURCE = ./*.c

#LIBS to include
LIBS = -ldl
LIBS += -lpthread

MSG_BUILD = Building owa4x_AN3 Object


all: build

build:
	@echo
	@echo $(MSG_BUILD)
	$(ARM_CC) $(CFLAGS) -o$(OBJECT) $(SOURCE) $(LIBS)
	$(ARM_STRIP) $(OBJECT)
	mv $(OBJECT) ./release_53/
	
	@echo $(MSG_BUILD)
	$(ARM_CC_83) $(CFLAGS) -o$(OBJECT) $(SOURCE) $(LIBS)
	$(ARM_STRIP_83) $(OBJECT)
	mv $(OBJECT) ./release_83/
	
