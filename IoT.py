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
    BROKER_IP = "192.168.10.11"
    BROKER_PORT = 1883
    
    # Inisiasi client sebagai publisher
    pub = mqtt_client.Client()

    # Koneksikan ke broker
    pub.connect(BROKER_IP, BROKER_PORT)

    # Publish message
    while True:
        temperature=random.randint(31,35)
        humidity=random.randint(65,79)
        oxygen=random.randint(70,75)
        ph=random.randint(4,7)
        pressure=random.randint(1000,10015)
        date=datetime.datetime.now().strftime("%H:%M:%S %d/%m/%Y")

        data={
            'temperature':temperature,
            'humidity':humidity,
            'oxygen':oxygen,
            'ph':ph,
            'pressure':pressure,
            'identifier':argv[1],
            'date':date
            }
        
        pub.publish("/sensor/"+argv[1], json.dumps(data))

        print (data)
        time.sleep(1)