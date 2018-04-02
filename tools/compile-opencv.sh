#! /bin/bash -xe
#
mkdir src/opencv/build
cd src/opencv/build
cmake -D CMAKE_BUILD_PATH=/usr/local -D CMAKE_BUILD_TYPE=Release -D BUILD_EXAMPLES=OFF -D PYTHON3_EXECUTABLE=`which python3` -D BUILD_EXAMPLES=OFF -D HAVE_CUDA=NO -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D WITH_V4L=YES -D WITH_LIBV4L=YES ..
make
make install

