#Compiler
ARM_CC = arm-linux-gnueabihf-gcc
#OBJECT
OBJECT = GPS_OWASYS_BACKGROUND_LS
#DEFINITIONS
DEFS = -DTRACES_VERIFICATION
DEFS += -DDEBUG_TRACES

#Source Files
SOURCE_FILE = *.c

#INCLUDE
#INCLS = -I../../owasys/include
#LIBS to include
LIBS = -ldl
LIBS += -lpthread -mthumb -mthumb-interwork -D_REENTRANT
LIBS += -lRTU_Module -lIOs_Module -lGPS2_Module
#STRIP
ARM_STRIP = arm-linux-gnueabihf-strip

all:
	$(ARM_CC) -Wall $(DEFS) -o$(OBJECT) $(SOURCE_FILE) $(INCLS) $(LIBS)
	$(ARM_STRIP) $(OBJECT)
