'''
    Copyright (C) 2018, by Christopher F. Moran and Emergent Technology
    This is original work contains products developed by other organisations
    including, but not limited to:
    OpenCV, Python Core Team

    This module receives a frame stream from the '0' video device and reduces
    it for processing in the same way we do with the on-board software.  The resulting
    stream is saved for analysis.
'''
import numpy as np
import cv2
import linecache
import sys

hasGui = True
hasStereoCam = False


'''
    Exception Handler
'''
def printException():
	exc_type, exc_obj, tb = sys.exc_info()
	f = tb.tb_frame
	lineNumber = tb.tb_lineno
	fileName = f.f_code.co_filename
	linecache.checkcache(fileName)
	line = linecache.getline(fileName, lineNumber, f.f_globals)
	print('EXCEPTION IN ({}, LINE {} "{}"): {}'.format(fileName, lineNumber, line.strip(), exc_obj))


'''
	Split and combine the stereo image
	This allows us to merge the data from an ELP Stereo Camera
'''
def splitFrame(frame):
	if hasStereoCam:
		try:
			frame_height = frame.shape[0]
			frame_width = frame.shape[1]
			crop1 = frame[0:frame_height, 0:frame_width / 2]
			crop2 = frame[0:frame_height, frame_width / 2:frame_width]
			result = cv2.addWeighted(crop1, 0.5, crop2, 0.5, 0)
		except Exception as ex:
			printException()
			result = None

		return result 
	else:
		return frame

def makeSmallFrame(frame, startC, startR, endC, endR):
	try:
		print('startC={} startR={} endC={} endR={}'.format(startC, startR, endC, endR))
		result = frame[startC:startR, endC:endR]
	except Exception as ex:
		printException()
		result = None

	return result
'''
	Reduce the captured image to the simplest form for mapping:
		This process follows a simple set of steps to return an object with only border
		objects from an original full-colour image.

'''
def reduceFrame(frame):
	kernel = np.ones((5,5),np.uint8)
	# Our operations on the frame come here
	grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	blur = cv2.GaussianBlur(grey, (5, 5), 0)
#	cv2.imshow('Blur', blur)
	eql = cv2.equalizeHist(blur)
	ret, thold = cv2.threshold(eql, 125, 255, cv2.THRESH_BINARY)
#	cv2.imshow('Threshold', thold)
	erosion = cv2.erode(thold, kernel, iterations = 1)
#	cv2.imshow('Erode', erosion)
	return erosion


cap = cv2.VideoCapture(0)
fourcc = cv2.VideoWriter_fourcc('H','2','6','4')
out = cv2.VideoWriter('output.mkv', fourcc, 20.0, (640, 480))

while True:
	try:
		# Capture frame-by-frame
		ret, frame = cap.read()

		frame = splitFrame(frame)	


		redFrame = reduceFrame(frame)
		row1Top = int(frame.shape[0] / 2)
		row1Bot = int(frame.shape[0] / 2 + 50)
		row2Top = int(frame.shape[0] / 2 - 50)
		row2Bot = row1Top

		# Get the moments from the frame
		#m = cv2.moments(makeSmallFrame(redFrame, startC = 0, startR = 0, endC = redFrame.shape[1], endR = redFrame.shape[0]))
		print(makeSmallFrame(redFrame, startC=0, startR=0, endC=128, endR=128))
		m = cv2.moments(redFrame)
		x = m['m10'] / m['m00']
		y = m['m01'] / m['m00']
		print(x, y)

		if hasGui:
			cv2.rectangle(frame, (0, row1Top), (frame.shape[1], row1Bot), (255, 255, 255), 1)
			cv2.rectangle(frame, (0, row2Top), ((int(frame.shape[1] / 3)), row2Bot), (255, 0, 255), 3)
			cv2.rectangle(frame, ((int(frame.shape[1] / 3)), row2Top), ((int(frame.shape[1] / 3 * 2)), row2Bot), (0, 255, 0), 3)
			cv2.rectangle(frame, ((int(frame.shape[1] / 3 * 2)), row2Top), ((int(frame.shape[1])), row2Bot), (0, 0, 255), 3)

#			cv2.circle(frame, (int(x + 100), int(row1Bot - y)), 10, (255, 255, 255), 1, 8)
			cv2.circle(frame, (int(x), int(y)), 10, (255, 255, 255), 2, 8)

			cv2.namedWindow('Live', cv2.WINDOW_NORMAL)
			cv2.imshow('Live', frame)
#			cv2.imshow('Processed', redFrame)


		# Display the resulting frame
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break
		out.write(redFrame)
	except Exception as ex:
		printException()

# When everything is done, release the capture
out.release()
cap.release()
cv2.destroyAllWindows()



