import sensor, image, time
import pyb

ROBOT_A = True
YELLOW = 1
BLUE = 2
ORANGE = 4
FRAME_WIDTH = 240
FRAME_HEIGHT = 240

# Yellow, Blue, Orange
thresholds = [(39, 81, -12, 6, 23, 53), (0, 0, -128, 127, -128, 127), (42, 70, 30, 82, 20, 57)]

sensor.reset()
redLED = pyb.LED(1)
redLED.on()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False, (-6.02073, -6.02073, -0.855915))
sensor.set_brightness(0)
sensor.set_contrast(0)
sensor.set_saturation(0)
sensor.set_windowing((FRAME_WIDTH, FRAME_HEIGHT))
clock = time.clock()
uart = pyb.UART(3, 115200, timeout_char = 10)
redLED.off()

while(True):
    data = [120, 120, 120, 120, 120, 120]
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs(thresholds, x_stride = 5, y_stride = 5, area_threshold = 0, pixel_threshold = 200, merge = False, margin = 23)
    blobs = sorted(blobs, key=lambda blob: -blob.area())
    yellow = None
    blue = None
    orange = None
    for blob in blobs:
        if data[0] == 120 and data[1] == 120 and blob.code() == YELLOW:
            data[0] = 240 - blob.cx()
            data[1] = 240 - blob.cy()
        if data[2] == 120 and data[3] == 120 and blob.code() == BLUE:
            data[2] = 240 - blob.cx()
            data[3] = 240 - blob.cy()
        if data[4] == 120 and data[5] == 120 and blob.code() == ORANGE:
            data[4] = 240 - blob.cx()
            data[5] = 240 - blob.cy()
    uart.writechar(234)
    uart.writechar(234)
    for byte in data:
        uart.writechar(byte)
    img.draw_line(round(FRAME_WIDTH / 2) - 10, round(FRAME_HEIGHT / 2), round(FRAME_WIDTH / 2) + 10, round(FRAME_HEIGHT / 2))
    img.draw_line(round(FRAME_WIDTH / 2), round(FRAME_HEIGHT / 2) + 10, round(FRAME_WIDTH / 2), round(FRAME_HEIGHT / 2) - 10)
    img.draw_line(round(FRAME_WIDTH / 2), round(FRAME_HEIGHT / 2), 240 - data[0], 240 - data[1])
    img.draw_line(round(FRAME_WIDTH / 2), round(FRAME_HEIGHT / 2), 240 - data[2], 240 - data[3])
    img.draw_line(round(FRAME_WIDTH / 2), round(FRAME_HEIGHT / 2), 240 - data[4], 240 - data[5])
