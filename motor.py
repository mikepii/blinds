from gpiozero import Motor
from time import sleep

motor = Motor(forward=12, backward=13)

while True:
    motor.forward(0.1)
    sleep(3)
    motor.backward()
    sleep(3)
