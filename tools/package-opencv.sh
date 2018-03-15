#! /bin/bash -xe
#
cd /usr/local
tar -cvzf /tmp/opencv-dist-$ARCH.tar.gz bin/opencv* lib/libopencv* lib/python3.5/* lib/python2.7* include/opencv include/opencv2 share/OpenCV
#
mv /tmp/opencv-dist-$ARCH.tar.gz $DISTDIR

