from flask import Flask,jsonify,json
from DatabaseHandler import DatabaseHandler
from flask_cors import CORS
from bson.json_util import dumps
#import json

app = Flask("Sensor App")
CORS(app)

DATABASE_IP = "10.11.12.13"
DATABASE_PORT = 27171

@app.route('/sensor', methods=['GET'])
def handle_get():
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    logs = list(Database.findBulkDocument("sensor", select={"_id":False}, sort=[("datetime",-1)], limit=60))
    return jsonify(Sensor=logs)

@app.route('/sensor', methods=['POST'])
def tambah_sensor():
    id_sensor = request.json['_id']
    temperature = request.json['temperature']
    humidity = request.json['humidity']
    pressure = request.json['pressure']
    oxygen = request.json['oxygen']
    ph = request.json['ph']
    date = request.json['date']
    identifier = request.json['identifier']

    new_data = {
        "_id": {
            "$oid": id_sensor
        },
        "temperature": temperature,
        "oxygen": oxygen,
        "humidity": humidity,
        "pressure": pressure,
        "date": date,
        "ph": ph,
        "identifier": identifier
    }
    with open("dump_json.json") as f:
        json_data = json.load(f)

    with open("dump_json.json", mode="w",encoding='utf-8') as ff:
        json.dump([], ff)

    with open("dump_json.json", mode='w', encoding='utf-8') as feedsjson:
        json_data.append(new_data)
        json.dump(json_data, feedsjson)

    return "OK"

app.run(port=80, host="0.0.0.0")