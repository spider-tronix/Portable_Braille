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

import pytesseract
import cv2
import numpy as np

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
