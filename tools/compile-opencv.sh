#! /bin/bash -xe
#
sudo apt-get install -y build-essential
sudo apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev python3-dev python3-numpy python3
sudo apt-get install -y dov4l dv4l libv4l-0 libv4l-dev libwebcam0 libwebcam0-dev v4l-conf v4l-utils v4l2ucp
# If the version of OpenCV is changed, the next three lines need to be edited.
mkdir ~/src/opencv-3.4.3/build
cd ~/src/opencv-3.4.3/build
cmake -D CMAKE_BUILD_PATH=/usr/local -D CMAKE_BUILD_TYPE=Release -D BUILD_EXAMPLES=OFF -D PYTHON3_EXECUTABLE=`which python3` -D BUILD_EXAMPLES=OFF -D HAVE_CUDA=NO -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D WITH_V4L=YES -D WITH_LIBV4L=YES -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-3.4.3/modules ..
make
make install

