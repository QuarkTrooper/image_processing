
# === INFO ==============================================================
# This project is to understand image convolution and different algos
# to apply this for filtering images. By no means meant to work with no
# flaws. It's merely a proop of concept to understand these things and
# to learn Python better in the process.
# =======================================================================

import timeit
import cv2 as cv
import numpy as np
import sys
from ext_fcn import *
from alex_image_convolution import alex_convolution as conv

timeStart = timeit.default_timer()

# ************************
# Load image file
# ************************

img = cv.imread("C:/Users/alexa/Documents/Programming/Projects/image_processing_training/convolution_test/test_image.jpg")
if img is None:
    sys.exit("Could not read the image.")

# ************************
# Process and show ROI
# ************************

print("jpg image size: " + str(img.shape))

imGray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
print("b/w image size: " + str(imGray.shape))

roi = imGray[1500:2000, 1500:2000] # [Y, X]

#roiScaledClean = cv.resize(roi, (1200, 600)) # [X, Y]
#cv.imshow("Clean ROI", roiScaledClean)
cv.imshow("Clean ROI", roi)

# ************************
# Convolve ROI
# ************************

# ==================
# 9x9 box blur
# ==================

square_blur_kernel = np.ones((9, 9))

print("blurring 9x9")
roiBlurred9x9 = conv(roi, square_blur_kernel)
cv.imshow("Blurred ROI 9x9", roiBlurred9x9)

## ==================
## Edge detection 1
## ==================
#
#edge_detect_kernel = np.matrix([[1, 0, -1], [0, 0, 0], [-1, 0, 1]])
#
#print("Edge detection 1")
#roiEdgeDetect1 = conv(roi, edge_detect_kernel)
#
#roiScaledEdgeDetect = cv.resize(roiEdgeDetect1, (1200, 600)) # [X, Y]
#cv.imshow("Edge Detection 1", roiScaledEdgeDetect)

# ==================
# END
# ==================

print("DONE!")
print("Processing these images took " + str((timeit.default_timer() - timeStart)/60) + " minutes")

k = cv.waitKey(0)