#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
#Import Library pyspark
from pyspark import SparkConf, SparkContext
from pyspark.sql.session import SparkSession
from pyspark import SparkContext
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg
import json, datetime,time
from sys import argv, path
path.insert(0,"../Common/")
from DatabaseHandler import DatabaseHandler

if __name__ == "__main__":
     
    if(len(argv) != 2) :
        print ("Usage : python AnalysisProcess.py <Minute>")
        exit()
    
    print ("[Info] System Running and automatic processing data for every {} minutes".format(argv[1]))
    
    DATABASE_IP = "192.168.10.11"
    DATABASE_PORT = 27017

    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    spark = SparkSession.builder.appName("Analysis Process").getOrCreate()
            
    while 1:
        try:
            print ("[LOG] Start Processing Data")
            directory = datetime.datetime.now().strftime("%d%m%y")
            fileName = datetime.datetime.now().strftime("%H%M") + ".json"

            df = spark.read.json("hdfs://master:9000/sensor/{}/{}".format(directory,fileName))
            
            #AVG
            avgSulfur = df.agg({'sulfur' : 'avg'}).collect()[0][0]
            avgAsap = df.agg({'asap' : 'avg'}).collect()[0][0]
            avgKarbon = df.agg({'karbon' : 'avg'}).collect()[0][0]
            avgOzon = df.agg({'ozon' : 'avg'}).collect()[0][0]
            avgNitrogen = df.agg({'nitrogen' : 'avg'}).collect()[0][0]
            avgSuhu = df.agg({'suhu' : 'avg'}).collect()[0][0]
            average = {"sulfur" : avgSulfur, "asap" : avgAsap, "karbon" : avgKarbon, "ozon" : avgOzon, "nitrogen" : avgNitrogen, "suhu" : avgSuhu}

            #MAX
            maxSulfur = df.agg({'sulfur' : 'max'}).collect()[0][0]
            maxAsap = df.agg({'asap' : 'max'}).collect()[0][0]
            maxKarbon = df.agg({'karbon' : 'max'}).collect()[0][0]
            maxOzon = df.agg({'ozon' : 'max'}).collect()[0][0]
            maxNitrogen = df.agg({'nitrogen' : 'max'}).collect()[0][0]
            maxSuhu = df.agg({'suhu' : 'max'}).collect()[0][0]
            max = {"sulfur" : maxSulfur, "asap" : maxAsap, "karbon" : maxKarbon, "ozon" : maxOzon, "nitrogen" : maxNitrogen, "suhu": maxSuhu}

            #MIN
            minSulfur = df.agg({'sulfur' : 'min'}).collect()[0][0]
            minAsap = df.agg({'asap' : 'min'}).collect()[0][0]
            minKarbon = df.agg({'karbon' : 'min'}).collect()[0][0]
            minOzon = df.agg({'ozon' : 'min'}).collect()[0][0]
            minNitrogen = df.agg({'nitrogen' : 'min'}).collect()[0][0]
            minSuhu = df.agg({'suhu' : 'min'}).collect()[0][0]
            min = {"sulfur" : minSulfur, "asap" : minAsap, "karbon" : minKarbon, "ozon" : minOzon, "nitrogen" : minNitrogen, "suhu": minSuhu}

            hasil = {"average":average, "max":max, "min":min, "datetime":datetime.datetime.now()}

            #Insert to Database
            Database.insertOneDocument("statistik",hasil)
            print ("[LOG] Success Processing Data")

            # Sleep
            time.sleep(60*int(argv[1]))

        except KeyboardInterrupt:
            print ("BYE")
            exit()