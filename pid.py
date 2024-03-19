import numpy as np
from numpy import random
import matplotlib.pyplot as plt
from numpy import random
import time

"""
PID parameters
"""
# Factor to smooth out and reduce the PWM frequency increase
FACTOR = 1

# Critical gain and period values (where the controller output oscillates constantly)
K_CRITICAL = 8.88889
T_CRITICAL_SECONDS = 0.1

# Controller gains - We use a PD controller since the Integral aspect of the controller does not interest us
# Equations are for a PID controller with no overshoot (found on Wikipedia - https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method)
KP = (K_CRITICAL * 0.2) * FACTOR
#KI = (0.4 * K_CRITICAL / T_CRITICAL_SECONDS) * FACTOR
KI = 0
KD = (0.066666 * K_CRITICAL * T_CRITICAL_SECONDS) * FACTOR
#KD = 0

"""
Constants
"""
FREQUENCY_CLOCK_HZ = 72000000
PRESCALER = 9
STEPS_PER_TURN = 1600
DEGREES_PER_STEPS = 360 / STEPS_PER_TURN

"""
Global variables
"""
# Equivalent of clockwise / counter-clockwise
direction = 1

desired_angle_degrees = 360

# Error values for Integral and Derivative components
eint = 0
edev = 0

# Sampling time - Also the approximation of the computation time per cycle evaluated to 50ms
dT = 50/1000

isTrajectoryCompleted = False

# Current iteration
i = 1
# Maximal iteration before ending the simulation
max_iteration = 500

"""
Arrays to contain data
"""
error = np.zeros(max_iteration)
ARR = np.zeros(max_iteration)
time = np.zeros(max_iteration)

position_degrees = np.zeros(max_iteration)
pwm_frequency_hz = np.zeros(max_iteration)
position_degrees[0] = 0
error[0] = 0

while True:
    # Verify error and pass by PID if we still haven't reach trajectory
    error[i] = desired_angle_degrees - position_degrees[i - 1]

    if (np.abs(error[i]) >= 1):
        # Verify change of direction
        if (error[i] < 0):
            direction = -1
        else:
            direction = 1
        
        eint = error[i - 1] + (error[i - 1] * dT)
        edev = (error[i] - error[i - 1]) / dT

        # Main formula to determine the output of the PID controller
        pwm_frequency_hz[i] = np.abs((KP * (error[i]) + (KI * eint) + (KD * edev)))
        
        if (pwm_frequency_hz[i] - pwm_frequency_hz[i - 1] > 50):
            pwm_frequency_hz[i] = pwm_frequency_hz[i - 1] + 50
        
        # Just in case we get a weird frequency value, set to 0
        if (pwm_frequency_hz[i] < 0):
            pwm_frequency_hz[i] = 0

        # Test formula for the Ziegler–Nichols method
        #pwm_frequency_hz[i] = np.abs((K_CRITICAL * error[i]))

        # ARR calculation - only if necessary for when porting code to stm32
        # ARR[i] = (FREQUENCY_CLOCK_HZ / (pwm_frequency_hz[i] * (PRESCALER + 1))) - 1
    else:
        desired_angle_degrees = random.randint(360)

    # Simulate position_degreesing of the stepper motor (theorical) - This would usually be replaced by the encoder measurement
    position_degrees[i] = position_degrees[i - 1] + ((((DEGREES_PER_STEPS * pwm_frequency_hz[i])) * direction))

    # Increment time values
    time[i] = i * dT
    i += 1

    if (i >= max_iteration):
        # Creating 2 subplots
        fig, ax = plt.subplots(2)
        
        # Accessing each axes object to plot the data through returned array
        ax[0].plot(time[:i], position_degrees[:i], '-', color='blue')
        ax[1].plot(time[:i], pwm_frequency_hz[:i], '-', color='black')

        plt.show()
        break