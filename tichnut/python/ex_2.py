# Name: ex_2.py
# Author: dipper
# Date: 27.5.2026
# Description: the code takes the mouse to random places on the screen every 10 seconds
# imports
import win32api
import random, time

# this function generates random x & y places on the screen
# and returns 2 x_cordinates
def random_xy():
    x_cordinate = random.randint(0, 1920)
    y_cordinate = random.randint(0, 1080)
    return x_cordinate, y_cordinate

def main():
    while 1:
        x_cordinate, y_cordinate = random_xy()
        win32api.mouse_event(1, x_cordinate, y_cordinate, 0)
        print ("x_cordinate-> ", x_cordinate,"\n", "y_cordinate-> ", y_cordinate)
        print ("to stop press cntrl + c")
        time.sleep(10)


if __name__=="__main__":
    main()