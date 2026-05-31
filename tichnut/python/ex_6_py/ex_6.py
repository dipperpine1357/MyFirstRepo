# Name: ex_6.py
# Author: dipper
# Date: 31.5.2026
# Description:  the code does dirbuster 
# imports
import requests

#CONSTANTS
DOMAIN_PATH = r"https://www.ynet.co.il"
FILE_PATH = r"C:\dipper\my_first_repo\tichnut\python\ex_6_py\common_files_names_ex6_py.txt"

# this func takes all the names
# this function returns all the seccessfull url names
def requesting (names, base_url):
    good_names = []
    current_url = ""
    for name in names:
        # print (name)
        current_url = base_url + "/" + name
        response = requests.get(current_url)

        # is the statuse code 200
        if (response.status_code == 200):
            good_names.append(name)
            # print ("hh")

            #is it a dir
            if (response.content != None):

                # doing recursion for directories
                good_names.append(requesting(names, current_url))
                # print (good_names)
    return good_names

def main():
    url = DOMAIN_PATH
    names = []
    seccess = []
    with open(FILE_PATH, "r") as file:
        for line in file:
            line = line.strip()
            names.append(line)
            url = DOMAIN_PATH + "/" + line
            # print (names)
            seccess = requesting(names, DOMAIN_PATH)
    print (f"""all the fitting names (if they are in [] then """
           f"""they are from the dir of the name before them)\n{seccess}""")
            



if __name__=="__main__":
    main()