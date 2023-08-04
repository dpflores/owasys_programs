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
OBJECT = IO_OWASYS

#Source Files
SOURCE = ./*.c

#LIBS to include
LIBS = -ldl
LIBS += -lpthread


all: 
	$(ARM_CC_83) $(CFLAGS) -o$(OBJECT) $(SOURCE) $(LIBS)
	$(ARM_STRIP_83) $(OBJECT)
	
