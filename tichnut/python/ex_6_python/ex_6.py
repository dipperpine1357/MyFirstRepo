# Name: ex_6.py
# Author: dipper
# Date: 31.5.2026
# Description:  the code does dirbuster 
#               (if they are in [] then they are from the dir of the name before them)
# imports
import requests

#CONSTANTS
GOOD_STATUSE_CODE = 200

# this func takes all the names as list
# this function returns all the seccessfull url names and domain names
def requesting (names, base_url):
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

def main():
    
    names = []
    seccess = []
    user_path = input("enter path to file with names to try\n like:"+
                        r"C:\dipper\my_first_repo\tichnut\python\ex_6_py\common_files_names_ex6_py.txt" + "\n")
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
            
    input("been nice attackingwith u \nbye")


if __name__=="__main__":
    main()