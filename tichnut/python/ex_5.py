# Name: ex_5.py
# Author: dipper
# Date: 31.5.2026
# Description:  the code recives a path to a dir and 
#               prints a list of the files in the directory
# imports
import os

# this function recives a directory path
# this function returns a list with all 
# the files and folder in a directory 
def list_files2(path):
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

        temp_files_list.append(object)

        # it is possible to replace the line above with the if statment so the listwon't show the folders
        # if os.path.isfile(temp_path):
        #     # add to list the files in the directory
        #     temp_files_list.append(object)
    files_list = temp_files_list
    

    # find all the folders in current dir
    for folder in all_objects:
        temp_path_dir = path + "\\" + folder
        if os.path.isdir(temp_path_dir):
            temp_folder_list.append(folder) 

    # run throughout the directories in the folder
    for dir in temp_folder_list:

        temp_path = path + "\\" + dir
        files_list.append(list_files2(temp_path))

    return files_list


def main():
    path = input("enter a directory path: (like-> C:\dipper\pictures_of_dipper)\n")
    full_list = []
    

    full_list = list_files2(path)
    print (f"finall list : \n {full_list}")
    input("been nice attackingwith u \nbye")


if __name__=="__main__":
    main()