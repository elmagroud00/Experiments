TARGET = player


CROSS_COMPILE =

#####################################
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)g++
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump
LN				= ln -f
CHMOD			= chmod

#####################################
CFLAGS += -DENABLE_AVIN_NULL=1
CFLAGS += -DENABLE_AVIN_FILE=1
CFLAGS += -DENABLE_AVIN_HA2=1

CFLAGS += -DENABLE_VO_NULL=1
CFLAGS += -DENABLE_AO_NULL=1

CFLAGS += -DENABLE_VO_SDL=1
CFLAGS += -DENABLE_VO_X11=1
CFLAGS += -DENABLE_VO_FB=1
CFLAGS += -DENABLE_VO_GL=1
CFLAGS += -DENABLE_VO_DIRECTX=0

CFLAGS += -DENABLE_AO_SDL=1
CFLAGS += -DENABLE_AO_ALSA=1
CFLAGS += -DENABLE_AO_OSS=1
CFLAGS += -DENABLE_AO_DSOUND=0
#####################################

#CFLAGS += -I. -I/usr/local/include -g -fomit-frame-pointer -Wdeclaration-after-statement -Wall -Wno-switch -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -O3 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_ISOC9X_SOURCE
CFLAGS += -I. -I/usr/local/include -g -Wall  -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_ISOC9X_SOURCE -D__STDC_CONSTANT_MACROS

LDFLAGS += -lavformat -lxml2 -lavcodec  -lavutil -lswscale -lfaad -lvdpau -ljpeg  -lpng -lglut -lGLEW -lGLU -lGL -lm -lz -lpthread -lX11 -lSDL

#####################################

SRC=$(wildcard *.cpp)
OBJS=${SRC:%.cpp=%.o}
NAME=${SRC:%.cpp=%}
DEPS=$(SRC:%.cpp=.dep/%.d)

.PHONY: dep  all

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) 
#	$(STRIP) $(TARGET)


clean:
	rm -rf *.o $(TARGET) .dep

%.o: %.cpp
	${CC} ${CFLAGS} -c $<
	@mkdir -p .dep
	${CC} -MM $(CFLAGS) $*.cpp > .dep/$*.d 


dep: 
	@mkdir -p .dep
	for i in ${NAME} ; do  \
		${CC} -MM $(CFLAGS) "$${i}".cpp > .dep/"$${i}".d ;\
	done

