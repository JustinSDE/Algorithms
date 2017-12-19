# filename: PID.py
# author: HinderKing
'''
in this file, I created a simulation to test PID test modules in order to figure out the effect of parameters
on performance.
I also created a programmed temperature control test module for fun
'''

import math
import matplotlib.pyplot as plt

CONSTPOWER = 20
EPISODENUM = 2000


class Heater:
    def __init__(self, roomtemperature, parampower=0.01, paramcoolrate=0.001):
        self.temperature = roomtemperature
        self.roomtemperature = roomtemperature
        self.parampower = parampower
        self.paramcoolrate = paramcoolrate

    def getTemperature(self, inputpower):
        self.temperature += self.parampower * inputpower - self.paramcoolrate * (
                self.temperature - self.roomtemperature + \
                0.5 * math.sqrt(abs(self.temperature - self.roomtemperature)))
        return self.temperature


class PIDController:
    def __init__(self, prop, integral, differential):
        self.param_p = prop
        self.param_i = integral
        self.param_d = differential
        self.accum_i = 0.0
        self.prev_diff = 0

    def getpower(self, measured_temp, target_temp):
        diff = measured_temp - target_temp
        diff_change = diff - self.prev_diff
        self.prev_diff = diff
        self.accum_i += diff
        power = -self.param_p * diff - self.param_d * diff_change - self.param_i * self.accum_i
        if power < 0:
            power = 0
        return power


if __name__ == "__main__":

    # test with constant input power to watch for temperature increase
    env = Heater(25, 0.01, 0.005)
    time = []
    temperature = []
    for i in range(EPISODENUM):
        time.append(i + 1)
        temperature.append(env.getTemperature(CONSTPOWER))

    plt.plot(time, temperature)
    plt.title("Temperature development with constant input power: 20")
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID
    param_p = 1.0
    param_i = 1.0
    param_d = 1.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)
    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 1.0
    param_i = 0.0
    param_d = 1.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)
    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 1.0
    param_i = 1.0
    param_d = 0.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)
    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 0.0
    param_i = 1.0
    param_d = 1.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)
    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 1.0
    param_i = 0.0
    param_d = 0.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)

    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 0.0
    param_i = 1.0
    param_d = 0.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)

    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ## test with constant target tempeature to see PID performance, perfect PID, tuning parameters
    param_p = 0.0
    param_i = 0.0
    param_d = 1.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)
    time = []
    temperature = []
    target_temp = 62.5
    inputpower = 0
    for i in range(EPISODENUM):
        time.append(i + 1)
        cur_temp = env.getTemperature(inputpower)
        temperature.append(cur_temp)
        inputpower = agent.getpower(cur_temp, target_temp)

    plt.plot([0, EPISODENUM], [target_temp, target_temp], label='target temperature')
    plt.plot(time, temperature, label='measured temperature')
    plt.title("PID controller: {}, {}, {}".format(param_p, param_i, param_d))
    plt.xlabel('time')
    plt.ylabel('Sample Temperature')
    plt.legend()
    plt.show()

    ### programmed temperature control module
    ## increase the temperature to to 75 degC in 500 s and
    # then hold on for 500 seconds, and then
    # cool down to 25 in 500 seconds
    # and then hold on for 500 seconds

    target_temp = []  # generate the target_temperature profile
    for i in range(500):
        target_temp.append(25 + 0.1 * i)
    for i in range(500):
        target_temp.append(75.0)
    for i in range(500):
        target_temp.append(75.0 - 0.1 * i)
    for i in range(500):
        target_temp.append(25.0)

    param_p = 1.0
    param_i = 1.0
    param_d = 1.0
    env = Heater(25, 0.01, 0.005)
    agent = PIDController(param_p, param_i, param_d)

    actual_temp = 25.0
    measured_temp = []
    output_power = []
    actual_pow = 0.0
    time = []
    for i in range(len(target_temp)):
        time.append(i + 1)
        actual_temp = env.getTemperature(actual_pow)
        measured_temp.append(actual_temp)
        actual_pow = agent.getpower(actual_temp, target_temp[i])
        output_power.append(actual_temp)

    fig = plt.figure(1)
    ax = fig.add_subplot(111)
    plt.plot(time, target_temp, 'k--', label='target temperature')
    plt.plot(time, measured_temp, label='measured temperature')
    plt.legend()
    plt.xlabel('time')
    plt.ylabel('Temperature')
    plt.title("Programming temperature control using PID: {}, {}, {}".format(param_p, param_i, param_d))
    a = fig.add_subplot(313, fc='none')
    plt.plot(time, output_power, 'r', lw=0.5, label='power')
    a.yaxis.tick_right()
    a.yaxis.set_label_position("right")
    plt.ylabel("power")
    plt.xticks([])
    plt.show()
