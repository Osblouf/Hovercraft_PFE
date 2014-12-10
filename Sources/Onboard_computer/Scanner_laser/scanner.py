## @file Scanner.py
#  @brief Scanner laser module.
#  @author Loic Dalloz
#  @version 2.0
#
#import picamera
#import picamera.array
import cv2
import numpy as np
import time
import math

## Scanner laser module.
# Fields :
#   - self.x         => x resolution
#   - self.y         => y resolution
#   - self.half      => half of the image (where the distance is calculated in the plan
#   - self.camera    => THE camera !
#   - self.image     => Where the pictures are stored
#   - self.mask      => Where the mask is located
#   - self.upper_red => Max color (for the mask)
#   - self.lower_red => Min color (for the mask)
#   - self.d        |
#   - self.k        |=> Scanner calibration coefs
#   - self.N        |
#   - self.cap       => Opencvcapture object
#
# Usages :
#   Calibration :
#       s = Scanner.Scanner()
#       s.start_module()
#       s.calibration()
#       exit()
#
#   Scanning :
#       s = Scanner.Scanner()
#       s.load_configs()
#       s.start_module()
#       while 1:
#           print Str(s.get_plan_distance())
#       exit()
#
class Scanner:
    ## Constructor.
    #  @param self The object pointer.
    def __init__(self):
        self.x = 0
        self.y = 0
        self.half = 0

    ## Start everything we need to capture photos.
    #  @param self The object pointer.
    def start_module(self):
        # Start the camera.
        self.cap = cv2.VideoCapture(0)
        compteur = 30
        max2 = 0
        # Calibrate
        while compteur > 0:
            ret, image = self.cap.read()
            if ret:
                compteur = compteur - 1
                if compteur > 10:
                    b, g, r = cv2.split(image)
                    max = np.amax(r)
                    if max > max2:
                        max2 = max

        if max2 > 254:
            max2 = 254

        # Init mask threshold.
        self.lower_red = np.array([0, 0, max2])
        self.upper_red = np.array([255, 255, 255])

        # Init resolution
        self.x = int(self.cap.get(4))
        self.y = int(self.cap.get(3))
        self.half = round(self.y * 0.63)

    ##  Take a picture.
    #   @param self The object pointer.
    def take_picture(self):
        ret, self.image = self.cap.read()
        while ret == False:
            ret, self.image = self.cap.read()

    ## build the mask.
    #  @param self The object pointer.
    def make_mask(self):
        self.mask = cv2.inRange(self.image, self.lower_red, self.upper_red)

    ## Get U (position of the laser in image)
    #  @param self The object pointer
    #  @return The position of the laser (in pixel)
    #  Find the position of the laser on the self.half row of the image.
    def get_U(self):
        rows, col = self.mask.shape
        liste = [j for j in xrange(col) if self.mask.item(self.half, j)==255]
        return np.mean(liste)

    ## Calibrate the scanner
    #  @param self The object pointer.
    #  Calibrate the scanner and store le calibration coeffs in a file "scan_config.txt"
    def calibration(self):
        print " "
        print " ________________________ "
        print "|                        |"
        print "|    Start calibration   |"
        print "|________________________|"
        print " "
        raw_input("Bring the target to 50cm of the camera then press ENTER...")
        print "Calibrating 50cm..."
        self.take_picture()
        self.take_picture()
        self.make_mask()
        u1 = self.get_U()
	cv2.imwrite("50cm.png", self.image)
	print "u = %s" % (str(u1))
        raw_input("Bring the target to 150cm of the camera then press ENTER...")
        print "Calibrating 150cm..."
        self.take_picture()
        self.take_picture()
        self.make_mask()
        u2 = self.get_U()
	cv2.imwrite("150cm.png", self.image)
	print "u = %s" % (str(u2))
        print "computing coefs..."
        self.d = 1500 - 500
        self.k = (u2*1.4)*1.5 - (u1*1.4)*0.5
        self.N = ((u1*1.4) - (u2*1.4))*1.5*500
        print "\td -> ", self.d
        print "\tk -> ", self.k
        print "\tN -> ", self.N
        print "Saving..."
        self.save_configs()
        cv2.destroyAllWindows()

    ## Get the distance (in cm)
    #  @param self The object pointer.
    #  @return The computed distance in the plan (in cm).
    #  The distance is calculated with the coeffs stored in the file scan_config.txt.
    def get_plan_distance(self):
        self.take_picture()
        self.take_picture()
        self.make_mask()
        u = self.get_U()
        dist = (self.N/((u*1.4)-self.k))/10
        return dist

    ## Load the calibration coefs
    #  @param self The object pointer.
    def load_configs(self):
        file = open("scan_config.txt", "r")
        self.x = int(file.readline())
        self.y = int(file.readline())
        self.d = float(file.readline())
        self.k = float(file.readline())
        self.N = float(file.readline())
        file.close()
        print ""
        print "Loaded scanner values :"
        print "\td -> " + str(self.d)
        print "\tk -> " + str(self.k)
        print "\tN -> " + str(self.N)

    ## Save calibration coefs
    #  @param The object pointer.
    # File format :
    #   ________________
    #   |x resolution   |
    #   |y resolution   |
    #   |d              |
    #   |k              |
    #   |N              |
    #   |EOF            |
    #   |_______________|
    def save_configs(self):
        file = open("scan_config.txt", "w")
        file.write(str(self.x) + "\n")
        file.write(str(self.y) + "\n")
        file.write(str(self.d) + "\n")
        file.write(str(self.k) + "\n")
        file.write(str(self.N) + "\n")
        file.close()







