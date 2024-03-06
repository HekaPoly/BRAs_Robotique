import numpy as np
import matplotlib.pyplot as plt
from numpy import random
import time

# Paramètres du PID
KP = 1
KI = 5
KD = 0

# Constantes
FREQUENCY_CLOCK_HZ = 72000000
PRESCALER = 9
STEPS_PER_TURN = 1600
DEGREES_PER_STEPS = 0.06

# Variables 
desired_angle = 360
i = 1
iteration = 100000       #max iteration before ending simulation

error=np.zeros(iteration)
ARR = np.zeros(iteration)
Time = np.zeros(iteration)

position = np.zeros(iteration)
pwm_frequency_hz = np.zeros(iteration)
position[0] = 0
error[0] = 0
current_pwm_frequency_hz = 0.1
eint = 0

dT = 1/1000            #Approximation of computation time per cycle of 1ms
isTrajectoryCompleted = False

while True:
    # Verify error and pass by PID if we still haven't reach trajectory
    error[i] = desired_angle - position[i - 1]

    #if (np.abs(error[i]) >= 1):
    # Verify change of direction
    if (error[i] < 0):
        DIR = -1
    else:
        DIR = 1

    # Integral error term is the accumulation of the previous errors
    # eint = ((error[i] + error[i - 1])* dT)
    # edev = (error[i] - error[i - 1]) / dT
    
    # Main formula to determine the output of the PID controller
    pwm_frequency_hz[i] = np.abs((KP * (error[i] - error[i - 1])) + (KI * error[i]))

    # Limiter to not have too low or high ARR
    """
    if (pwm_frequency_hz[i] > 10000):
        pwm_frequency_hz[i] = 10000
    elif (pwm_frequency_hz[i] < 500):
        pwm_frequency_hz[i] = 500
    """

    ARR[i] = (FREQUENCY_CLOCK_HZ / (pwm_frequency_hz[i] * (PRESCALER + 1))) - 1
        
    # Simulate positioning of the stepper motor (theorical) - This would usually be replaced by the encoder measurement
    position[i] = position[i - 1] + (((0.096 * pwm_frequency_hz[i]) / STEPS_PER_TURN) * DIR)

    Time[i] = i * dT
    i += 1
    """
    else:
        isTrajectoryCompleted = True

        if (isTrajectoryCompleted == True):

            fig, ax = plt.subplots(3)
        
            # Accessing each axes object to plot the data through returned array
            ax[0].plot(Time[:i], position[:i], '-', color='blue')

            ax[1].plot(Time[:i], ARR[:i], '-', color='red')

            ax[2].plot(Time[:i], pwm_frequency_hz[:i], '-', color='black')

            plt.show()

            # Select new angle
            print("Enter desired angle")
            desired_angle = int(input())
            print(desired_angle)

            desired_angle = random.randint(0, 360)
            #print(desired_angle)

            # Reset the integral term because no error has yet to be accumulated
            eint = 0

            isTrajectoryCompleted = False
    """ 
    if (i >= iteration):
        print(desired_angle)
        # Creating 2 subplots
        fig, ax = plt.subplots(3)
        
        # Accessing each axes object to plot the data through returned array
        ax[0].plot(Time[:i], position[:i], '-', color='blue')

        ax[1].plot(Time[:i], ARR[:i], '-', color='red')

        ax[2].plot(Time[:i], pwm_frequency_hz[:i], '-', color='black')

        plt.show()

        break