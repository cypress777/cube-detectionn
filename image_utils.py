import cv2 as cv
import numpy as np
import random

def rotate_img(img, degree):
    cols, rows = img.shape 
    M = cv.getRotationMatrix2D((cols/2, rows/2), degree, 1)
    dst = cv.warpAffine(img, M, (cols, rows))
    return dst

def translate_img(img, x_trans, y_trans):
    cols, rows = img.shape 
    M = np.float32([[1, 0, x_trans],[0, 1, y_trans]])
    dst = cv.warpAffine(img, M, (cols,rows))
    return dst

def add_random_noise(img, strength):
    cols, rows = img.shape 
    num = random.randint(0, strength)
    for i in range(num):
        col = random.randint(0, cols-1)
        row = random.randint(0, rows-1)
        noise = random.randint(-30, 30)
        value = img[col][row] + noise
        value = min(value, 255)
        value = max(0, value)
        img[col][row] = value
    return img
