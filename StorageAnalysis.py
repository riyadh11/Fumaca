#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import Class DatabaseHandler 
from DatabaseHandler import DatabaseHandler
from StorageHandler import StorageHandler
from sys import argv, exit
from bson.json_util import dumps
import json, time, datetime

#main function
if __name__ == "__main__":
     
    if(len(argv) != 2) :
        print ("Usage : python StorageAnalysis.py <Minute>")
        exit()

    STORAGE_IP = "127.0.0.1"
    STORAGE_PORT = 9000

    DATABASE_IP = "127.0.0.1"
    DATABASE_PORT = 27017

    print ("[Info] System Running and automatic dump database for every {} minutes".format(argv[1]))
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    while 1:
        try:
            print ("[LOG] Start Dump Data")
            logs = list(Database.findBulkDocument("sensor",select={"_id":False}))
            
            # Writing Data
            Storage = StorageHandler(STORAGE_IP, STORAGE_PORT)
            directory = "/Analysis/"+datetime.datetime.now().strftime("%d%m%y")
            fileName = datetime.datetime.now().strftime("%H%M") + ".json"
            jsonData = json.dumps(json.loads(dumps(logs)))#, sort_keys=False,indent=4, separators=(',', ': '))
            Storage.write(directory+"/"+fileName, "w", jsonData)
            
            print ("[LOG] Success Dump Data")

            # Sleep
            time.sleep(60*int(argv[1]))

        except KeyboardInterrupt:
            print ("BYE")
            exit()
    