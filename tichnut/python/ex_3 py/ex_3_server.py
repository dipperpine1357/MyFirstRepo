# Name: ex_3.py
# Author: dipper
# Date: 28.5.2026
# Description: the code takes cmd commands through a tcp connection
# imports
import socket
import subprocess

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432
BYTES_RECIVED = 1024
DECODE_TYPE = "utf-8"

def try1():
    # create an INET, STREAMing socket
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to a public host, and a well-known port
    serversocket.bind((HOST, PORT))

    #queue up as many as 5 connect requests
    serversocket.listen(2)

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST, PORT))
        server_socket.listen()
        connection, address = server_socket.accept()
        with connection:
            print(f"Connected by {address}")
            while True:
                data = connection.recv(BYTES_RECIVED)
                data = data.decode(DECODE_TYPE) #convert bytes to string

                # if we receive nothing then close connection
                if not data:
                    break
                print(f"command: {data}")

                #running the command
                command = subprocess.run(data,shell=True ,capture_output=True, text=True)
                print("Output:", command.stdout)
                print("Return Code:", command.returncode)

                # code = subprocess.call(data)

                if command.returncode == 1:
                    print("Success")
                else:
                    print("Failed")


                #connection.sendall(data)





if __name__=="__main__":
    main()