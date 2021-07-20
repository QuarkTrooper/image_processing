import math
import numpy as np

def alex_convolution(imgIn, kernel):

    imgInHeight = imgIn.shape[0]
    imgInWidth = imgIn.shape[1]

    kernelHeight = kernel.shape[0]
    kernelWidth = kernel.shape[1]

    # Make sure the kernel has a center pixel.
    # I.e. has an odd number of rows and columns.
    if kernelWidth%2 == 0:
        raise Exception("Kernel has an even number of columns")
    if kernelHeight%2 == 0:
        raise Exception("Kernel has an even number of rows")

    padY = math.floor(kernelHeight/2)
    padX = math.floor(kernelWidth/2)

    imgConv = imgIn

    iY = 0
    while iY < imgInHeight:
        iX = 0
        while iX < imgInWidth:

            Ystart = max(iY-padY, 0) # at least 0
            Ystart = min(Ystart, imgInHeight-kernelHeight) # or max image height - kernel height
            Yend = max(iY+padY, kernelHeight-1) # at least kernel height
            Yend = min(Yend, imgInHeight-1) # or max image height
            Xstart = max(iX-padX, 0) # at least 0
            Xstart = min(Xstart, imgInWidth-kernelWidth) # or max image width - kernel width
            Xend = max(iX+padX, kernelWidth-1) # at least kernel width
            Xend = min(Xend, imgInWidth-1) # or max image width

            # === ISSUES ============================================================
            # I need to understand what's going on. I think there is an issue with
            # bit depth of the pixels that either cause rollover or saturation or
            # something else that makes the result a big mess... Blur seems to
            # work fine, as long as you take the mean and not the sum. However,
            # the sum should create a clean convolution, so I'm not sure. Need to
            # dig deeper into this!
            # =======================================================================

            convolutionRoi = np.multiply(imgIn[Ystart:Yend+1, Xstart:Xend+1], kernel)
            #convolutionRoi = np.multiply(imgIn[Ystart:Yend+1, Xstart:Xend+1], np.flipud(np.fliplr(kernel)))

            imgConv[iY, iX] = convolutionRoi.mean()
            #imgConv[iY, iX] = convolutionRoi.sum()

            iX = iX + 1 # Increment column

        # Print every 100 rows to show progress
        if iY%100 == 0:
            print("Row " + str(iY) + "/" + str(imgInHeight) + " completed!")

        iY = iY + 1 # Increment row

    return imgConv