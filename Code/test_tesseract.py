# -*- coding: utf-8 -*-
"""
**************************************************************************************
*                              Simple OCR
*                           ===============
*  This program is intended to perform simple OCR in a given image/
*  MODULE: test_tesseract
*  Filename: test_tesseract.py
*  Version: 1.0.0  
*  Date: January 9, 2019
*  
*  Author: Aditya Kumar Singh
*  Team Name: Victorious Visionaries
*  Team Members: Aditya Kumar Singh, Raj Kumar Bhagat,
*                Ruphan S, Yash Patel
***************************************************************************************
"""

#Importing required Libraries

try:
    from PIL import Image
except ImportError:
    import Image

import os
import pytesseract
import cv2

"""
    This program is just to test the OCR functionality.
    This will read an image and then tries to read text present in it.
    If found(any), then tthe text will be printed on the screen
"""
text = cv2.imread('text.jpg')
cv2.imshow('text',text)
cv2.waitKey(0)
cv2.destroyAllWindows()
print(pytesseract.image_to_string(text))

"""
To test the rotation detection functionality of the tesseract
"""
test_images = ['test1_0.jpg', 'test1_90.jpg', 'test1_180.jpg', 'test_tilt.png']
for image in test_images:
    path = os.path.join('..\\Images', image)
    img = cv2.imread(path)
    cv2.imshow(image, img)
    print(image+' :', '\n', pytesseract.image_to_osd(path), '\n')
cv2.waitKey(0)
cv2.destroyAllWindows()
