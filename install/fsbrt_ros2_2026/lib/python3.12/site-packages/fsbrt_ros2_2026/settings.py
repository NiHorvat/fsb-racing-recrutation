#!/usr/bin/env python3 
#-*- coding: utf-8 -*-

"""
Author: Matej LovrekoviĆ

FSBRT Autonomous - Recruitment task

Define important variables used in simulation.
"""


def init():

    global SAMPLING
    global MAX_VELOCITY
    global STEERING_POWER
    global X_SECONDS_APPEREANCE
    global A_a
    global A_b
    global POINTS_IN_FUTURE


    SAMPLING = 150                  #Sampling time of simulation in Hz
    MAX_VELOCITY = 19.5             #Maximum velocity of a car
    STEERING_POWER = 3              #Assume steering is achieved with motor with constant moment output
    X_SECONDS_APPEREANCE = 0.1      #Each X_SECONDS_APPEREANCE formula is drawn on live plotting and velocities are saved
    A_a = 4                         #Acceleration constant
    A_b = 7                         #Braking constant
    POINTS_IN_FUTURE = 15           #Predict horison of checkpoints
 

