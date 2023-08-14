#!/usr/bin/python3
#
import cv2

def process_image(image):
    (h, w, d) = image.shape
    print("width={}, height={}, depth={}".format(w, h, d))
    #roi = image[0:480, 0:1280]
    roi1 = image[0:480, 0:639]

    grey = cv2.cvtColor(roi1, cv2.COLOR_BGR2GRAY)
    cv2.imshow("Image 1", roi1)
    cv2.imshow("Grey", grey)
    cv2.waitKey(0)

process_image(cv2.imread("image.jpg"))
