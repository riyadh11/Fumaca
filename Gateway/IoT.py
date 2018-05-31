#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import library mqtt, random, json, time
import paho.mqtt.client as mqtt_client
from sys import argv, exit
import random,json,time, datetime

#main function
if __name__ == "__main__":
     
    if(len(argv) < 2) :
        print ("Usage : python IoT.py <Identifier>")
        exit()

    # Define Broker
    BROKER_IP = "13.67.76.30"
    BROKER_PORT = 1883
    
    # Inisiasi client sebagai publisher
    pub = mqtt_client.Client()

    # Koneksikan ke broker
    pub.connect(BROKER_IP, BROKER_PORT)

    # Publish message
    while True:
        # Dummy data, for testing purpose only
        asap=random.randint(21,35)
        karbon=random.randint(65,79)
        ozon=random.randint(140,200)
        sulfur=random.randint(29,35)
        nitrogen=random.randint(100,150)
        suhu=random.randint(29,31)

        data={
            'asap':asap,
            'karbon':karbon,
            'ozon':ozon,
            'sulfur':sulfur,
            'nitrogen':nitrogen,
            'suhu':suhu,
            'identifier':argv[1],
            }
        
        pub.publish("/sensor/"+argv[1], json.dumps(data))

        print (data)
        time.sleep(1)