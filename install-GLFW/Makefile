CXX := g++
CXXFLAGS = -g -Wall -std=c++11
GLFW_VERSION := 3.2.1

INC := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/include
INC := $(addprefix -I,${INC})
LDLIBS1 := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/lib
LDLIBS2 := glfw3 dl X11 Xxf86vm Xinerama Xrandr Xcursor Xi pthread
LDLIBS := $(addprefix -L,${LDLIBS1}) $(addprefix -l,${LDLIBS2})
LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) ${LDFLAGS} $(TARGET_ARCH)

OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := check_version
export

.DEFAULT_GOAL : run

${TARGET} : ${OBJECTS}

%.o : %.cpp
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ ${INC} ${LDLIBS} -c -o $@
% : %.o
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $^ ${LDLIBS} -o $@

.PHONY : run
run :  # 要件チェック
	${MAKE} ${TARGET}
	./${TARGET}

.PHONY : preprocess
preprocess :  # 要件チェック
ifndef GLFW_VERSION
	$(error "=== The GLFW_VERSION variable should be set ===")
endif

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core


#===============================================================================
.PHONY : install-glfw
install-glfw :
	@$(MAKE) preprocess
	GLFW_VERSION=${GLFW_VERSION} ./install-glfw.bash.sh


