import sensor, image, time
import pyb
from math import atan2, sqrt
from pyb import UART

ROBOT_A = False
ATTACK_BLUE = False
DEGREES_TO_RADIANS = 0.017453292519943295769236907684886
RADIANS_TO_DEGREES = 57.295779513082320876798154814105

# Individual
if ROBOT_A:
    thresholds = [((83, 98, -28, 14, 22, 63),), ((58, 80, -28, -9, -41, -12),)] # Yellow  is first
else:
    thresholds = [((63, 79, -3, 18, 20, 59),), ((40, 54, -16, 6, -37, -16),)] # Yellow  is first

# Superteam
#if ROBOT_A:
    #thresholds = [((39, 57, 5, 40, 8, 57),), ((17, 26, -2, 41, -59, -14),)] # Yellow  is first
#else:
    #thresholds = [((38, 61, 4, 43, 7, 64),), ((16, 21, -1, 23, -35, -16),)] # Yellow  is first

sensor.reset()
redLED = pyb.LED(1)
redLED.on()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False, (-5.623446, -6.02073, -1.317097))
sensor.set_brightness(1)
sensor.set_contrast(0)
sensor.set_saturation(2)
clock = time.clock()
uart = UART(3, 115200, timeout_char = 10)
redLED.off()
if ATTACK_BLUE:
    while(True):
        data = [-1, -1, -1, -1]
        clock.tick()
        img = sensor.snapshot()
        blobs = img.find_blobs(thresholds[1], x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        if len(blobs) != 0:
            largest_blob = sorted(blobs, key=lambda blob: -blob.area())[0]
            data[0] = round(360 - RADIANS_TO_DEGREES * atan2(largest_blob.cy() - 60, largest_blob.cx() - 80))
            if data[0] > 360:
                data[0] -= 360
            if data[0] < 0:
                data[0] += 360
            data[1] = round(sqrt((largest_blob.cx() - 80)**2 + (largest_blob.cy() - 60)**2))
            #img.draw_line(80, 60, largest_blob.cx(), largest_blob.cy()) # Not needed for Gameplay
        blobs = img.find_blobs(thresholds[0], x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        if len(blobs) != 0:
            largest_blob = sorted(blobs,key=lambda blob: -blob.area())[0]
            data[2] = round(360 - RADIANS_TO_DEGREES * atan2(largest_blob.cy() - 60, largest_blob.cx() - 80))
            if data[2] > 360:
                data[2] -= 360
            if data[2] < 0:
                data[2] += 360
            data[3] = round(sqrt((largest_blob.cx() - 80)**2 + (largest_blob.cy() - 60)**2))
            #img.draw_line(80, 60, largest_blob.cx(), largest_blob.cy()) # Not needed for Gameplay
        #print(clock.fps()) # Not needed for Gameplay
        uart.writechar(255)
        uart.writechar(255)
        uart.writechar(data[0] >> 8)
        uart.writechar(data[0])
        uart.writechar(data[1])
        uart.writechar(data[2] >> 8)
        uart.writechar(data[2])
        uart.writechar(data[3])
        #img.draw_line(82, 60, 78, 60)
        #img.draw_line(80, 62, 80, 58)
else:
    while(True):
        data = [-1, -1, -1, -1]
        clock.tick()
        img = sensor.snapshot()
        blobs = img.find_blobs(thresholds[0], x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        if len(blobs) != 0:
            largest_blob = sorted(blobs, key=lambda blob: -blob.area())[0]
            data[0] = round(360 - RADIANS_TO_DEGREES * atan2(largest_blob.cy() - 60, largest_blob.cx() - 80))
            if data[0] > 360:
                data[0] -= 360
            if data[0] < 0:
                data[0] += 360
            data[1] = round(sqrt((largest_blob.cx() - 80)**2 + (largest_blob.cy() - 60)**2))
            #img.draw_line(80, 60, largest_blob.cx(), largest_blob.cy()) # Not needed for Gameplay
        blobs = img.find_blobs(thresholds[1], x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        if len(blobs) != 0:
            largest_blob = sorted(blobs,key=lambda blob: -blob.area())[0]
            data[2] = round(360 - RADIANS_TO_DEGREES * atan2(largest_blob.cy() - 60, largest_blob.cx() - 80))
            if data[2] > 360:
                data[2] -= 360
            if data[2] < 0:
                data[2] += 360
            data[3] = round(sqrt((largest_blob.cx() - 80)**2 + (largest_blob.cy() - 60)**2))
            #img.draw_line(80, 60, largest_blob.cx(), largest_blob.cy()) # Not needed for Gameplay
        #print(clock.fps()) # Not needed for Gameplay
        uart.writechar(255)
        uart.writechar(255)
        uart.writechar(data[0] >> 8)
        uart.writechar(data[0])
        uart.writechar(data[1])
        uart.writechar(data[2] >> 8)
        uart.writechar(data[2])
        uart.writechar(data[3])
        #img.draw_line(82, 60, 78, 60)
        #img.draw_line(80, 62, 80, 58)
