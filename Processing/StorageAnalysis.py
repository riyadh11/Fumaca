#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import Class DatabaseHandler 
from sys import argv, exit, path
from bson.json_util import dumps
import json, time, datetime
path.insert(0,"../Common/")
from DatabaseHandler import DatabaseHandler
from StorageHandler import StorageHandler

#main function
if __name__ == "__main__":
     
    if(len(argv) != 2) :
        print ("Usage : python StorageAnalysis.py <Minute>")
        exit()

    STORAGE_IP = "192.168.10.11"
    STORAGE_PORT = 9000

    DATABASE_IP = "192.168.10.11"
    DATABASE_PORT = 27017

    print ("[Info] System Running and automatic dump database for every {} minutes".format(argv[1]))
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    while 1:
        try:
            print ("[LOG] Start Dump Data")
            logs = list(Database.findBulkDocument("sensor",select={"_id":False}, sort=[("datetime",-1)], limit=60*int(argv[1])))
            
            # Writing Data
            Storage = StorageHandler(STORAGE_IP, STORAGE_PORT)
            directory = "/sensor/"+datetime.datetime.now().strftime("%d%m%y")
            fileName = datetime.datetime.now().strftime("%H%M") + ".json"
            jsonData = json.dumps(json.loads(dumps(logs)))#, sort_keys=False,indent=4, separators=(',', ': '))
            Storage.write(directory+"/"+fileName, "w", jsonData)
            
            print ("[LOG] Success Dump Data")

            # Sleep
            time.sleep(60*int(argv[1]))

        except KeyboardInterrupt:
            print ("BYE")
            exit()
    