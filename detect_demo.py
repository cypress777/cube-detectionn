import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
import math
import random
import sys
import image_utils

def init_random_square(size, length, ratio=1):
    img = np.zeros((size, size))
    img[int(size/2-length/2):int(size/2+length/2), int(size/2-length/2*ratio):int(size/2+length/2*ratio)] = 255

    degree = random.randint(0, 360)
    print('degree: {}'.format(degree))
    img = image_utils.rotate_img(img, degree)

    x_trans = random.randint(-30,30)
    y_trans = random.randint(-30,30)
    img = image_utils.translate_img(img, x_trans, y_trans)

    return img, degree

def hough_test_random():
    square, ori_angle = init_random_square(256, 60, 0.7)
    square = image_utils.add_random_noise(square, 30)
    square = np.uint8(square)
    
    edges = cv.Canny(square, 50, 150)
    minLineLength = 20
    maxLineGap = 10
    lines = cv.HoughLinesP(edges, 1, np.pi/180, 20, minLineLength, maxLineGap)

    for i in range(len(lines)):
        for x1, y1, x2, y2 in lines[i]:
            cv.line(square, (x1, y1), (x2, y2), (0, 255, 0), 2)
            angle = math.atan2((y2 - y1), (x2 - x1)) / math.pi * 180
            print('Predict: {}'.format(angle))

    cv.imshow('hough test', square)
    cv.waitKey(0)

def hough_test_real():
    square = cv.imread(sys.argv[1], 0)
    square = np.uint8(square)
    
    edges = cv.Canny(square, 50, 150)
    minLineLength = 50
    maxLineGap = 10
    lines = cv.HoughLinesP(edges, 1, np.pi/180, 20, minLineLength, maxLineGap)

    for i in range(len(lines)):
        for x1, y1, x2, y2 in lines[i]:
            cv.line(square, (x1, y1), (x2, y2), (0, 128, 0), 2)
            angle = math.atan2((y2 - y1), (x2 - x1)) / math.pi * 180
            print('Predict: {}'.format(angle))

    cv.resize(square, (512, 512), interpolation = cv.INTER_CUBIC)
    cv.imshow('hough test', square)
    cv.waitKey(0)

def fft_test_random():
    square, ori_angle = init_random_square(256, 60, 0.7)
    square = image_utils.add_random_noise(square, 30)

    fimg = np.fft.fft2(square)
    fshift = np.fft.fftshift(fimg)
    mag_spec = np.log(np.abs(fshift))
    ph_spec = np.angle(fshift)

    mag_spec[70:186, 70:186] = 0
    top_num =5
    max_x_stack = np.zeros(top_num).astype(np.int)
    max_y_stack = np.zeros(top_num).astype(np.int)
    i = 0
    min_mag = np.min(mag_spec)
    while i < top_num:
        max_y, max_x = np.where(mag_spec == np.max(mag_spec))
        for j in range(len(max_x)):
            if i + j > top_num - 1:
                break
            max_x_stack[i+j] = max_x[j]
            max_y_stack[i+j] = max_y[j]
            mag_spec[max_y[j]][max_x[j]] = min_mag
        i = i + len(max_x)

    i = 0
    total_error = 0
    for i in range(top_num):
        cv.line(square, (max_x_stack[i], max_y_stack[i]), (256 - max_x_stack[i], 256 - max_y_stack[i]), (128, 0, 0), 1)
        angle = -math.atan2((max_y_stack[i] - 128), (max_x_stack[i] - 128)) / math.pi * 180
        mult = math.modf(math.fabs(ori_angle - angle)/90.)[1]
        error = min((math.fabs(ori_angle - angle) - mult*90), ((mult + 1)*90 - math.fabs(ori_angle - angle)))
        total_error = total_error + error
    total_error = total_error / top_num
    print('Prediction Error: {}'.format(total_error))

    plt.subplot(131), plt.imshow(square, cmap='gray')
    plt.subplot(132), plt.imshow(mag_spec, cmap='gray')
    plt.subplot(133), plt.imshow(ph_spec, cmap='gray')
    plt.show()

def fft_test_real():
    square = cv.imread(sys.argv[1], 0)
    print(np.mean(square))
    square = square - np.mean(square)
    img_height, img_width = square.shape
   # print(square.shape)
   # nh = int(math.pow(2, int(math.log(img_height, 2))))
   # nw = int(math.pow(2, int(math.log(img_width, 2))))
   # square = square[0:nh, 0:nw]
   # img_height, img_width = square.shape
   # print(square.shape)

    fimg = np.fft.fft2(square)
    fshift = np.fft.fftshift(fimg)
    mag_spec = np.log(np.abs(fshift))
    ph_spec = np.angle(fshift)

    mag_spec[int(img_height/2*0.9):int(img_height/2*1.1), int(img_width/2*0.9):int(img_width/2*1.1)] = 0
    top_num =5
    max_x_stack = np.zeros(top_num).astype(np.int)
    max_y_stack = np.zeros(top_num).astype(np.int)
    i = 0
    min_mag = np.min(mag_spec)
    print(np.max(mag_spec))
    print(np.min(mag_spec))
    while i < top_num:
        max_y, max_x = np.where(mag_spec == np.max(mag_spec))
        for j in range(len(max_x)):
            if i + j > top_num - 1:
                break
            max_x_stack[i+j] = max_x[j]
            max_y_stack[i+j] = max_y[j]
            mag_spec[max_y[j]][max_x[j]] = min_mag
        i = i + len(max_x)

    i = 0
    for i in range(top_num):
        cv.line(square, (max_x_stack[i], max_y_stack[i]), (img_width - max_x_stack[i], img_height - max_y_stack[i]), (255, 0, 0), 2)
        angle = -math.atan2((max_y_stack[i] - img_height/2), (max_x_stack[i] - img_width/2)) / math.pi * 180
        print('Angle: {}'.format(angle))

    plt.subplot(131), plt.imshow(square, cmap='gray')
    plt.subplot(132), plt.imshow(mag_spec, cmap='gray')
    plt.subplot(133), plt.imshow(ph_spec, cmap='gray')
    plt.show()

if __name__ == '__main__':
#    for i in range(10):
#        fft_test_random()
#        hough_test_random()
#     fft_test_real()
     hough_test_real()
