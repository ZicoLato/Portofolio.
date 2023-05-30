# -*- coding: utf-8 -*-
"""
Created on Tue Jul 12 10:06:44 2022

@author: Asus
"""

import cv2
import numpy as np
from imutils.object_detection import non_max_suppression


## Histogram of Oriented Gradients Detector
HOGCV = cv2.HOGDescriptor()
HOGCV.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())#deteksi gambar aslinya

def Detector(frame):
    ## USing Sliding window concept
    #rect=rectangle penyimpan dijadikan array,weight mengambil hogcv untuk mendeteksi , winstride= metode ngeslide-ngeslide manusia buat kotak,#scale kecepatannya
    rects, weights = HOGCV.detectMultiScale(frame, winStride=(4, 4), padding=(8, 8), scale=1.03)
    rects = np.array([[x, y, x + w, y + h] for (x, y, w, h) in rects])
    pick = non_max_suppression(rects, probs=None, overlapThresh=0.25)#metode kotak nya bisa digabung jika kecil"
    c = 1#buat perulangan nambah manusia
    for x, y, w, h in pick:
        cv2.rectangle(frame, (x, y), (w, h), (139, 34, 104), 2)
        cv2.rectangle(frame, (x, y - 20), (w,y), (139, 34, 104), -1)#139 tiga digit code warna
        cv2.putText(frame, f'P{c}', (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
        c += 1

    cv2.putText(frame, f'Total Persons : {c - 1}', (20, 450), cv2.FONT_HERSHEY_DUPLEX, 0.8, (255, 255,255), 2)
    cv2.imshow('output', frame)
    return frame

cap = cv2.VideoCapture('tubes.mp4')


while True:
    ret, frame = cap.read()
    frame = Detector(frame)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cv2.destroyAllWindows()