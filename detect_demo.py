import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
import math
import random
import image_utils

def init_random_square(size, length):
    img = np.zeros((size, size))
    img[int(size/2-length/2):int(size/2+length/2), int(size/2-length/2):int(size/2+length/2)] = 255

    degree = random.randint(0, 360)
    print('degree: {}'.format(degree))
    img = image_utils.rotate_img(img, degree)

    x_trans = random.randint(-30,30)
    y_trans = random.randint(-30,30)
    img = image_utils.translate_img(img, x_trans, y_trans)

    return img, degree

def main():
    square, ori_angle = init_random_square(256, 60)
    square = image_utils.add_random_noise(square, 30)

    fimg = np.fft.fft2(square)
    fshift = np.fft.fftshift(fimg)
    mag_spec = np.log(np.abs(fshift))

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

    plt.subplot(121), plt.imshow(square, cmap='gray')
    plt.subplot(122), plt.imshow(mag_spec, cmap='gray')
    plt.show()

if __name__ == '__main__':
    for i in range(10):
        main()
