# -*- coding: utf-8 -*-
"""
**************************************************************************************
*                              Actuator
*                           =============
*  This software is intended to convert english text into braille characters
*  MODULE: Actuator
*  Filename: Actuator.py
*  Version: 1.0.0  
*  Date: February 9, 2019
*  
*  Author: Aditya Kumar Singh
*  Team Name: Victorious Visionaries
*  Team Members: Aditya Kumar Singh, Raj Kumar Bhagat,
*                Ruphan S, Yash Patel
***************************************************************************************
"""

#Importing required libraries
from time import sleep
import RPi.GPIO as GPIO

"""
    Function which initialises all the required PINs in OUTPUT mode.
    And give logic 0 output to thr pins initially.
    Example call: init()
"""
def init():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(11, GPIO.OUT)
    GPIO.setup(12, GPIO.OUT)
    GPIO.setup(13, GPIO.OUT)
    GPIO.setup(15, GPIO.OUT)
    GPIO.setup(16, GPIO.OUT)
    GPIO.setup(18, GPIO.OUT)
    set_all_low()

"""
    Function which sets all the PINs to digitaly LOW state.
    Example call: set_all_low()
"""    
def set_all_low():
    GPIO.output(11, GPIO.LOW)
    GPIO.output(12, GPIO.LOW)
    GPIO.output(13, GPIO.LOW)
    GPIO.output(15, GPIO.LOW)
    GPIO.output(16, GPIO.LOW)
    GPIO.output(18, GPIO.LOW)

"""
    Function which maps the given array index to its corresponding PIN number
    to which it is attached to RPi adn returns the PIN number on RPi.
    Example call: x = get_pin_number(5)
"""
def get_pin_number(pin):
    str_= -1
    # Pins which are to be used from Rpi for actuatng.
    # 12 11 13 15 16 18
    if(pin==0):
        str_=16
    elif(pin==1):
        str_=18
    elif(pin==2):
        str_=12
    elif(pin==3):
        str_=15
    elif(pin==4):
        str_=11
    elif(pin==5):
        str_=13
    return str_

"""
    Function to set the particular PIN as HIGH or LOW depending upon the argument
    passed.
    Example Call: set_port_pin(0,0) to make pin 0 LOW,
                  set_port_pin(0,1) to make pin 0 HIGH 
"""
def set_port_pin(pin,value):
    ret=get_pin_number(pin)
    if(value):
        #HIGH
        GPIO.output(ret, GPIO.HIGH)
    else:
        GPIO.output(ret, GPIO.LOW)
        #LOW

"""
    Function to set the braille terminal according the Braille value passed.
    Example Call: actuate([1,1,1,0,0,0])
"""
def actuate(brl):
    index=0
    for i in brl:
        set_port_pin(index,i)
        index+=1
"""
    Function to clean GPIO PINs used in the module.
    Example Call: clean()
"""
def clean():
    GPIO.cleanup()
    
init()
