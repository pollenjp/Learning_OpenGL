CXX := g++
CXXFLAGS = -g -Wall -std=c++11
GLFW_VERSION := 3.2.1

INC := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/include
INC := $(addprefix -I,${INC})
LDLIBS1 := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/lib
LDLIBS2 := GL glfw3 dl X11 Xxf86vm Xinerama Xrandr Xcursor Xi pthread
LDLIBS := $(addprefix -L,${LDLIBS1}) $(addprefix -l,${LDLIBS2})
LINK.cc := $(CXX) $(CXXFLAGS) $(CPPFLAGS) ${LDFLAGS} $(TARGET_ARCH)

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := sample
export

.DEFAULT_GOAL := run

%.o : %.cpp
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ ${INC} ${LDLIBS} -c -o $@

${TARGET} : ${OBJECTS}
	@$(MAKE) preprocess
	$(LINK.cc) $(TARGET_ARCH) $^ ${LDLIBS} -o $@

.PHONY : run
run :
	${MAKE} ${TARGET}
	./${TARGET}

.PHONY : preprocess
preprocess :
ifndef GLFW_VERSION
	$(error "=== The GLFW_VERSION variable should be set ===")
endif

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core

