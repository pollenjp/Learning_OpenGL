#CXX := g++
#CXXFLAGS = -g -Wall -std=c++11
#GLEW_VERSION := 2.1.0
#
#INC := ${HOME}/.glew/install/GLEW-${GLEW_VERSION}/include
#INC := $(addprefix -I,${INC})
#LDLIBS1 := ${HOME}/.glew/install/GLEW-${GLEW_VERSION}/lib
#LDLIBS2 := GLEW GL
#LDLIBS := $(addprefix -L,${LDLIBS1}) $(addprefix -l,${LDLIBS2})
#LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) ${LDFLAGS} $(TARGET_ARCH)

CXX := g++
CXXFLAGS = -g -Wall -std=c++11
GLFW_VERSION := 3.2.1
GLEW_VERSION := 2.1.0

INC := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/include \
       ${HOME}/.glew/install/GLEW-${GLEW_VERSION}/include
INC := $(addprefix -I,${INC})
LDLIBS1 := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/lib \
           ${HOME}/.glew/install/GLEW-${GLEW_VERSION}/lib
LDLIBS2 := GL glfw3 GLEW dl X11 Xxf86vm Xinerama Xrandr Xcursor Xi pthread
LDLIBS := $(addprefix -L,${LDLIBS1}) $(addprefix -l,${LDLIBS2})
LINK.cc := $(CXX) $(CXXFLAGS) $(CPPFLAGS) ${LDFLAGS} $(TARGET_ARCH)


OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := check_version
export

.DEFAULT_GOAL := run

${TARGET} : ${OBJECTS}

%.o : %.cpp
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ ${INC} ${LDLIBS} -c -o $@
% : %.o
	@$(MAKE) preprocess
	$(LINK.cc) $(TARGET_ARCH) $^ ${LDLIBS} -o $@

.PHONY : run
run :  # 要件チェック
	${MAKE} ${TARGET}
	./${TARGET}

.PHONY : preprocess
preprocess :  # 要件チェック
ifndef GLEW_VERSION
	$(error "=== The GLEW_VERSION variable should be set ===")
endif

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core


#===============================================================================
.PHONY : install-glew
install-glew :
	@$(MAKE) preprocess
	GLEW_VERSION=${GLEW_VERSION} ./install-glew.bash.sh


