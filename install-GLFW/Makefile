#===============================================================================
CC := g++
CXXFLAGS = -g -Wall -std=c++11
GLFW_VERSION :=

# [gcc -l -L option flags for library link](https://www.rapidtables.com/code/linux/gcc/gcc-l.html)
# [gcc -I option flag (include directory)](https://www.rapidtables.com/code/linux/gcc/gcc-i.html)
LDLIBS1 := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/lib
LDLIBS2 := glfw3 dl X11 Xxf86vm Xinerama Xrandr Xcursor Xi pthread
LDLIBS := $(addprefix -L,${LDLIBS1}) $(addprefix -l,${LDLIBS2})
INC := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/include
INC := $(addprefix -I,${INC})

OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := check_version

${TARGET} : ${TARGET}.cpp
% : %.cpp
#${TARGET} : ${OBJECTS}
	$(LINK.cc) $^ ${INC} ${LDLIBS} -o $@

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core


#===============================================================================
.PHONY : install-glfw
install-glfw :
	GLFW_VERSION=${GLFW_VERSION} ./install-glfw.bash.sh


