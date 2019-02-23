#!/bin/bash -eux
#GLEW_VERSION=2.1.0
#NOTCLEAN  # flag : buildディレクトリルが存在していればそれを使う
GLEW_DIR="${HOME}/.glew"
CMAKE_INSTALL_PREFIX=${GLEW_DIR}/install/GLEW-${GLEW_VERSION}
# current working directory
CWD=$(pwd)

# [nigels-com/glew: The OpenGL Extension Wrangler Library](https://github.com/nigels-com/glew)

#=======================================
# Dependencies
sudo apt update -y
sudo apt install -y build-essential libxmu-dev libxi-dev libgl-dev

if [ ! -d "${GLEW_DIR}" ]; then
  mkdir ${GLEW_DIR}
fi
cd ${GLEW_DIR}

#=======================================
if [ ! -d "${GLEW_DIR}/glew" ]; then
  git clone https://github.com/nigels-com/glew.git
  https://github.com/nigels-com/glew/archive/glew-2.1.0.tar.gz
fi

cd "${GLEW_DIR}/glew"
git checkout glew-${GLEW_VERSION}
cd ..
 
#=======================================
directory1="${GLEW_DIR}/glew/build/cmake/build"
if [ -d "${directory1}" ] && [ -z ${NOTCLEAN+x} ]; then
  # ${NOTCLEAN} is unset
  rm -rf ${directory1}
  mkdir ${directory1}
fi
if [ ! -d "${directory1}" ]; then
  mkdir ${directory1}
fi
cd ${directory1}
cmake \
      -D CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} \
      ..
make -j4
if [ -d "${CMAKE_INSTALL_PREFIX}" ]; then
  rm -rf ${CMAKE_INSTALL_PREFIX}
fi
make install

#=======================================
#  Back to working directory
cd ${CWD}

