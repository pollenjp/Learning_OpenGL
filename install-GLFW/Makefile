CXX := g++
CXXFLAGS = -g -Wall -std=c++11
GLFW_VERSION := 3.2.1

INC := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/include
INC := $(addprefix -I,${INC})
LDFLAGS1 := ${HOME}/.glfw/install/GLFW-${GLFW_VERSION}/lib
LDFLAGS2 := glfw3 dl X11 Xxf86vm Xinerama Xrandr Xcursor Xi pthread
LDFLAGS := $(addprefix -L,${LDFLAGS1}) $(addprefix -l,${LDFLAGS2})
LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) ${LDFLAGS} $(TARGET_ARCH)

OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := check_version
export

.DEFAULT_GOAL : run

${TARGET} : ${OBJECTS}

%.o : %.cpp
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ ${INC} ${LDFLAGS} -c -o $@
% : %.o
	@$(MAKE) preprocess
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $^ ${LDFLAGS} -o $@

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


