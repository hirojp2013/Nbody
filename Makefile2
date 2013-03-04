CXX = g++
DEBUGOPT = -g
CFLAGS = `pkg-config --cflags libpng` -I/usr/X11R6/include -I/usr/local/CAVE/include
	
LDLIBS = -L/usr/X11R6/lib64 -L/usr/local/CAVE/lib64 -lcave_ogl_mt -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread\
	`pkg-config --libs libpng`

TARGET = viewptc
OBJS = Particle.o common.o ui.o binary.o motion.o main.o \
	 angular_vel.o arrow.o color_legend_hue.o \
	hsv.o Particle_Objs.o pointsprite.o snapshot.o

.SUFFIXES : .cpp .o

.cpp.o :
	${CXX} ${DEBUGOPT} -c  ${CFLAGS} $<
#.cpp.o :
#	${CXX} -c ${CFLAGS} $<

${TARGET} : ${OBJS}
	${CXX} ${DEBUGOPT} -o $@ ${OBJS} ${LDLIBS}
#${TARGET} : ${OBJS}
#	${CXX} -o $@ ${OBJS} ${LDLIBS}
#makefile :
#	cp Makefile.mk Makefile
#	${CXX} -c -MM ${CFLAGS} ${OBJS:.o=.cpp} >> Makefile

clean :
	rm -f *.o ${TARGET}

Particle.o: Particle.cpp Particle.h /usr/local/CAVE/include/cave_ogl.h
common.o: common.cpp common.h Particle.h \
  /usr/local/CAVE/include/cave_ogl.h
ui.o: ui.cpp ui.h common.h Particle.h /usr/local/CAVE/include/cave_ogl.h
motion.o: motion.cpp motion.h common.h Particle.h \
  /usr/local/CAVE/include/cave_ogl.h
main.o: main.cpp common.h Particle.h /usr/local/CAVE/include/cave_ogl.h \
  ui.h motion.h
Particle_Objs.o: Particle_Objs.cpp
binary.o: binary.cpp
angular_vel.o: angular_vel.cpp
arrow.o: arrow.cpp
color_legend_hue.o: color_legend_hue.cpp
hsv.o: hsv.cpp
Particle_Objs.o: Particle_Objs.cpp
pointsprite.o: pointsprite.cpp
snapshot.o: snapshot.cpp