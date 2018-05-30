#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import library paho mqtt
import paho.mqtt.client as mqtt_client
import socket, json, struct, datetime
from sys import argv, exit

# Fungsi untuk handle message yang masuk
def handle_message(mqttc, obj, msg):
    # Dapatkan topik dan payloadnya
    topic = msg.topic
    payload = msg.payload
    payload = payload.decode('utf-8')
    collect_data(payload)

# Fungsi menyimpan data
def collect_data(payload):
    payload = json.loads(payload)
    payload['datetime']=datetime.datetime.now()
    data.append(payload)

    if(len(data)>=MAX_MESSAGE):
        send_msg(json.dumps(data, indent=4, sort_keys=True, default=str).encode('utf-8'))
        data[:] = []
        print ("[LOG] Sending Data")

# Fungsi mengirim data
def send_msg(msg):
    msg = struct.pack('>I', len(msg)) + msg
    # Koneksi ke Receiver
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.connect((RECEIVER_IP, RECEIVER_PORT))
    tcp_sock.send(msg)
    tcp_sock.shutdown(1)
    tcp_sock.close()

#main function
if __name__ == "__main__":
     
    if(len(argv) < 2) :
        print ("Usage : python Gateway.py <Number of Nodes>")
        exit()

    # Define Broker
    BROKER_IP = "13.67.76.30"
    BROKER_PORT = 1883

    # Define Receiver
    RECEIVER_IP = "192.168.10.11"
    RECEIVER_PORT = 5555

    # Inisiasi client mqtt sebagai subscriber
    sub = mqtt_client.Client()

    # Koneksikan ke broker
    sub.connect(BROKER_IP, BROKER_PORT)

    # List
    data = []

    # Define Buffer Time
    MINUTE = 1

    # Define Nodes
    NODES = int(argv[1])

    # Define Max Message
    MAX_MESSAGE = (MINUTE * 60 * NODES) + NODES

    # Daftarkan fungsinya untuk event on_message
    sub.on_message = handle_message

    # Subscribe ke sebuah topik
    sub.subscribe("/sensor/#")

    print ('[Info] Subscribe at {} sensor'.format(str(NODES)))

    # Loop forever
    sub.loop_forever()