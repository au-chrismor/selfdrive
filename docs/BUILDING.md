# How to build everything #

## Python ##

We're using Python 3. Live with it...

## OpenCV ##

The upper layers of the project rely on OpenCV 3.4 or later.  When there is a new release of OpenCV 3, I rebuild and test against that.  After that I will bring that release into the opencv and opencv_contrib trees under /src.  If you want to build your own OpenCV, that's entirely up to you.

Detailed instructions can be found at https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html but in summary:

Make sure you have the pre-requisites are in place

* gcc 4.4 or later
* cmake 2.8.7 or later
* git
* libgtk-3-dev
* pkg-config
* libavcodec-dev
* libavformat-dev
* libswscale-dev
* python3-dev
* python3-numpy
* libtbb2
* libtbb-dev
* libjpeg-dev
* libpng-dev
* libtiff-dev
* libavresample-dev
* libgphoto2-dev
* libopenblas-dev
* libatlas-dev
* liblapack-dev

### Settings for OpenCV ###

As per the standard build docs, *do not build OpenCV in the source directory*, but create a build directory and change into there.

Configure OpenCV with cmake as follows:

cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=[path]/opencv_contrib -D PYTHON3_EXECUTABLE=\`which python3\` ..

cmake will take a while to run (especially on a Raspberry Pi) so be patient.  Errors will probably be the result of a missing dependency or typo, but the cmake output will help you track it down

After cmake is finished run a standard make with:

make -j n

where n is a number equal to the cores available.  This takes a considerable amount of time to run, so go get a coffee...

When make is done without error, install everything with:

sudo make install

