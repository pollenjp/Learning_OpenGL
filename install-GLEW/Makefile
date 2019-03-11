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
GLFW_VERSION := 3.2.1
GLEW_VERSION := 2.1.0
ERROR_MESSAGE :=

CXX := g++
CXXFLAGS = -g -Wall -std=c++11
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

#===============================================================================
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


#===============================================================================
.PHONY : preprocess
preprocess :
# [Bash - adding color - NoskeWiki printf zsh](http://www.andrewnoske.com/wiki/Bash_-_adding_color)
ifndef GLFW_VERSION
	@printf "\e[101m Variable GLFW_VERSION does not set. \e[0m \n"
	@${MAKE} error ERROR_MESSAGE="GLFW_VERSION"
endif
ifndef GLEW_VERSION
	@printf "\e[101m Variable GLEW_VERSION does not set. \e[0m \n"
	@${MAKE} error ERROR_MESSAGE="GLEW_VERSION"
endif

.PHONY : error
error :  ## errors処理を外部に記述することで好きなエラーメッセージをprintfで記述可能.
	$(error "${ERROR_MESSAGE}")

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core


#===============================================================================
.PHONY : install-glew
install-glew :
	@$(MAKE) preprocess
	GLEW_VERSION=${GLEW_VERSION} ./install-glew.bash.sh


